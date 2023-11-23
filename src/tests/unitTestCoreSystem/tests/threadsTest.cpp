#include <gtest/gtest.h>
#include "core/coreSystem/build.h"

TEST(RWSpinLockTests, LockAndUnlock)
{
    uge::RWSpinLock lock;

    lock.Lock();
    // Assert that the lock is acquired

    lock.Unlock();
    // Assert that the lock is released
}

TEST(RWSpinLockTests, LockSharedAndUnlockShared)
{
    uge::RWSpinLock lock;

    lock.LockShared();
    // Assert that the shared lock is acquired

    lock.UnlockShared();
    // Assert that the shared lock is released
}

TEST(RWSpinLockTests, TryLock)
{
    uge::RWSpinLock lock;

    bool locked = lock.TryLock();
    // Assert that the lock is acquired

    if (locked)
    {
        lock.Unlock();
        // Assert that the lock is released
    }
    else
    {
        // Assert that the lock is not acquired
    }
}

TEST(RWSpinLockTests, TryLockShared)
{
    uge::RWSpinLock lock;

    bool locked = lock.TryLockShared();
    // Assert that the shared lock is acquired

    if (locked)
    {
        lock.UnlockShared();
        // Assert that the shared lock is released
    }
    else
    {
        // Assert that the shared lock is not acquired
    }
}
