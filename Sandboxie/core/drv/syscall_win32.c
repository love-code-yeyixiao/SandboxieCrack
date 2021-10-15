/*
 * Copyright 2020-2021 David Xanatos, xanasoft.com
 *
 * This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//---------------------------------------------------------------------------
// Syscall Management
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------


static BOOLEAN Syscall_Init_List32(void);

static BOOLEAN Syscall_Init_Table32(void);


//---------------------------------------------------------------------------


static NTSTATUS Syscall_Api_Query32(PROCESS *proc, ULONG64 *parms);

static NTSTATUS Syscall_Api_Invoke32(PROCESS *proc, ULONG64 *parms);


//---------------------------------------------------------------------------


#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, Syscall_Init_List32)
#pragma alloc_text (INIT, Syscall_Init_Table32)
#endif // ALLOC_PRAGMA



//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------


static LIST Syscall_List32;

static SYSCALL_ENTRY **Syscall_Table32 = NULL;

ULONG Syscall_MaxIndex32 = 0;




//---------------------------------------------------------------------------
// Syscall_GetWin32kAddr
//---------------------------------------------------------------------------

//struct _EX_FAST_REF
//{
//    void *Object;
//    unsigned long RefCnt:3;
//    unsigned long Value;
//};
//
//struct _EX_CALLBACK
//{
//    struct _EX_FAST_REF RoutineBlock;
//};
//
//struct _PS_WIN32K_GLOBALS
//{
//    struct _EX_CALLBACK Win32CallBack;
//    struct _KSERVICE_TABLE_DESCRIPTOR ServiceDescriptorTableShadow[2];
//    struct _KSERVICE_TABLE_DESCRIPTOR ServiceDescriptorTableFilter[2];
//};

typedef struct _KSERVICE_TABLE_DESCRIPTOR
{
    unsigned long *Base;
    unsigned long *Reserved1;
    unsigned long Limit;
    unsigned int *Number;
} KSERVICE_TABLE_DESCRIPTOR, *PKSERVICE_TABLE_DESCRIPTOR ;


_FX BOOLEAN Syscall_GetWin32kAddr(ULONG *Base_Copy, 
    ULONG index, void **pKernelAddr, ULONG *pParamCount)
{
    KSERVICE_TABLE_DESCRIPTOR *ShadowTable = (KSERVICE_TABLE_DESCRIPTOR *)Syscall_GetServiceTable();
    ShadowTable += 1; // ServiceDescriptorTableShadow[0] -> ntoskrnl.exe, ServiceDescriptorTableShadow[1] -> win32k.sys

    if (ShadowTable) {

        ULONG MaxSyscallIndexPlusOne = ShadowTable->Limit;
        if ((index >= 0x1000) &&
                    ((index & 0xFFF) < MaxSyscallIndexPlusOne)) {

            long EntryValue = Base_Copy[index & 0xFFF];

            *pKernelAddr = (UCHAR *)ShadowTable->Base + (EntryValue >> 4);
            *pParamCount = (ULONG)(EntryValue & 0x0F) + 4;
            //DbgPrint("    SysCall32 offset: %d\r\n", (ULONG)(EntryValue >> 4));
            return TRUE;
        }

        Log_Msg1(MSG_1113, L"ADDRESS");
    }

    return FALSE;
}


//---------------------------------------------------------------------------
// Syscall_Init_List32
//---------------------------------------------------------------------------


_FX BOOLEAN Syscall_Init_List32(void)
{
    UCHAR *name, *win32k_code;
    void *ntos_addr;
    DLL_ENTRY *dll;
    SYSCALL_ENTRY *entry;
    ULONG proc_index, proc_offset, syscall_index, param_count;
    ULONG name_len, entry_len;


    KSERVICE_TABLE_DESCRIPTOR *ShadowTable = (KSERVICE_TABLE_DESCRIPTOR *)Syscall_GetServiceTable();
    if (!ShadowTable) {
        Log_Msg1(MSG_1113, L"SHADOW_TABLE");
        return FALSE;
    }
    //DbgPrint(" win32k.sys SysCalls: %d %p %p\n", ShadowTable->Limit, ShadowTable->Base, ShadowTable->Number);
    ShadowTable += 1;
    //DbgPrint(" win32k.sys SysCalls: %d %p %p\n", ShadowTable->Limit, ShadowTable->Base, ShadowTable->Number);

    if (ShadowTable->Limit > 0xFFF) { // not plausible
        Log_Msg1(MSG_1113, L"SHADOW_TABLE");
        return FALSE;
    }
    
    //
    // We can not read ShadowTable->Base bemory, without being in a GUI thread
    // hence we grab csrss.exe and attache to it, create a copy of this memory
    // and use it in the loop below instead
    //

    HANDLE csrssId = Util_GetProcessPidByName(L"csrss.exe");
    if (csrssId == (HANDLE)-1) {
        Log_Msg1(MSG_1113, L"csrss.exe");
        return FALSE;
    }

    ULONG* table_copy = (ULONG*)Mem_AllocEx(Driver_Pool, ShadowTable->Limit * sizeof(long), TRUE);
    if (!table_copy) 
        return FALSE;

    BOOLEAN success = FALSE;

    PEPROCESS ProcessObject;
    if (NT_SUCCESS(PsLookupProcessByProcessId(csrssId,&ProcessObject))) {
        KAPC_STATE ApcState;
        KeStackAttachProcess(ProcessObject, &ApcState);
        if (MmIsAddressValid(ShadowTable->Base)) {
            memcpy(table_copy, ShadowTable->Base, ShadowTable->Limit * sizeof(long));
            success = TRUE;
        }
        KeUnstackDetachProcess(&ApcState);
        ObDereferenceObject(ProcessObject);
    }

    if (!success) {
        Log_Msg1(MSG_1113, L"WIN32K_TABLE");
        return FALSE;
    }
    
    //
    // ready
    //

    List_Init(&Syscall_List32);

    //
    // scan each NtXxx export in WIN32U
    //

    dll = Dll_Load(L"WIN32U");
    if (! dll)
        return FALSE;

    proc_offset = Dll_GetNextProc(dll, "Nt", &name, &proc_index);
    if (! proc_offset)
        return FALSE;

    while (proc_offset) {

        if (name[0] != 'N' || name[1] != 't')
            break;
        name += 2;                  // skip Nt prefix
        for (name_len = 0; (name_len < 64) && name[name_len]; ++name_len)
            ;
        
        //DbgPrint("    Found SysCall32 %s\n", name);

        entry = NULL;

        //
        // we don't hook UserCreateWindowEx as it uses callbacks into
        // user space from teh kernel, for ocne this dies not play well 
        // with out sys call interface, but also it would be a security issue
        // to allow user code execution while we have restored the original token
        //

        #define IS_PROC_NAME(ln,nm) (name_len == ln && memcmp(name, nm, ln) == 0)

        if (    IS_PROC_NAME(18, "UserCreateWindowEx")
            ||  IS_PROC_NAME( 7, "GdiInit") // bsod
            ||  IS_PROC_NAME(12, "GdiInitSpool") // probably too
            ||  IS_PROC_NAME(20, "UserSetThreadDesktop") // bsod
            
                                                            ) {
            goto next_ntxxx;
        }

        //
        // analyze each NtXxx export to find the service index number
        //

        ntos_addr = NULL;
        param_count = 0;

        win32k_code = Dll_RvaToAddr(dll, proc_offset);
        if (win32k_code) {

            syscall_index =
                Syscall_GetIndexFromNtdll(win32k_code, name, name_len);

            if (syscall_index == -2) {
                //
                // if ZwXxx export is not a real syscall, then skip it
                //
                goto next_ntxxx;
            }

            if (syscall_index != -1) {

                Syscall_GetWin32kAddr(table_copy,
                            syscall_index, &ntos_addr, &param_count);

                //BOOLEAN test;
                //KeStackAttachProcess(pProcess, &ApcState);
                //test = MmIsAddressValid(ntos_addr);
                //KeUnstackDetachProcess(&ApcState);
                //DbgPrint("    Found SysCall32: %s, pcnt %d; idx: %d; addr: %p %s\r\n", name, param_count, syscall_index, ntos_addr, test ? "valid" : "invalid");
                //DbgPrint("    Found SysCall32: %s, pcnt %d; idx: %d\r\n", name, param_count, syscall_index);
            }
        }

        if (! ntos_addr) {
            Syscall_ErrorForAsciiName(name);
            return FALSE;
        }

        syscall_index = (syscall_index & 0xFFF);

        //
        // store an entry for the syscall in our list of syscalls
        //

        entry_len = sizeof(SYSCALL_ENTRY) + name_len + 1;
        entry = Mem_AllocEx(Driver_Pool, entry_len, TRUE);
        if (!entry) {
            Syscall_MaxIndex32 = 0;
            return FALSE;
        }

        entry->syscall_index = (USHORT)syscall_index;
        entry->param_count = (USHORT)param_count;
        entry->ntdll_offset = proc_offset;
        entry->ntos_func = ntos_addr;
        entry->handler1_func = NULL;
        entry->handler2_func = NULL;
        entry->handler3_func_support_procmon = NULL;
        entry->name_len = (USHORT)name_len;
        memcpy(entry->name, name, name_len);
        entry->name[name_len] = '\0';

        List_Insert_After(&Syscall_List32, NULL, entry);

        if (syscall_index > Syscall_MaxIndex32)
            Syscall_MaxIndex32 = syscall_index;

        //
        // process next ZwXxx export
        //
        
next_ntxxx:

        proc_offset = Dll_GetNextProc(dll, NULL, &name, &proc_index);

    }

    //DbgPrint("Found %d win32 SysCalls\n", Syscall_MaxIndex32);

    //
    // report an error if we did not find a reasonable number of services
    //

    if (Syscall_MaxIndex32 < 100) {
        Log_Msg1(MSG_1113, L"100");
        Syscall_MaxIndex32 = 0;
        return FALSE;
    }

    if (Syscall_MaxIndex32 >= 2000) {
        Log_Msg1(MSG_1113, L"2000");
        Syscall_MaxIndex32 = 0;
        return FALSE;
    }

    Mem_Free(table_copy, ShadowTable->Limit * sizeof(long));

    return TRUE;
}


//---------------------------------------------------------------------------
// Syscall_Init_Table32
//---------------------------------------------------------------------------


_FX BOOLEAN Syscall_Init_Table32(void)
{
    SYSCALL_ENTRY *entry;
    ULONG len, i;

    //
    // build the table which maps syscall index numbers to entries
    //

    len = sizeof(SYSCALL_ENTRY *) * (Syscall_MaxIndex32 + 1);
    Syscall_Table32 = Mem_AllocEx(Driver_Pool, len, TRUE);
    if (! Syscall_Table32)
        return FALSE;

    for (i = 0; i <= Syscall_MaxIndex32; ++i) {

        entry = List_Head(&Syscall_List32);
        while (entry) {
            if (entry->syscall_index == i)
                break;
            entry = List_Next(entry);
        }

        Syscall_Table32[i] = entry;
    }

    return TRUE;
}


//---------------------------------------------------------------------------
// Syscall_Api_Invoke32
//---------------------------------------------------------------------------

extern unsigned int g_TrapFrameOffset;

_FX NTSTATUS Syscall_Api_Invoke32(PROCESS* proc, ULONG64* parms)
{
    ULONG_PTR *user_args;
    SYSCALL_ENTRY *entry;
    ULONG syscall_index;
    NTSTATUS status;
#ifdef _WIN64
    volatile ULONG_PTR ret = 0;
    volatile ULONG_PTR UserStack = 0;

    volatile PETHREAD pThread = PsGetCurrentThread();
    volatile PKTRAP_FRAME pTrapFrame = NULL;
#endif

    //
    // caller must be sandboxed and service index must be known
    //

    if (! proc)
        return STATUS_NOT_IMPLEMENTED;

    syscall_index = (ULONG)parms[1];

    syscall_index = (syscall_index & 0xFFF);

    //DbgPrint("[syscall] request for service %d / %08X\n", syscall_index, syscall_index);

    if (Syscall_Table32 && (syscall_index <= Syscall_MaxIndex32))
        entry = Syscall_Table32[syscall_index];
    else
        entry = NULL;

    if (! entry)
        return STATUS_INVALID_SYSTEM_SERVICE;

    //DbgPrint("[syscall] request %s\n", entry->name);

    // DbgPrint("[syscall] request p=%06d t=%06d - BEGIN %s\n", PsGetCurrentProcessId(), PsGetCurrentThreadId(), entry->name);

//    Thread_SetThreadToken(proc);        // may set proc->terminated

//    if (proc->terminated) {
//
//        Process_TerminateProcess(proc);
//        return STATUS_PROCESS_IS_TERMINATING;
//    }


    //
    // on first win32k.sys call we must convert this thread to a GUI thread
    //

    // todo: call KiConvertToGuiThread() or PsConvertToGuiThread()

    //
    // if we have a handler for this service, invoke it
    //

    user_args = (ULONG_PTR *)parms[2];

    __try {

        BOOLEAN traced = FALSE;
        const ULONG args_len = entry->param_count * sizeof(ULONG_PTR);
#ifdef _WIN64
        ProbeForRead(user_args, args_len, sizeof(ULONG_PTR));

        // default - support procmon stack if handler3_func_support_procmon is null.
        if (!entry->handler3_func_support_procmon
            || entry->handler3_func_support_procmon(proc, entry, user_args)
            )
        {
            if (g_TrapFrameOffset) {

                pTrapFrame = (PKTRAP_FRAME) *(ULONG_PTR*)((UCHAR*)pThread + g_TrapFrameOffset);
                if (pTrapFrame) {
                    ret = pTrapFrame->Rip;
                    UserStack = pTrapFrame->Rsp;
                    pTrapFrame->Rsp = pTrapFrame->Rbp; //*pRbp;
                    pTrapFrame->Rip = pTrapFrame->Rbx; //*pRbx;
                }
            }
            else
            {
                pTrapFrame = NULL;
            }
        }
        else
        {
            pTrapFrame = NULL;
        }

#else ! _WIN64
        ProbeForRead(user_args, args_len, sizeof(UCHAR));
#endif _WIN64

        if (entry->handler1_func) {

            status = entry->handler1_func(proc, entry, user_args);

        } else {

            if (MmIsAddressValid(entry->ntos_func)) {

                //DbgPrint("   SysCall32 %d -> %p\r\n", syscall_index, entry->ntos_func);
                status = Syscall_Invoke(entry, user_args);

            } else {

                status = STATUS_INVALID_ADDRESS;

            }
        }

        if (!traced && ((proc->call_trace & TRACE_ALLOW) || ((status != STATUS_SUCCESS) && (proc->call_trace & TRACE_DENY))))
        {
            WCHAR trace_str[128];
            RtlStringCbPrintfW(trace_str, sizeof(trace_str), L"[syscall32] %.*S, status = 0x%X", //59 chars + entry->name
                max(strlen(entry->name), 64), entry->name,
                status);
            const WCHAR* strings[2] = { trace_str, NULL };
            Session_MonitorPutEx(MONITOR_SYSCALL | MONITOR_TRACE, strings, NULL, PsGetCurrentProcessId(), PsGetCurrentThreadId());
        }

#ifdef _WIN64
        if (g_TrapFrameOffset) {
            if (pTrapFrame) {
                pTrapFrame->Rip = ret;
                pTrapFrame->Rsp = UserStack;
            }
        }
#endif

    } __except (EXCEPTION_EXECUTE_HANDLER) {
        status = GetExceptionCode();
    }


//    if (proc->terminated) {
//
//        Process_TerminateProcess(proc);
//        return STATUS_PROCESS_IS_TERMINATING;
//    }

    //
    // clear any thread impersonation set during the syscall, to restore
    // use of the highly restricted primary token in this thread
    //

//    Thread_ClearThreadToken();

    /*if (! NT_SUCCESS(status)) {
        DbgPrint("Process %06d Syscall %04X Status %08X\n", proc->pid, syscall_index, status);
    }*/

    return status;
}


//---------------------------------------------------------------------------
// Syscall_Api_Query32
//---------------------------------------------------------------------------


_FX NTSTATUS Syscall_Api_Query32(PROCESS *proc, ULONG64 *parms)
{
    ULONG buf_len;
    ULONG *user_buf;
    ULONG *ptr;
    SYSCALL_ENTRY *entry;

    //
    // allocate user mode space for syscall table
    //

    buf_len = sizeof(ULONG)         // size of buffer
            + List_Count(&Syscall_List32) * sizeof(ULONG) * 2
            + sizeof(ULONG) * 2     // final terminator entry
            ;

    user_buf = (ULONG *)parms[1];

    ProbeForWrite(user_buf, buf_len, sizeof(ULONG));

    //
    // populate the buffer with syscall data.  first we store
    // the size of the buffer, and then we leave room for ULONG used
    // by SbieSvc, and for the code for four ZwXxx stub functions
    //

    ptr = user_buf;
    *ptr = buf_len;
    ++ptr;

    //
    // store service index number and (only on 32-bit Windows) also
    // the parameter count for each syscall into one ULONG.
    // store corresponding offset within ntdll into the other ULONG
    //

    entry = List_Head(&Syscall_List32);
    while (entry) {

        ULONG syscall_index = (ULONG)entry->syscall_index;
#ifndef _WIN64
        ULONG param_count = (ULONG)entry->param_count;
        syscall_index |= (param_count * 4) << 24;
#endif ! _WIN64

        *ptr = syscall_index;
        ++ptr;
        *ptr = entry->ntdll_offset;
        ++ptr;

        entry = List_Next(entry);
    }

    //
    // store a final zero terminator entry and return successfully
    //

    *ptr = 0;
    ++ptr;
    *ptr = 0;

    return STATUS_SUCCESS;
}

