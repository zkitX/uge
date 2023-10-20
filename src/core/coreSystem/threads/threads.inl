#include "threads.h"

namespace uge
{
    // Mutex
    inline Mutex::Mutex()
    {
        ::InitializeCriticalSection( &m_critSect );
    }

    inline Mutex::~Mutex()
    {
        ::DeleteCriticalSection( &m_critSect );
    }

    inline void Mutex::Lock()
    {
        ::EnterCriticalSection( &m_critSect );
    }

    inline Bool Mutex::TryLock()
    {
        return ::TryEnterCriticalSection( &m_critSect ) != FALSE;
    }

    inline void Mutex::Unlock()
    {
        ::LeaveCriticalSection( &m_critSect );
    }

    inline void Mutex::SetSpinCount( SpinCount_t count )
    {
        (void)::SetCriticalSectionSpinCount( &m_critSect, count );
    }

    // Semaphore
    inline Semaphore::Semaphore( Int32 initialCount, Int32 maxCount )
    {
        m_semaphore = ::CreateSemaphore( nullptr, initialCount, maxCount, nullptr );
    }

    inline Semaphore::~Semaphore()
    {
        if ( m_semaphore )
        {
            ::CloseHandle( m_semaphore );
        }
    }

    inline void Semaphore::Acquire()
    {
        const WaitResult_t result = ::WaitForSingleObject( m_semaphore, INFINITE );
        assert( result != WAIT_FAILED );
    }

    inline Bool Semaphore::TryAcquire( TimeoutMs_t ms )
    {
        assert( ms != INFINITE );
        const WaitResult_t result = ::WaitForSingleObject( m_semaphore, ms );
        assert( result != WAIT_FAILED );

        return result == WAIT_OBJECT_0;
    }

    inline void Semaphore::Release(Int32 count)
    {
        ::ReleaseSemaphore( m_semaphore, count, nullptr );
    }

    inline const Semaphore_t Semaphore::Get() const
    {
        return m_semaphore;
    }

    // ConditionVariable
    inline ConditionVariable::ConditionVariable()
    {
        ::InitializeConditionVariable( &m_condition );
    }

    inline ConditionVariable::~ConditionVariable()
    {
    }

    inline void ConditionVariable::Wait( Mutex& mtx )
    {
        ::SleepConditionVariableCS( &m_condition, &mtx.m_critSect, INFINITE );
    }

    inline void ConditionVariable::WaitTimeout( Mutex& mtx, TimeoutMs_t ms )
    {
        ::SleepConditionVariableCS( &m_condition, &mtx.m_critSect, ms );
    }

    inline void ConditionVariable::WakeAny()
    {
        ::WakeConditionVariable( &m_condition );
    }

    inline void ConditionVariable::WakeAll()
    {
        ::WakeAllConditionVariable( &m_condition );
    }


}
