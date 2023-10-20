#include "build.h"

#include <DbgHelp.h>
#include "CStackTrace.h"

namespace uge
{
    namespace dbg
    {
        CStackTrace::CStackTrace()
        {
            Reset();
        }

        Bool CStackTrace::Init()
        {
            m_hProcess = GetCurrentProcess();
            m_hThread = GetCurrentThread();
            const DWORD tid = ::GetThreadId(m_hThread);
            if (tid == 0)
            {
                return false;
            }
            else if (tid == ::GetCurrentThreadId())
            {
                m_isCurrentThread = true;
            }

            if (!m_isCurrentThread)
            {
                const DWORD suspendCount = ::SuspendThread(m_hThread);
                if (suspendCount == static_cast<DWORD>(-1))
                {
                    // TODO: Trace failed to suspend thread
                    return false;
                }
            }

            DWORD symFlags = SYMOPT_FAIL_CRITICAL_ERRORS | SYMOPT_UNDNAME | SYMOPT_LOAD_LINES | SYMOPT_NO_PROMPTS;

            SymSetOptions(symFlags);

            if (!SymInitialize(m_hProcess, nullptr, TRUE))
            {
                // TODO: Trace failed to initialize symbols
                return false;
            }
            return true;
        }

        void CStackTrace::Reset()
        {
            if (m_hProcess != 0)
            {
                SymCleanup(m_hProcess);
            }

            if (m_isCurrentThread == false && m_hThread != 0)
            {
                ::ResumeThread(m_hThread);
            }

            m_hProcess = 0;
            m_hThread = 0;
            m_inStackTrace = false;
            m_isCurrentThread = false;
            memset(&m_tContext, 0, sizeof(m_tContext));
            memset(&m_stackFrame, 0, sizeof(m_stackFrame));
            memset(&m_addrInfo, 0, sizeof(m_addrInfo));
        }

        void CStackTrace::PrintStackTrace()
        {
            /*
            fprintf(stdout, "!!!!! STACKTRACE !!!!!\n");
            for (UInt32 i = 0; i < m_addrInfo.m_numFrameAddresses; ++i)
            {
                AddressInfo *currentAddr = &m_addrInfo.m_frameAddresses[i];
                fprintf(stdout, "%2d : %016llX %s:%d : %s\n", i, currentAddr->address, currentAddr->functionName, currentAddr->linePos, currentAddr->fileName);
            }
            */
        }

        inline Bool CStackTrace::GetNameInfo(AddressInfo *addrInfo, SYMBOL_INFO *symbols)
        {
            DWORD64 dwDisplacement;

            if (SymFromAddr(m_hProcess, addrInfo->m_address, &dwDisplacement, symbols))
            {
                addrInfo->m_functionDisplacement = dwDisplacement;
                uge::Strcpy( addrInfo->m_functionName, symbols->Name, MAX_FUNCNAME_LEN );
                return true;
            }
            else
            {
                return false;
            }
        }

        inline Bool CStackTrace::GetLineInfo(AddressInfo *addrInfo)
        {
            IMAGEHLP_LINE64 line;
            DWORD dwDisplacement;

            memset(&line, 0, sizeof(line));
            line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

            if (SymGetLineFromAddr64(m_hProcess, addrInfo->m_address, &dwDisplacement, &line))
            {
                addrInfo->m_lineDisplacement = dwDisplacement;
                addrInfo->m_linePos = line.LineNumber;
                uge::Strcpy( addrInfo->m_fileName, line.FileName, MAX_FILENAME_LEN );
                return true;
            }
            else
            {
                return false;
            }
        }

        Bool CStackTrace::GetFullStackFrame()
        {
            Bool ok = Init();
            if (!ok)
            {
                return false;
            }

            if (m_isCurrentThread)
            {
                ::RtlCaptureContext(&m_tContext);
            }
            else
            {
                if (!::GetThreadContext(m_hThread, &m_tContext))
                {
                    ::ResumeThread(m_hThread);
                    return false;
                }
            }

            m_stackFrame.AddrStack.Mode = m_stackFrame.AddrPC.Mode = m_stackFrame.AddrFrame.Mode = m_stackFrame.AddrReturn.Mode = AddrModeFlat;
            m_stackFrame.AddrPC.Offset = m_tContext.Rip;
            m_stackFrame.AddrReturn.Offset = m_tContext.Rip;
            m_stackFrame.AddrFrame.Offset = m_tContext.Rbp;
            m_stackFrame.AddrStack.Offset = m_tContext.Rsp;

            SYMBOL_INFO *symbolInfo = static_cast<SYMBOL_INFO *>(malloc(sizeof(SYMBOL_INFO) + MAX_SYM_NAME));
            if (symbolInfo == NULL)
            {
                return false;
            }
            memset(symbolInfo, 0, sizeof(symbolInfo) + MAX_SYM_NAME);

            for (UInt32 i = 0; i < MAX_STACK_TRACE_FRAMES; ++i)
            {
                ok = StackWalk64(
                    IMAGE_FILE_MACHINE_AMD64,
                    m_hProcess,
                    m_hThread,
                    &m_stackFrame,
                    &m_tContext,
                    nullptr,
                    SymFunctionTableAccess64,
                    SymGetModuleBase64,
                    nullptr);
                if (!ok)
                {
                    // TODO: log finished
                    break;
                }

                symbolInfo->SizeOfStruct = sizeof(SYMBOL_INFO);
                symbolInfo->MaxNameLen = MAX_SYM_NAME;

                UInt64 address = (UInt64)m_stackFrame.AddrPC.Offset;
                AddressInfo *currentAddress = &m_addrInfo.m_frameAddresses[i];

                currentAddress->m_address = address;

                ok = ok && GetNameInfo(currentAddress, symbolInfo);
                ok = ok && GetLineInfo(currentAddress);
                ++m_addrInfo.m_numFrameAddresses;
            }

            return true;
        }
    }
}
