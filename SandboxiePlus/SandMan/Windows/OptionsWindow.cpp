#include "stdafx.h"
#include "OptionsWindow.h"
#include "SandMan.h"
#include "SettingsWindow.h"
#include "../MiscHelpers/Common/Settings.h"
#include "../MiscHelpers/Common/Common.h"
#include "../MiscHelpers/Common/ComboInputDialog.h"
#include "../MiscHelpers/Common/SettingsWidgets.h"
#include "Helpers/WinAdmin.h"


COptionsWindow::COptionsWindow(const QSharedPointer<CSbieIni>& pBox, const QString& Name, QWidget *parent)
	: QDialog(parent)
{
	m_pBox = pBox;

	m_Template = pBox->GetName().left(9).compare("Template_", Qt::CaseInsensitive) == 0;
	bool ReadOnly = /*pBox->GetAPI()->IsConfigLocked() ||*/ (m_Template && pBox->GetName().mid(9, 6).compare("Local_", Qt::CaseInsensitive) != 0);
	
	QSharedPointer<CSandBoxPlus> pBoxPlus = m_pBox.objectCast<CSandBoxPlus>();
	if (!pBoxPlus.isNull())
		m_Programs = pBoxPlus->GetRecentPrograms();

	Qt::WindowFlags flags = windowFlags();
	flags |= Qt::CustomizeWindowHint;
	//flags &= ~Qt::WindowContextHelpButtonHint;
	//flags &= ~Qt::WindowSystemMenuHint;
	//flags &= ~Qt::WindowMinMaxButtonsHint;
	flags |= Qt::WindowMinimizeButtonHint;
	//flags &= ~Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	bool bAlwaysOnTop = theConf->GetBool("Options/AlwaysOnTop", false);
	this->setWindowFlag(Qt::WindowStaysOnTopHint, bAlwaysOnTop);

	ui.setupUi(this);
	this->setWindowTitle(tr("Sandboxie Plus - '%1' Options").arg(Name));

	ui.tabs->setTabPosition(QTabWidget::West);
	ui.tabs->tabBar()->setStyle(new CustomTabStyle(ui.tabs->tabBar()->style()));

	ui.tabs->setTabIcon(0, CSandMan::GetIcon("Options"));
	ui.tabs->setTabIcon(1, CSandMan::GetIcon("Group"));
	ui.tabs->setTabIcon(2, CSandMan::GetIcon("Force"));
	ui.tabs->setTabIcon(3, CSandMan::GetIcon("Stop"));
	ui.tabs->setTabIcon(4, CSandMan::GetIcon("Start"));
	ui.tabs->setTabIcon(5, CSandMan::GetIcon("Wall"));
	ui.tabs->setTabIcon(6, CSandMan::GetIcon("Ampel"));
	ui.tabs->setTabIcon(7, CSandMan::GetIcon("Recover"));
	ui.tabs->setTabIcon(8, CSandMan::GetIcon("Advanced"));
	ui.tabs->setTabIcon(9, CSandMan::GetIcon("Template"));
	ui.tabs->setTabIcon(10, CSandMan::GetIcon("EditIni"));


	CreateDebug();

	if (m_Template)
	{
		ui.tabGeneral->setEnabled(false);
		ui.tabStart->setEnabled(false);
		ui.tabInternet->setEnabled(false);
		ui.tabAdvanced->setEnabled(false);
		ui.tabTemplates->setEnabled(false);

		for (int i = 0; i < ui.tabs->count(); i++) 
			ui.tabs->setTabEnabled(i, ui.tabs->widget(i)->isEnabled());

		ui.tabs->setCurrentIndex(ui.tabs->indexOf(ui.tabAccess));

		ui.chkShowForceTmpl->setEnabled(false);
		ui.chkShowStopTmpl->setEnabled(false);
		ui.chkShowNetFwTmpl->setEnabled(false);
		ui.chkShowAccessTmpl->setEnabled(false);
		ui.chkShowRecoveryTmpl->setEnabled(false);

		//ui.chkWithTemplates->setEnabled(false);
	}

	ui.tabs->setCurrentIndex(m_Template ? 10 : 0);

	//connect(ui.chkWithTemplates, SIGNAL(clicked(bool)), this, SLOT(OnWithTemplates()));

	m_ConfigDirty = true;

	CreateGeneral();

	// Groupes
	connect(ui.btnAddGroup, SIGNAL(clicked(bool)), this, SLOT(OnAddGroup()));
	connect(ui.btnAddProg, SIGNAL(clicked(bool)), this, SLOT(OnAddProg()));
	connect(ui.btnDelProg, SIGNAL(clicked(bool)), this, SLOT(OnDelProg()));
	//

	// Force
	connect(ui.btnForceProg, SIGNAL(clicked(bool)), this, SLOT(OnForceProg()));
	connect(ui.btnForceDir, SIGNAL(clicked(bool)), this, SLOT(OnForceDir()));
	connect(ui.btnDelForce, SIGNAL(clicked(bool)), this, SLOT(OnDelForce()));
	connect(ui.chkShowForceTmpl, SIGNAL(clicked(bool)), this, SLOT(OnShowForceTmpl()));
	//

	// Stop
	connect(ui.btnAddLingering, SIGNAL(clicked(bool)), this, SLOT(OnAddLingering()));
	connect(ui.btnAddLeader, SIGNAL(clicked(bool)), this, SLOT(OnAddLeader()));
	connect(ui.btnDelStopProg, SIGNAL(clicked(bool)), this, SLOT(OnDelStopProg()));
	connect(ui.chkShowStopTmpl, SIGNAL(clicked(bool)), this, SLOT(OnShowStopTmpl()));
	//

	// Start
	connect(ui.radStartAll, SIGNAL(clicked(bool)), this, SLOT(OnRestrictStart()));
	connect(ui.radStartExcept, SIGNAL(clicked(bool)), this, SLOT(OnRestrictStart()));
	connect(ui.radStartSelected, SIGNAL(clicked(bool)), this, SLOT(OnRestrictStart()));
	connect(ui.btnAddStartProg, SIGNAL(clicked(bool)), this, SLOT(OnAddStartProg()));
	connect(ui.btnDelStartProg, SIGNAL(clicked(bool)), this, SLOT(OnDelStartProg()));
	connect(ui.chkStartBlockMsg, SIGNAL(clicked(bool)), this, SLOT(OnStartChanged()));
	//

	CreateNetwork();

	CreateAccess();

	// Resource Access
	connect(ui.chkCloseForBox, SIGNAL(clicked(bool)), this, SLOT(OnAccessChanged()));
	//

	// Recovery
	connect(ui.chkAutoRecovery, SIGNAL(clicked(bool)), this, SLOT(OnRecoveryChanged()));
	connect(ui.btnAddRecovery, SIGNAL(clicked(bool)), this, SLOT(OnAddRecFolder()));
	connect(ui.btnDelRecovery, SIGNAL(clicked(bool)), this, SLOT(OnDelRecEntry()));
	connect(ui.btnAddRecIgnore, SIGNAL(clicked(bool)), this, SLOT(OnAddRecIgnore()));
	connect(ui.btnAddRecIgnoreExt, SIGNAL(clicked(bool)), this, SLOT(OnAddRecIgnoreExt()));
	connect(ui.chkShowRecoveryTmpl, SIGNAL(clicked(bool)), this, SLOT(OnShowRecoveryTmpl()));
	//

	CreateAdvanced();

	// Templates
	connect(ui.cmbCategories, SIGNAL(currentIndexChanged(int)), this, SLOT(OnFilterTemplates()));
	connect(ui.txtTemplates, SIGNAL(textChanged(const QString&)), this, SLOT(OnFilterTemplates()));
	connect(ui.treeTemplates, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(OnTemplateClicked(QTreeWidgetItem*, int)));
	connect(ui.treeTemplates, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(OnTemplateDoubleClicked(QTreeWidgetItem*, int)));
	connect(ui.btnAddTemplate, SIGNAL(clicked(bool)), this, SLOT(OnAddTemplates()));
	connect(ui.btnDelTemplate, SIGNAL(clicked(bool)), this, SLOT(OnDelTemplates()));
	connect(ui.chkScreenReaders, SIGNAL(clicked(bool)), this, SLOT(OnScreenReaders()));
	//

	connect(ui.tabs, SIGNAL(currentChanged(int)), this, SLOT(OnTab()));

	// edit
	connect(ui.btnEditIni, SIGNAL(clicked(bool)), this, SLOT(OnEditIni()));
	connect(ui.btnSaveIni, SIGNAL(clicked(bool)), this, SLOT(OnSaveIni()));
	connect(ui.btnCancelEdit, SIGNAL(clicked(bool)), this, SLOT(OnCancelEdit()));
	//

	connect(ui.buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(ok()));
	connect(ui.buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked(bool)), this, SLOT(apply()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(close()));

	if (ReadOnly)
	{
		ui.btnEditIni->setEnabled(false);
		ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
		ui.buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
	}

	if (theAPI->IsRunningAsAdmin())
	{
		ui.chkDropRights->setEnabled(false);
		ui.chkFakeElevation->setEnabled(false);
	}
	else
		ui.lblAdmin->setVisible(false);

	LoadConfig();

	ui.treeAccess->viewport()->installEventFilter(this);
	ui.treeINet->viewport()->installEventFilter(this);
	ui.treeNetFw->viewport()->installEventFilter(this);

	restoreGeometry(theConf->GetBlob("OptionsWindow/Window_Geometry"));

	QByteArray
	Columns = theConf->GetBlob("OptionsWindow/Run_Columns");
	if (!Columns.isEmpty()) ui.treeRun->header()->restoreState(Columns);
	Columns = theConf->GetBlob("OptionsWindow/AutoRun_Columns");
	if (!Columns.isEmpty()) ui.treeAutoStart->header()->restoreState(Columns);
	Columns = theConf->GetBlob("OptionsWindow/Groups_Columns");
	if (!Columns.isEmpty()) ui.treeGroups->header()->restoreState(Columns);
	Columns = theConf->GetBlob("OptionsWindow/Forced_Columns");
	if (!Columns.isEmpty()) ui.treeForced->header()->restoreState(Columns);
	Columns = theConf->GetBlob("OptionsWindow/Stop_Columns");
	if (!Columns.isEmpty()) ui.treeStop->header()->restoreState(Columns);
	Columns = theConf->GetBlob("OptionsWindow/Start_Columns");
	if (!Columns.isEmpty()) ui.treeStart->header()->restoreState(Columns);
	Columns = theConf->GetBlob("OptionsWindow/INet_Columns");
	if (!Columns.isEmpty()) ui.treeINet->header()->restoreState(Columns);
	Columns = theConf->GetBlob("OptionsWindow/NetFw_Columns");
	if (!Columns.isEmpty()) ui.treeNetFw->header()->restoreState(Columns);
	Columns = theConf->GetBlob("OptionsWindow/Access_Columns");
	if (!Columns.isEmpty()) ui.treeAccess->header()->restoreState(Columns);
	Columns = theConf->GetBlob("OptionsWindow/Recovery_Columns");
	if (!Columns.isEmpty()) ui.treeRecovery->header()->restoreState(Columns);
	Columns = theConf->GetBlob("OptionsWindow/Templates_Columns");
	if (!Columns.isEmpty()) ui.treeTemplates->header()->restoreState(Columns);
}

COptionsWindow::~COptionsWindow()
{
	theConf->SetBlob("OptionsWindow/Window_Geometry",saveGeometry());

	theConf->SetBlob("OptionsWindow/Run_Columns", ui.treeRun->header()->saveState());
	theConf->SetBlob("OptionsWindow/AutoRun_Columns", ui.treeAutoStart->header()->saveState());
	theConf->SetBlob("OptionsWindow/Groups_Columns", ui.treeGroups->header()->saveState());
	theConf->SetBlob("OptionsWindow/Forced_Columns", ui.treeForced->header()->saveState());
	theConf->SetBlob("OptionsWindow/Stop_Columns", ui.treeStop->header()->saveState());
	theConf->SetBlob("OptionsWindow/Start_Columns", ui.treeStart->header()->saveState());
	theConf->SetBlob("OptionsWindow/INet_Columns", ui.treeINet->header()->saveState());
	theConf->SetBlob("OptionsWindow/NetFw_Columns", ui.treeNetFw->header()->saveState());
	theConf->SetBlob("OptionsWindow/Access_Columns", ui.treeAccess->header()->saveState());
	theConf->SetBlob("OptionsWindow/Recovery_Columns", ui.treeRecovery->header()->saveState());
	theConf->SetBlob("OptionsWindow/Templates_Columns", ui.treeTemplates->header()->saveState());
}

void COptionsWindow::closeEvent(QCloseEvent *e)
{
	emit Closed();
	this->deleteLater();
}

bool COptionsWindow::eventFilter(QObject *source, QEvent *event)
{
	if (event->type() == QEvent::KeyPress && ((QKeyEvent*)event)->key() == Qt::Key_Escape 
		&& ((QKeyEvent*)event)->modifiers() == Qt::NoModifier)
	{
		CloseINetEdit(false);
		CloseNetFwEdit(false);
		CloseAccessEdit(false);
		return true; // cancel event
	}

	if (event->type() == QEvent::KeyPress && (((QKeyEvent*)event)->key() == Qt::Key_Enter || ((QKeyEvent*)event)->key() == Qt::Key_Return) 
		&& ((QKeyEvent*)event)->modifiers() == Qt::NoModifier)
	{
		CloseINetEdit(true);
		CloseNetFwEdit(true);
		CloseAccessEdit(true);
		return true; // cancel event
	}
	
	if (source == ui.treeAccess->viewport() && event->type() == QEvent::MouseButtonPress)
	{
		CloseAccessEdit();
	}

	if (source == ui.treeINet->viewport() && event->type() == QEvent::MouseButtonPress)
	{
		CloseINetEdit();
	}
	
	if (source == ui.treeNetFw->viewport() && event->type() == QEvent::MouseButtonPress)
	{
		CloseNetFwEdit();
	}

	return QDialog::eventFilter(source, event);
}

//void COptionsWindow::OnWithTemplates()
//{
//	m_Template = ui.chkWithTemplates->isChecked();
//	ui.buttonBox->setEnabled(!m_Template);
//	LoadConfig();
//}

void COptionsWindow::ReadAdvancedCheck(const QString& Name, QCheckBox* pCheck, const QString& Value)
{
	QString Data = m_pBox->GetText(Name, "");
	if (Data == Value)			pCheck->setCheckState(Qt::Checked);
	else if (Data.isEmpty())	pCheck->setCheckState(Qt::Unchecked);
	else						pCheck->setCheckState(Qt::PartiallyChecked);
}

void COptionsWindow::LoadConfig()
{
	m_ConfigDirty = false;

	LoadGeneral();

	LoadGroups();

	LoadForced();

	LoadStop();

	LoadStart();

	LoadINetAccess();

	LoadNetFwRules();

	LoadAccessList();

	LoadRecoveryList();

	LoadAdvanced();
	LoadDebug();

	LoadTemplates();
	
}

void COptionsWindow::WriteAdvancedCheck(QCheckBox* pCheck, const QString& Name, const QString& Value)
{
	SB_STATUS Status;
	if (pCheck->checkState() == Qt::Checked)		
		Status = m_pBox->SetText(Name, Value);
	else if (pCheck->checkState() == Qt::Unchecked) 
		Status = m_pBox->DelValue(Name);
	
	if (!Status)
		throw Status;
}

void COptionsWindow::WriteAdvancedCheck(QCheckBox* pCheck, const QString& Name, const QString& OnValue, const QString& OffValue)
{
	//if (pCheck->checkState() == Qt::PartiallyChecked)
	//	return;

	SB_STATUS Status;
	if (pCheck->checkState() == Qt::Checked)
	{
		if(!OnValue.isEmpty())
			Status = m_pBox->SetText(Name, OnValue);
		else
			Status = m_pBox->DelValue(Name);
	}
	else if (pCheck->checkState() == Qt::Unchecked)
	{
		if (!OffValue.isEmpty())
			Status = m_pBox->SetText(Name, OffValue);
		else
			Status = m_pBox->DelValue(Name);
	}

	if (!Status)
		throw Status;
}

void COptionsWindow::WriteText(const QString& Name, const QString& Value)
{
	SB_STATUS Status = m_pBox->SetText(Name, Value);
	if (!Status)
		throw Status;
}

void COptionsWindow::WriteTextList(const QString& Setting, const QStringList& List)
{
	SB_STATUS Status = m_pBox->UpdateTextList(Setting, List, m_Template);
	if (!Status)
		throw Status;
}

void COptionsWindow::SaveConfig()
{
	try
	{
		if (m_GeneralChanged)
			SaveGeneral();

		if (m_GroupsChanged)
			SaveGroups();

		if (m_ForcedChanged)
			SaveForced();

		if (m_StopChanged)
			SaveStop();

		if (m_StartChanged)
			SaveStart();

		if (m_INetBlockChanged)
			SaveINetAccess();

		if (m_NetFwRulesChanged)
			SaveNetFwRules();

		if (m_AccessChanged)
			SaveAccessList();

		if (m_RecoveryChanged)
			SaveRecoveryList();

		if (m_AdvancedChanged)
			SaveAdvanced();
		SaveDebug();

		if (m_TemplatesChanged)
			SaveTemplates();

		if (m_FoldersChanged)
			SaveFolders();
	}
	catch (SB_STATUS Status)
	{
		theGUI->CheckResults(QList<SB_STATUS>() << Status);
	}
}

void COptionsWindow::apply()
{
	if (m_pBox->GetText("Enabled").isEmpty() && !(m_Template && m_pBox->GetName().mid(9, 6).compare("Local_", Qt::CaseInsensitive) == 0)) {
		QMessageBox::critical(this, "Sandboxie-Plus", tr("This sandbox has been deleted hence configuration can not be saved."));
		return;
	}

	CloseINetEdit();
	CloseNetFwEdit();
	CloseAccessEdit();

	if (!ui.btnEditIni->isEnabled())
		SaveIniSection();
	else
		SaveConfig();

	LoadConfig();

	UpdateCurrentTab();

	emit OptionsChanged();
}

void COptionsWindow::ok()
{
	apply();

	this->close();
}

void COptionsWindow::reject()
{
	if (m_GeneralChanged
	 || m_GroupsChanged
	 || m_ForcedChanged
	 || m_StopChanged
	 || m_StartChanged
	// ||  m_RestrictionChanged
	 || m_INetBlockChanged
	 || m_AccessChanged
	 || m_TemplatesChanged
	 || m_FoldersChanged
	 || m_RecoveryChanged
	 || m_AdvancedChanged)
	{
		if (QMessageBox("Sandboxie-Plus", tr("Some changes haven't been saved yet, do you really want to close this options window?")
		, QMessageBox::Warning, QMessageBox::Yes | QMessageBox::Default, QMessageBox::No | QMessageBox::Escape, QMessageBox::NoButton, this).exec() != QMessageBox::Yes)
			return;
	}

	this->close();
}

void COptionsWindow::SetProgramItem(QString Program, QTreeWidgetItem* pItem, int Column)
{
	pItem->setData(Column, Qt::UserRole, Program);
	if (Program.left(1) == "<")
		Program = tr("Group: %1").arg(Program.mid(1, Program.length() - 2));
	else
		m_Programs.insert(Program);
	pItem->setText(Column, Program);
}

QString COptionsWindow::SelectProgram(bool bOrGroup)
{
	CComboInputDialog progDialog(this);
	progDialog.setText(tr("Enter program:"));
	progDialog.setEditable(true);

	if (bOrGroup)
	{
		for (int i = 0; i < ui.treeGroups->topLevelItemCount(); i++) {
			QTreeWidgetItem* pItem = ui.treeGroups->topLevelItem(i);
			progDialog.addItem(tr("Group: %1").arg(pItem->text(0)), pItem->data(0, Qt::UserRole).toString());
		}
	}

	foreach(const QString & Name, m_Programs)
		progDialog.addItem(Name, Name);

	progDialog.setValue("");

	if (!progDialog.exec())
		return QString();

	// Note: pressing enter adds the value to the combo list !
	QString Program = progDialog.value(); 
	int Index = progDialog.findValue(Program);
	if (Index != -1 && progDialog.data().isValid())
		Program = progDialog.data().toString();

	return Program;
}

void COptionsWindow::OnTab()
{
	if (ui.tabs->currentWidget() == ui.tabEdit)
	{
		LoadIniSection();
		ui.txtIniSection->setReadOnly(true);
	}
	else 
	{
		if (m_ConfigDirty)
			LoadConfig();

		UpdateCurrentTab();
	}
}

void COptionsWindow::UpdateCurrentTab()
{
	if (ui.tabs->currentWidget() == ui.tabStart)
	{
		if (GetAccessEntry(eIPC, "!<StartRunAccess>", eClosed, "*") != NULL)
			ui.radStartSelected->setChecked(true);
		else if (GetAccessEntry(eIPC, "<StartRunAccess>", eClosed, "*") != NULL)
			ui.radStartExcept->setChecked(true);
		else
			ui.radStartAll->setChecked(true);
		CopyGroupToList("<StartRunAccess>", ui.treeStart);

		OnRestrictStart();
	}
	else if (ui.tabs->currentWidget() == ui.tabInternet)
	{
		CheckINetBlock();

		LoadBlockINet();

		OnBlockINet();
	}
	else if (ui.tabs->currentWidget() == ui.tabAdvanced)
	{
		if (GetAccessEntry(eWnd, "", eDirect, "*") != NULL)
		{
			ui.chkNoWindowRename->setEnabled(false);
			ui.chkNoWindowRename->setChecked(true);
		}
		else
		{
			ui.chkNoWindowRename->setEnabled(true);
			ui.chkNoWindowRename->setChecked(GetAccessEntry(eWnd, "", eDirect, "#") != NULL);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Raw section ini Editot
//

void COptionsWindow::SetIniEdit(bool bEnable)
{
	for (int i = 0; i < ui.tabs->count() - 1; i++) {
		bool Enabled = ui.tabs->widget(i)->isEnabled();
		ui.tabs->setTabEnabled(i, !bEnable && Enabled);
		ui.tabs->widget(i)->setEnabled(Enabled);
	}
	ui.btnSaveIni->setEnabled(bEnable);
	ui.btnCancelEdit->setEnabled(bEnable);
	ui.txtIniSection->setReadOnly(!bEnable);
	ui.btnEditIni->setEnabled(!bEnable);
}

void COptionsWindow::OnEditIni()
{
	SetIniEdit(true);
}

void COptionsWindow::OnSaveIni()
{
	SaveIniSection();
	SetIniEdit(false);
}

void COptionsWindow::OnCancelEdit()
{
	SetIniEdit(false);
}

void COptionsWindow::LoadIniSection()
{
	QString Section;

	m_Settings = m_pBox->GetIniSection(NULL, m_Template);
	
	for (QList<QPair<QString, QString>>::const_iterator I = m_Settings.begin(); I != m_Settings.end(); ++I)
		Section += I->first + "=" + I->second + "\n";

	ui.txtIniSection->setPlainText(Section);
}

void COptionsWindow::SaveIniSection()
{
	m_ConfigDirty = true;

	// Note: an incremental update would be more elegant but it would change the entry order in the ini,
	//			hence it's better for the user to fully rebuild the section each time.
	//
	for (QList<QPair<QString, QString>>::const_iterator I = m_Settings.begin(); I != m_Settings.end(); ++I)
		m_pBox->DelValue(I->first, I->second);

	//QList<QPair<QString, QString>> NewSettings;
	//QList<QPair<QString, QString>> OldSettings = m_Settings;

	QStringList Section = SplitStr(ui.txtIniSection->toPlainText(), "\n");
	foreach(const QString& Line, Section)
	{
		if (Line.isEmpty())
			return;
		StrPair Settings = Split2(Line, "=");
		
		//if (!OldSettings.removeOne(Settings))
		//	NewSettings.append(Settings);

		m_pBox->InsertText(Settings.first, Settings.second);
	}

	//for (QList<QPair<QString, QString>>::const_iterator I = OldSettings.begin(); I != OldSettings.end(); ++I)
	//	m_pBox->DelValue(I->first, I->second);
	//
	//for (QList<QPair<QString, QString>>::const_iterator I = NewSettings.begin(); I != NewSettings.end(); ++I)
	//	m_pBox->InsertText(I->first, I->second);

	LoadIniSection();
}
