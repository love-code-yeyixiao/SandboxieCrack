#include "stdafx.h"
#include "SandMan.h"
#include <QtWidgets/QApplication>
#include "../QSbieAPI/SbieAPI.h"
#include "../QtSingleApp/src/qtsingleapplication.h"
#include "../QSbieAPI/SbieUtils.h"
//#include "../MiscHelpers/Common/qRC4.h"
#include "../MiscHelpers/Common/Common.h"
#include <windows.h>

CSettings* theConf = NULL;

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
	SetProcessDPIAware();
#endif // Q_OS_WIN 

	//QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); 
	//QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);

	QtSingleApplication app(argc, argv);
	app.setQuitOnLastWindowClosed(false);

	//InitConsole(false);

	SB_STATUS Status = CSbieUtils::DoAssist();
	if (Status.GetStatus()) {
		if(Status.GetStatus() == ERROR_OK) app.sendMessage("Status:OK");
		else app.sendMessage("Status:" + CSandMan::FormatError(Status)); // todo: localization
		return 0;
	}
	
	QString PendingMessage;

	QStringList Args = QCoreApplication::arguments();
	int CmdPos = Args.indexOf("-op", Qt::CaseInsensitive);
	if (CmdPos != -1) {
		QString Op;
		if (Args.count() > CmdPos)
			Op = Args.at(CmdPos + 1);
		PendingMessage = "Op:" + Op;
	}

	CmdPos = Args.indexOf("/box:__ask__", Qt::CaseInsensitive);
	if (CmdPos != -1) {
		// Note: a escaped command ending with \" will fail and unescape "
		//QString CommandLine;
		//for (int i = CmdPos + 1; i < Args.count(); i++)
		//	CommandLine += "\"" + Args[i] + "\" ";
		//PendingMessage = "Run:" + CommandLine.trimmed();
		LPWSTR ChildCmdLine = wcsstr(GetCommandLineW(), L"/box:__ask__") + 13;
		PendingMessage = "Run:" + QString::fromWCharArray(ChildCmdLine);
	}

	if (!PendingMessage.isEmpty()) {
		if(app.sendMessage(PendingMessage))
			return 0;
	}
	else if (app.sendMessage("ShowWnd"))
		return 0;

	theConf = new CSettings("Sandboxie-Plus");

	//QThreadPool::globalInstance()->setMaxThreadCount(theConf->GetInt("Options/MaxThreadPool", 10));

	CSandMan* pWnd = new CSandMan();

	QObject::connect(&app, SIGNAL(messageReceived(const QString&)), pWnd, SLOT(OnMessage(const QString&)));
	if (!PendingMessage.isEmpty())
		QMetaObject::invokeMethod(pWnd, "OnMessage", Qt::QueuedConnection, Q_ARG(QString, PendingMessage));

	int ret =  app.exec();

	delete pWnd;

	delete theConf;
	theConf = NULL;

	return ret;
}

/*HANDLE hServerPipe = CreateFileW(L"\\\\.\\pipe\\qtsingleapp-sandma-ca4a-1", GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL);
if (hServerPipe != INVALID_HANDLE_VALUE) {
	DWORD lenWritten;
    WriteFile(hServerPipe, "test", 4, &lenWritten, NULL)

    CloseHandle(hServerPipe);
}*/