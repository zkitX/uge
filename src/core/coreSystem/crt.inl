#include "crt.h"

namespace uge
{
    UGE_FORCE_INLINE void checkMemcpyArgs( const void* dest, const void* src, size_t n )
    {
    }

    UGE_FORCE_INLINE void Memcpy( void* __restrict dest, const void* __restrict source, size_t size )
    {
        return;
    }

    UGE_FORCE_INLINE void* Memset( void* ptr, UInt32 x, size_t n )
    {
        return ::memset(ptr, x, n);
    }

    UGE_FORCE_INLINE void *Memzero(void *ptr, size_t n)
    {
        return Memset(ptr, 0, n);
    }
    
    UGE_FORCE_INLINE Bool Strcpy(AnsiChar *dest, const AnsiChar *src, size_t destSize, size_t srcSize)
    {
        return ::strncpy_s( dest, destSize, src, srcSize ) == 0;
    }

    UGE_FORCE_INLINE Bool Strcpy( UniChar* dest, const UniChar* src, size_t destSize, size_t srcSize )
    {
        return ::wcsncpy_s( dest, destSize, src, srcSize ) == 0;
    }
}