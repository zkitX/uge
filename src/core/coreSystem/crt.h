#ifndef __UGE_CORESYSTEM_CRT_H__
#define __UGE_CORESYSTEM_CRT_H__

namespace uge
{
    UGE_FORCE_INLINE void Memcpy( void* __restrict dest, const void* __restrict source, size_t size );

    UGE_FORCE_INLINE void* Memset( void* ptr, UInt32 x, size_t n );

    UGE_FORCE_INLINE void* Memzero( void* ptr, size_t n );

    UGE_FORCE_INLINE Bool Strcpy(UniChar* dest, const UniChar* src, size_t destSize, size_t srcSize = -1);
    UGE_FORCE_INLINE Bool Strcpy(AnsiChar* dest, const AnsiChar* src, size_t destSize, size_t srcSize = -1);
}

#include "crt.inl"

#endif
