#include "build.h"

#include "readWriteSpinLock.h"

namespace uge
{
    /**
     * @brief Acquires a write lock on the RWSpinLock object.
     * If the lock is already held by another thread, the function will spin until the lock is released.
     */
    void RWSpinLock::Lock()
    {
        UInt32 spinCount = 0;
        for (;;)
        {
            if (atomic::Atomic8::Fetch(&m_lock) == 0)
            {
                if (atomic::Atomic8::CompareExchange(&m_lock, c_WriteLockValue, c_UnlockValue) == c_UnlockValue)
                {
                    break;
                }
            }
        }
    }

    /**
     * @brief Acquires a shared lock on the read-write spin lock.
     * If the lock is currently held by a writer, the calling thread will spin until the lock is released.
     * If the lock is currently held by one or more readers, the calling thread will acquire a shared lock and proceed.
     */
    void RWSpinLock::LockShared()
    {
        UInt32 spinCount = 0;
        for (;;)
        {
            Byte expectedValue = atomic::Atomic8::Fetch(&m_lock);
            if (expectedValue != c_WriteLockValue)
            {
                Byte desiredValue = 1 + expectedValue;
                if (atomic::Atomic8::CompareExchange(&m_lock, desiredValue, expectedValue) == expectedValue)
                {
                    break;
                }
            }

            YieldThread(spinCount);
        }
    }

    /**
     * @brief Attempts to acquire the write lock on the RWSpinLock object.
     *
     * @return true if the lock was acquired, false otherwise.
     */
    Bool RWSpinLock::TryLock()
    {
        return atomic::Atomic8::CompareExchange(&m_lock, c_WriteLockValue, c_UnlockValue) == c_UnlockValue;
    }

    /**
     * @brief Attempts to acquire a shared read lock on the RWSpinLock object.
     * 
     * @return true if the shared read lock was acquired successfully, false otherwise.
     */
    Bool RWSpinLock::TryLockShared()
    {
        Byte expectedValue = atomic::Atomic8::Fetch(&m_lock);
        if (expectedValue != c_WriteLockValue)
        {
            Byte desiredValue = 1 + expectedValue;
            return atomic::Atomic8::CompareExchange(&m_lock, desiredValue, expectedValue) == expectedValue;
        }

        return false;
    }

    /**
     * @brief This function yields the thread if the spin count exceeds the maximum spin count for sleep or yield.
     * 
     * @param spinCount The number of times the thread has spun without yielding or sleeping.
     */
    void RWSpinLock::YieldThread(UInt32 &spinCount)
    {
        ++spinCount;

        if (spinCount >= c_MaxSpinCountForSleep)
        {
            Thread_Sleep(1);
            spinCount = 0;
        }
        else if (spinCount % c_MaxSpinCountForYield == 0)
        {
            Thread_Yield();
        }
    }
}
