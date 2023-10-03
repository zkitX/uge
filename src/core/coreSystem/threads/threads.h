#ifndef __CORESYSTEM_THREADS_H__
#define __CORESYSTEM_THREADS_H__
#pragma once

#define UGE_NOCLASSCOPY(class_)     \
    private:                        \
        class_(const class_&);      \
        void operator=(const class_&);

#define UGE_NOSTRUCTCOPY(struct_)       \
    UGE_NOCLASSCOPY(struct_)            \
    public:                             

typedef DWORD       SpinCount_t;
typedef DWORD       TimeoutMs_t;
typedef DWORD       WaitResult_t;
typedef HANDLE      Semaphore_t;
typedef HANDLE      Thread_t;
typedef DWORD_PTR   AffinityMask_t;

namespace uge
{
    enum EThreadPriority : Int32
    {
        Idle,
        Lowest,
        BelowNormal,
        Normal,
        AboveNormal,
        Highest,
        TimeCritical
    };

    //////////////////////////////////////////////////////////////////////////
    // Mutex
    //////////////////////////////////////////////////////////////////////////
    class Mutex
    {
        friend class ConditionVariable;
    private:
        CRITICAL_SECTION    m_critSect;

    public:
        Mutex();
        ~Mutex();

    public:
        void Lock();
        Bool TryLock();
        void Unlock();
        void SetSpinCount( SpinCount_t count);
    };

    //////////////////////////////////////////////////////////////////////////
    // Semaphore
    //////////////////////////////////////////////////////////////////////////
    class Semaphore
    {
    private:
        Semaphore_t m_semaphore;

    public:
        Semaphore( Int32 initialCount, Int32 maxCount );
        ~Semaphore();

    public:
        void Acquire();
        Bool TryAcquire( TimeoutMs_t  ms );
        void Release(Int32 count);
        const Semaphore_t Get() const;
    };

    //////////////////////////////////////////////////////////////////////////
    // ConditionVariable
    //////////////////////////////////////////////////////////////////////////
    class ConditionVariable
    {
    private:
        CONDITION_VARIABLE m_condition;

    public:
        ConditionVariable();
        ~ConditionVariable();

    public:
        void Wait( Mutex& mtx );
        void WaitTimeout( Mutex& mtx, TimeoutMs_t ms );

        void WakeAny();
        void WakeAll();
    };

    //////////////////////////////////////////////////////////////////////////
    // ThreadId
    //////////////////////////////////////////////////////////////////////////
    struct ThreadId
    {
        constexpr ThreadId() : id( 0 ) {}
        explicit constexpr ThreadId( UInt32 tId ) : id( tId ) {}
        UInt32 id;

        UGE_INLINE Bool operator==( const ThreadId& other ) const
        {
            return id == other.id;
        }

        UGE_INLINE Bool operator!=( const ThreadId& other ) const
        {
            return id != other.id;
        }

        UGE_INLINE const UInt32 Get() const
        {
            return id;
        }

        void Init()
        {
            Int64 value = __readgsqword( 0x30 );
            id = *reinterpret_cast<UInt32*>(value + 0x48);
        }

        UGE_INLINE Bool isValid() const
        {
            return id != 0;
        }

        static ThreadId GetCurrentThread()
        {
            ThreadId threadId;
            threadId.Init();
            return threadId;
        }
    };

    constexpr size_t g_MaxThreadNameLength = 32;
    
    void Thread_Yield();
    void Thread_Sleep( TimeoutMs_t ms );
    void Thread_SetAffinity( AffinityMask_t affinityMask );
    void Thread_SetName( const AnsiChar* threadName );
    void Thread_Suspend( ThreadId id );
    void Thread_Resume( ThreadId id );

    //////////////////////////////////////////////////////////////////////////
    // Thread
    //////////////////////////////////////////////////////////////////////////
    class Thread
    {
        UGE_NOCLASSCOPY(Thread)
    private:
        Thread_t        m_thread;
        AnsiChar        m_threadName[g_MaxThreadNameLength];

    public:
                        Thread( const Char* threadName );
        virtual         ~Thread();
        void            Join();
        void            Detach();
        void            Init();

        virtual void    ThreadFunc() = 0;
        const AnsiChar* GetThreadName() const;

        void            SetAffinityMask( AffinityMask_t mask );
        void            SetPriority( EThreadPriority threadPriority );

        Bool            operator==( const Thread& other ) const;
    };
}

#include "threads.inl"
#endif