#include "threads.h"

namespace uge
{
    template<typename TLockType>
    inline ScopedLock<TLockType>::ScopedLock(TLockType &lock)
    : m_lock(lock)
    {
        m_lock.Lock();
    }

    template <typename TLockType>
    inline ScopedLock<TLockType>::~ScopedLock()
    {
        m_lock.Unlock();
    }

    template<typename TLockType>
    inline ScopedSharedLock<TLockType>::ScopedSharedLock(TLockType &sharedLock)
    : m_sharedLock(sharedLock)
    {
        m_sharedLock.LockShared();
    }

    template <typename TLockType>
    inline ScopedSharedLock<TLockType>::~ScopedSharedLock()
    {
        m_sharedLock.UnlockShared();
    }

    // Mutex
    UGE_INLINE Mutex::Mutex()
    {
        ::InitializeCriticalSection( &m_critSect );
    }

    UGE_INLINE Mutex::~Mutex()
    {
        ::DeleteCriticalSection( &m_critSect );
    }

    UGE_INLINE void Mutex::Lock()
    {
        ::EnterCriticalSection( &m_critSect );
    }

    UGE_INLINE Bool Mutex::TryLock()
    {
        return ::TryEnterCriticalSection( &m_critSect ) != FALSE;
    }

    UGE_INLINE void Mutex::Unlock()
    {
        ::LeaveCriticalSection( &m_critSect );
    }

    UGE_INLINE void Mutex::SetSpinCount( SpinCount_t count )
    {
        (void)::SetCriticalSectionSpinCount( &m_critSect, count );
    }

    // Semaphore
    UGE_INLINE Semaphore::Semaphore( Int32 initialCount, Int32 maxCount )
    {
        UGE_ASSERT( initialCount >= 0 && maxCount >= 0, "Invalid arguments");
        UGE_ASSERT( initialCount <= maxCount, "Invalid arguments");

        m_semaphore = ::CreateSemaphore( nullptr, initialCount, maxCount, nullptr );
    }

    UGE_INLINE Semaphore::~Semaphore()
    {
        if ( m_semaphore )
        {
            ::CloseHandle( m_semaphore );
        }
    }

    UGE_INLINE void Semaphore::Acquire()
    {
        const WaitResult_t result = ::WaitForSingleObject( m_semaphore, INFINITE );
        UGE_ASSERT( result == WAIT_OBJECT_0, "Failed to wait" );
    }

    UGE_INLINE Bool Semaphore::TryAcquire( TimeoutMs_t ms )
    {
        UGE_ASSERT( ms != INFINITE, "Infinite timeout ms specified" );
        const WaitResult_t result = ::WaitForSingleObject( m_semaphore, ms );
        UGE_ASSERT( result == WAIT_OBJECT_0 || result == WAIT_TIMEOUT, "Failed to wait" );

        return result == WAIT_OBJECT_0;
    }

    UGE_INLINE void Semaphore::Release(Int32 count)
    {
        ::ReleaseSemaphore( m_semaphore, count, nullptr );
    }

    UGE_INLINE const Semaphore_t Semaphore::Get() const
    {
        return m_semaphore;
    }

    // ConditionVariable
    UGE_INLINE ConditionVariable::ConditionVariable()
    {
        ::InitializeConditionVariable( &m_condition );
    }

    UGE_INLINE ConditionVariable::~ConditionVariable()
    {
    }

    UGE_INLINE void ConditionVariable::Wait( Mutex& mtx )
    {
        ::SleepConditionVariableCS( &m_condition, &mtx.m_critSect, INFINITE );
    }

    UGE_INLINE void ConditionVariable::WaitTimeout( Mutex& mtx, TimeoutMs_t ms )
    {
        ::SleepConditionVariableCS( &m_condition, &mtx.m_critSect, ms );
    }

    UGE_INLINE void ConditionVariable::WakeAny()
    {
        ::WakeConditionVariable( &m_condition );
    }

    UGE_INLINE void ConditionVariable::WakeAll()
    {
        ::WakeAllConditionVariable( &m_condition );
    }

    UGE_INLINE const AnsiChar *uge::Thread::GetThreadName() const
    {
        return m_threadName;
    }
}
