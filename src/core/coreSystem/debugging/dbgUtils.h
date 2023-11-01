#ifndef __CORESYSTEM_DBGUTILS_H__
#define __CORESYSTEM_DBGUTILS_H__

namespace uge
{
    namespace dbg
    {
        typedef HANDLE hProcess_t;
        typedef HANDLE hThread_t;
        typedef CONTEXT Context_t;

        enum EAssertType
        {
            AssertType_None,
            AssertType_Assert,
            AssertType_Sanity
        };  

        class CTrace
        {
            private:
                enum { BUFFER_SIZE = 4096 };
            public:
                CTrace();
                ~CTrace();
                void Trace( const AnsiChar* msg, ...);
                void Trace( const AnsiChar* msg, va_list argList );
            protected:
                void ClearBuffer();

            protected:
                FILE*            traceFile;
                AnsiChar         buffer[ BUFFER_SIZE ];
        };

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

        protected:
            Bool Init();
            void Reset();
            inline Bool GetNameInfo(AddressInfo *addrInfo, SYMBOL_INFO *symbols);
            inline Bool GetLineInfo(AddressInfo *addrInfo);

        public:
            CStackTrace();
            void PrintStackTrace();
            Bool GetFullStackFrame();

            const SStackTrace& getStackTrace() const;
            const SStackTrace& getStackTrace();

        protected:
            // Are we already in a stacktrace?
            Bool                m_inStackTrace;

            // Are we the current thread?
            Bool                m_isCurrentThread;

            // Handle to our process
            hProcess_t          m_hProcess;

            // Handle to our thread
            hThread_t           m_hThread;

            // Context for the thread we are walking the stack of
            Context_t           m_tContext;

            STACKFRAME64        m_stackFrame;

            // All of our stack info
            SStackTrace         m_addrInfo;
        };

        class CAssert
        {
        public:
            CAssert()
                : m_assertType( AssertType_None ),
                  m_isHandlingAssert( false )
            {
            }
            void OnAssert( const AnsiChar* filename, UInt32 line, const AnsiChar* expression, const AnsiChar* message, ... );

        protected:
            friend class CStackTrace;
            AnsiChar m_buffer[1024];
            EAssertType m_assertType;
            Bool m_isHandlingAssert;
        };

        extern CAssert g_assert;
        extern CTrace g_trace;
    }
}

#ifdef UGE_ASSERTS_ENABLED
    #define UGE_ASSERT(cond, msg, ...)\
        do {\
            if ( !(cond) ) {\
                uge::dbg::g_assert.OnAssert( __FILE__, __LINE__, #cond, msg, ##__VA_ARGS__ );\
                __debugbreak();\
            }\
        } while ( (void)0, 0 )

    #define UGE_VERIFY(expr, msg, ...)\
        do {\
            if ( !(expr) ) {\
                UGE_LOG_ERROR( "%hs: " msg, #expr, ##__VA_ARGS__ );\
                __debugbreak();\
            }\
        } while ( (void)0, 0 )

    #define UGE_TRACE(msg, ...)\
        do {\
            uge::dbg::g_trace.Trace( msg, ##__VA_ARGS__ );\
        } while ( (void)0, 0 )

    #define UGE_CHECK_WINAPI(expr) \
        do { \
            Bool result = ((expr) != 0); \
            DWORD error = GetLastError(); \
            UGE_ASSERT( result, #expr, "\nGetLastError() result: 0x%08X", error ); \
        } while (0)

#else
    #define UGE_ASSERT(cond, msg, ...) do {} while( (void)0, 0) )
    #define UGE_VERIFY(expr, msg, ...) do { if ( !(expr) ) {} } while ( (void)0, 0)
#endif

#endif  // __CORESYSTEM_DBGUTILS_H__