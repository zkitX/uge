#ifndef __CORESYSTEM_READWRITESPINLOCK_INL__
#define __CORESYSTEM_READWRITESPINLOCK_INL__

namespace uge
{
    UGE_INLINE RWSpinLock::RWSpinLock()
    : m_lock( c_UnlockValue)
    {
    }

    UGE_INLINE RWSpinLock::~RWSpinLock()
    {
    }

    UGE_INLINE void RWSpinLock::UnlockShared()
    {
        const AtomicByte oldValue = atomic::Atomic8::ExchangeAdd( &m_lock, -1);
        UGE_ASSERT( oldValue > 0, "Invalid usage!" );
    }

    UGE_INLINE void RWSpinLock::Unlock()
    {
        const AtomicByte oldValue = atomic::Atomic8::Exchange( &m_lock, c_UnlockValue);
        UGE_ASSERT( oldValue == c_WriteLockValue, "Invalid usage!" );
    }
}

#endif // __CORESYSTEM_READWRITESPINLOCK_INL__