#ifndef __CORESYSTEM_READWRITESPINLOCK_H__
#define __CORESYSTEM_READWRITESPINLOCK_H__

#include "atomic.h"

namespace uge
{
    class CORESYSTEM_API RWSpinLock
    {
    public:
        RWSpinLock();
        ~RWSpinLock();
        
        void Lock();
        void LockShared();
        Bool TryLock();
        Bool TryLockShared();

        void Unlock();
        void UnlockShared();

    private:
        constexpr static AtomicByte c_UnlockValue = 0;
        constexpr static AtomicByte c_WriteLockValue = -1;

        constexpr static UInt32 c_MaxYieldsForSleep = 32;
        constexpr static UInt32 c_MaxSpinCountForYield = 512;
        constexpr static UInt32 c_MaxSpinCountForSleep = c_MaxSpinCountForYield * c_MaxYieldsForSleep;

        void YieldThread(UInt32& spinCount);

        volatile AtomicByte m_lock;
    };
}

#include "readWriteSpinLock.inl"

#endif // __CORESYSTEM_READWRITESPINLOCK_H__