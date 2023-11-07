#include "threads.h"

namespace uge
{
    /**
     * @brief Yields the current thread's time slice to another thread that is ready to run on the current processor.
     * 
     */
    void Thread_Yield()
    {
        (void)::SwitchToThread();
    }

    /**
     * @brief Suspends the execution of the current thread for a specified amount of time.
     * 
     * @param ms The time, in milliseconds, for which to suspend the execution of the current thread.
     */
    void Thread_Sleep( TimeoutMs_t ms )
    {
        ::Sleep( ms );
    }

    /**
     * @brief Sets the affinity mask for the current thread.
     * 
     * @param affinityMask The affinity mask to set for the current thread.
     */
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

        THREADNAME_INFO info{};
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

    /**
     * @brief Suspends the execution of the specified thread.
     * 
     * @param id The ID of the thread to suspend.
     */
    void Thread_Suspend( ThreadId id )
    {
        DWORD threadId = static_cast<DWORD>(id.Get());

        // We can't suspend the current thread
        UGE_ASSERT( threadId != GetCurrentThreadId(), "Unable to suspend current thread!" );

        Thread_t thread = OpenThread( THREAD_SUSPEND_RESUME, FALSE, threadId );
        if ( thread != INVALID_HANDLE_VALUE )
        {
            SuspendThread( thread );
            CloseHandle( thread );
        }
    }
    
    /**
     * @brief Resumes a previously suspended thread.
     * 
     * @param id The ID of the thread to be resumed.
     */
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

    static UInt32 UGE_STDCALL ThreadEntry( void* userData )
    {
        Thread* thread = reinterpret_cast<Thread*>(userData);
        UGE_ASSERT( thread, "Thread is null!" );
        
        if (thread)
        {
            Thread_SetName( thread->GetThreadName() );
            ::CoInitializeEx( nullptr, COINIT_MULTITHREADED );
            thread->ThreadFunc();
        }

        return 0;
    }

    Thread::Thread(const AnsiChar *threadName, const UInt32 stackSize)
        : m_stackSize( stackSize )
        , m_thread()
    {
        UGE_ASSERT( threadName, "Thread name cannot be null!" );
        UGE_ASSERT( Strlen( threadName ) <= g_MaxThreadNameLength, "Thread name cannot be longer than %d characters!", g_MaxThreadNameLength );

        Strcpy( m_threadName, threadName, g_MaxThreadNameLength );
    }

    Thread::~Thread()
    {
    }

    void Thread::Join()
    {
        if ( IsValid() )
        {
            const WaitResult_t result = WaitForSingleObject( m_thread, INFINITE );
            UGE_ASSERT( result == WAIT_OBJECT_0, "Failed to wait for thread!" );
            ::CloseHandle( m_thread );
            m_thread = HANDLE();
        }
    }

    void Thread::Detach()
    {
        if ( IsValid() )
        {
            ::CloseHandle( m_thread );
            m_thread = HANDLE();
        }
    }

    void Thread::Init()
    {
        UGE_ASSERT( !IsValid(), "Thread already started!" );

        const UInt32 flags = CREATE_SUSPENDED | STACK_SIZE_PARAM_IS_A_RESERVATION;

        m_thread = reinterpret_cast<Thread_t>(::_beginthreadex( nullptr, m_stackSize, ThreadEntry, this, 0, nullptr ));
        UGE_ASSERT( m_thread != INVALID_HANDLE_VALUE, "Failed to create thread!" );

        Int32 priority = Normal;
        ::SetThreadPriority( m_thread, priority );
        ::ResumeThread( m_thread );
    }

    void Thread::SetAffinityMask(AffinityMask_t mask)
    {
        UGE_ASSERT( IsValid(), "Thread is not valid!" );

        if ( IsValid() )
        {
            UGE_CHECK_WINAPI(::SetThreadAffinityMask( m_thread, mask ));
        }
    }

    void Thread::SetPriority(EThreadPriority threadPriority)
    {
        UGE_ASSERT( IsValid(), "Thread is not valid!" );

        if (IsValid())
        {
            UGE_CHECK_WINAPI(::SetThreadPriority( m_thread, threadPriority ));
        }
    }
    void Thread::SetPriorityBoost(Bool disablePriorityBoost)
    {
        UGE_ASSERT( IsValid(), "Thread is not valid!" );

        if ( IsValid() )
        {
            UGE_CHECK_WINAPI(::SetThreadPriorityBoost( m_thread, disablePriorityBoost ));
        }
    }
}