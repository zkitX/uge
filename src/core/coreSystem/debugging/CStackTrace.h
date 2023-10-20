#ifndef __CORESYSTEM_CSTACKTRACE_H__
#define __CORESYSTEM_CSTACKTRACE_H__

namespace uge
{
    namespace dbg
    {
        typedef HANDLE hProcess_t;
        typedef HANDLE hThread_t;
        typedef CONTEXT Context_t;

        class CStackTrace
        {
        private:
            enum { MAX_STACK_TRACE_FRAMES = 128, MAX_FILENAME_LEN = 256, MAX_FUNCNAME_LEN = 256 };
            struct AddressInfo
            {
                char m_fileName[MAX_FILENAME_LEN];
                char m_functionName[MAX_FUNCNAME_LEN];
                UInt64 m_functionDisplacement;
                UInt32 m_linePos;
                UInt32 m_lineDisplacement;
                UInt64 m_address;
            };

            struct SStackTrace
            {
                AddressInfo m_frameAddresses[MAX_STACK_TRACE_FRAMES];
                UInt32 m_numFrameAddresses;
            };
            ;

        public:
            CStackTrace();
            Bool Init();
            void Reset();
            void PrintStackTrace();
            inline Bool GetNameInfo(AddressInfo *addrInfo, SYMBOL_INFO *symbols);
            inline Bool GetLineInfo(AddressInfo *addrInfo);
            Bool GetFullStackFrame();

        protected:
            // Are we already in a stacktrace?
            Bool m_inStackTrace;

            // Are we the current thread?
            Bool m_isCurrentThread;

            // Handle to our process
            hProcess_t m_hProcess;

            // Handle to our thread
            hThread_t m_hThread;

            // Context for the thread we are walking the stack of
            Context_t m_tContext;

            STACKFRAME64 m_stackFrame;

            // All of our stack info
            SStackTrace m_addrInfo;
        };
    }
}

#endif