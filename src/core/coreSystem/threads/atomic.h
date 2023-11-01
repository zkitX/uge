#ifndef __CORESYSTEM_ATOMIC_H__
#define __CORESYSTEM_ATOMIC_H__

#include <intrin.h>

namespace uge
{
    namespace atomic
    {
        struct Atomic8
        {
            UGE_ALIGNED_TYPEDEF( Byte, 1, TAtomic8 );

            UGE_FORCE_INLINE static TAtomic8 Increment( TAtomic8 volatile* addend )
            {
                return (TAtomic8)::_InterlockedExchangeAdd8( addend, 1 ) + 1;
            }

            UGE_FORCE_INLINE static TAtomic8 Decrement( TAtomic8 volatile* addend )
            {
                return (TAtomic8)::_InterlockedExchangeAdd8( addend, -1 ) - 1;
            }

            UGE_FORCE_INLINE static TAtomic8 Exchange( TAtomic8 volatile* target, TAtomic8 value )
            {
                return (TAtomic8)::_InterlockedExchange8( target, value );
            }

            UGE_FORCE_INLINE static TAtomic8 CompareExchange( TAtomic8 volatile* destination, TAtomic8 exchange, TAtomic8 comparand )
            {
                return (TAtomic8)::_InterlockedCompareExchange8( destination, exchange, comparand );
            }

            UGE_FORCE_INLINE static TAtomic8 ExchangeAdd( TAtomic8 volatile* addend, TAtomic8 value )
            {
                return (TAtomic8)::_InterlockedExchangeAdd8( addend, value );
            }

            UGE_FORCE_INLINE static TAtomic8 Or( TAtomic8 volatile* destination, TAtomic8 value )
            {
                return (TAtomic8)::_InterlockedOr8( destination, value );
            }

            UGE_FORCE_INLINE static TAtomic8 And( TAtomic8 volatile* destination, TAtomic8 value )
            {
                return (TAtomic8)::_InterlockedAnd8( destination, value );
            }

            UGE_FORCE_INLINE static TAtomic8 Fetch( TAtomic8 volatile* destination )
            {
                return *(volatile TAtomic8*)(destination);
            }
        };
        struct Atomic16
        {
            UGE_ALIGNED_TYPEDEF( Int16, 2, TAtomic16 );

            UGE_FORCE_INLINE static TAtomic16 Increment( TAtomic16 volatile* addend )
            {
                return (TAtomic16)::_InterlockedIncrement16( addend );
            }

            UGE_FORCE_INLINE static TAtomic16 Decrement( TAtomic16 volatile* addend )
            {
                return (TAtomic16)::_InterlockedDecrement16( addend );
            }

            UGE_FORCE_INLINE static TAtomic16 Exchange( TAtomic16 volatile* target, TAtomic16 value )
            {
                return (TAtomic16)::_InterlockedExchange16( target, value );
            }

            UGE_FORCE_INLINE static TAtomic16 CompareExchange( TAtomic16 volatile* destination, TAtomic16 exchange, TAtomic16 comparand )
            {
                return (TAtomic16)::_InterlockedCompareExchange16( destination, exchange, comparand );
            }

            UGE_FORCE_INLINE static TAtomic16 ExchangeAdd( TAtomic16 volatile* addend, TAtomic16 value )
            {
                return (TAtomic16)::_InterlockedExchangeAdd16( addend, value );
            }

            UGE_FORCE_INLINE static TAtomic16 Or( TAtomic16 volatile* destination, TAtomic16 value )
            {
                return (TAtomic16)::_InterlockedOr16( destination, value );
            }

            UGE_FORCE_INLINE static TAtomic16 And( TAtomic16 volatile* destination, TAtomic16 value )
            {
                return (TAtomic16)::_InterlockedAnd16( destination, value );
            }

            UGE_FORCE_INLINE static TAtomic16 Fetch( TAtomic16 volatile* destination )
            {
                return *(volatile TAtomic16*)(destination);
            }
        };
        struct Atomic32
        {
            UGE_ALIGNED_TYPEDEF( LONG, 4, TAtomic32 );

            UGE_FORCE_INLINE static TAtomic32 Increment( TAtomic32 volatile* addend )
            {
                return (TAtomic32)::_InterlockedIncrement( addend );
            }

            UGE_FORCE_INLINE static TAtomic32 Decrement( TAtomic32 volatile* addend )
            {
                return (TAtomic32)::_InterlockedDecrement( addend );
            }

            UGE_FORCE_INLINE static TAtomic32 Exchange( TAtomic32 volatile* target, TAtomic32 value )
            {
                return (TAtomic32)::_InterlockedExchange( target, value );
            }

            UGE_FORCE_INLINE static TAtomic32 CompareExchange( TAtomic32 volatile* destination, TAtomic32 exchange, TAtomic32 comparand )
            {
                return (TAtomic32)::_InterlockedCompareExchange( destination, exchange, comparand );
            }

            UGE_FORCE_INLINE static TAtomic32 ExchangeAdd( TAtomic32 volatile* addend, TAtomic32 value )
            {
                return (TAtomic32)::_InterlockedExchangeAdd( addend, value );
            }

            UGE_FORCE_INLINE static TAtomic32 Or( TAtomic32 volatile* destination, TAtomic32 value )
            {
                return (TAtomic32)::_InterlockedOr( destination, value );
            }

            UGE_FORCE_INLINE static TAtomic32 And( TAtomic32 volatile* destination, TAtomic32 value )
            {
                return (TAtomic32)::_InterlockedAnd( destination, value );
            }

            UGE_FORCE_INLINE static TAtomic32 Fetch( TAtomic32 volatile* destination )
            {
                return *(volatile TAtomic32*)(destination);
            }
        };
        struct Atomic64
        {
            UGE_ALIGNED_TYPEDEF( LONG64, 8, TAtomic64 );

            UGE_FORCE_INLINE static TAtomic64 Increment( TAtomic64 volatile* addend )
            {
                return (TAtomic64)::_InterlockedIncrement64( addend );
            }

            UGE_FORCE_INLINE static TAtomic64 Decrement( TAtomic64 volatile* addend )
            {
                return (TAtomic64)::_InterlockedDecrement64( addend );
            }

            UGE_FORCE_INLINE static TAtomic64 Exchange( TAtomic64 volatile* target, TAtomic64 value )
            {
                return (TAtomic64)::_InterlockedExchange64( target, value );
            }

            UGE_FORCE_INLINE static TAtomic64 CompareExchange( TAtomic64 volatile* destination, TAtomic64 exchange, TAtomic64 comparand )
            {
                return (TAtomic64)::_InterlockedCompareExchange64( destination, exchange, comparand );
            }

            UGE_FORCE_INLINE static TAtomic64 ExchangeAdd( TAtomic64 volatile* addend, TAtomic64 value )
            {
                return (TAtomic64)::_InterlockedExchangeAdd64( addend, value );
            }

            UGE_FORCE_INLINE static TAtomic64 Or( TAtomic64 volatile* destination, TAtomic64 value )
            {
                return (TAtomic64)::_InterlockedOr64( destination, value );
            }

            UGE_FORCE_INLINE static TAtomic64 And( TAtomic64 volatile* destination, TAtomic64 value )
            {
                return (TAtomic64)::_InterlockedAnd64( destination, value );
            }

            UGE_FORCE_INLINE static TAtomic64 Fetch( TAtomic64 volatile* destination )
            {
                return *(volatile TAtomic64*)(destination);
            }
        };
        struct AtomicPtr
        {
            UGE_ALIGNED_TYPEDEF( void*, 8, TAtomicPtr );

            UGE_FORCE_INLINE static TAtomicPtr Exchange( TAtomicPtr volatile* target, TAtomicPtr value )
            {
                return _InterlockedExchangePointer( target, value );
            }

            UGE_FORCE_INLINE static TAtomicPtr CompareExchange( TAtomicPtr volatile* destination, TAtomicPtr exchange, TAtomicPtr comparand )
            {
                return _InterlockedCompareExchangePointer( destination, exchange, comparand );
            }

            UGE_FORCE_INLINE static TAtomicPtr Fetch( TAtomicPtr volatile* destination )
            {
                return *(volatile TAtomicPtr*)(destination);
            }
        };
    }

    typedef atomic::Atomic8::TAtomic8 AtomicByte;
    typedef atomic::Atomic16::TAtomic16 AtomicShort;
    typedef atomic::Atomic32::TAtomic32 AtomicInt;
    typedef atomic::Atomic64::TAtomic64 AtomicLong;
    typedef atomic::AtomicPtr::TAtomicPtr AtomicPointer;
}

#endif