#include <QtWidgets/QApplication>
#include "windows_manage.h"
#include <windows.h>
#include <DbgHelp.h>
#include "ctp_beep.h"
#pragma comment(lib,"Dbghelp.lib")

long  __stdcall CrashInfocallback(_EXCEPTION_POINTERS* pexcp)
{
    //创建 Dump 文件
    HANDLE hDumpFile = ::CreateFile(
        L"MEMORY.DMP",
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hDumpFile != INVALID_HANDLE_VALUE)
    {
        //Dump信息
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pexcp;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;
        //写入Dump文件内容
        ::MiniDumpWriteDump(
            GetCurrentProcess(),
            GetCurrentProcessId(),
            hDumpFile,
            MiniDumpNormal,
            &dumpInfo,
            NULL,
            NULL
        );
    }
    return 0;
}


extern void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);

int main(int argc, char* argv[])
{
    ::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CrashInfocallback);
    qInstallMessageHandler(myMessageOutput);
    ctp_beep_init();
    QApplication a(argc, argv);
    windows_manage w(0);

    return a.exec();
}
