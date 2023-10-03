#include "threads.h"

namespace uge
{
    void Thread_Yield()
    {
        (void)::SwitchToThread();
    }

    void Thread_Sleep( TimeoutMs_t ms )
    {
        ::Sleep( ms );
    }

    void Thread_SetAffinity( AffinityMask_t affinityMask )
    {
        if ( affinityMask != 0 )
        {
            ::SetThreadAffinityMask( GetCurrentThread(), affinityMask );
        }
    }

    // https://learn.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2015/debugger/how-to-set-a-thread-name-in-native-code?view=vs-2015
    constexpr DWORD MS_VC_EXCEPTION = 0x406D1388;
    constexpr DWORD g_CallerThread = (DWORD)-1;
#pragma pack(push,8)  
    typedef struct tagTHREADNAME_INFO
    {
        DWORD dwType; // Must be 0x1000.  
        LPCSTR szName; // Pointer to name (in user addr space).  
        DWORD dwThreadID; // Thread ID (-1=caller thread).  
        DWORD dwFlags; // Reserved for future use, must be zero.  
    } THREADNAME_INFO;
#pragma pack(pop)
    void Thread_SetName( const AnsiChar* threadName )
    {
        if ( !threadName )
        {
            return;
        }

        THREADNAME_INFO info;
        info.dwType = 0x1000;
        info.szName = threadName;
        info.dwThreadID = g_CallerThread;
        info.dwFlags = 0;
#pragma warning(push)  
#pragma warning(disable: 6320 6322)  
        __try
        {
            RaiseException( MS_VC_EXCEPTION, 0, sizeof( info ) / sizeof( ULONG_PTR ), (ULONG_PTR*)&info );
        }
        __except ( EXCEPTION_EXECUTE_HANDLER )
        {
        }
#pragma warning(pop) 
    }

#pragma warning(push)  
#pragma warning(disable: 6387)  
    void Thread_Suspend( ThreadId id )
    {
        DWORD threadId = static_cast<DWORD>(id.Get());

        // We can't suspend the current thread
        assert( threadId != GetCurrentThreadId() );

        Thread_t thread = OpenThread( THREAD_SUSPEND_RESUME, FALSE, threadId );
        if ( thread != INVALID_HANDLE_VALUE )
        {
            SuspendThread( thread );
            CloseHandle( thread );
        }
    }
    void Thread_Resume( ThreadId id )
    {
        DWORD threadId = static_cast<DWORD>(id.Get());
        Thread_t thread = OpenThread( THREAD_SUSPEND_RESUME, FALSE, threadId );
        if ( thread != INVALID_HANDLE_VALUE )
        {
            ResumeThread( thread );
            CloseHandle( thread );
        }
    }
#pragma warning(pop)
}