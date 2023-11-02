#include <cstring>
#include <cstdlib>
#include <cwchar>
#include <cctype>
#include <cwctype>
#include <stdio.h>
#include <errno.h>
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

    UGE_FORCE_INLINE void *Malloc( size_t size)
    {
        void* ptr = ::malloc( size );
        if (ptr == nullptr)
        {
            return nullptr;
        }
        return ptr;
    }

    UGE_FORCE_INLINE Bool Strcpy(AnsiChar *dest, const AnsiChar *src, size_t destSize, size_t srcSize)
    {
        return ::strncpy_s( dest, destSize, src, srcSize ) == 0;
    }

    UGE_FORCE_INLINE Bool Strcat(UniChar *dest, const UniChar *src, size_t destSize, size_t srcSize)
    {
        return ::wcsncat_s( dest, destSize, src, srcSize ) == 0;
    }

    UGE_FORCE_INLINE Bool Strcat(AnsiChar *dest, const AnsiChar *src, size_t destSize, size_t srcSize)
    {
        return ::strncat_s( dest, destSize, src, srcSize ) == 0;
    }

    UGE_FORCE_INLINE Bool Strcpy( UniChar* dest, const UniChar* src, size_t destSize, size_t srcSize )
    {
        return ::wcsncpy_s( dest, destSize, src, srcSize ) == 0;
    }

    UGE_FORCE_INLINE size_t Strlen(const UniChar *str)
    {
        return ::wcslen( str );
    }

    UGE_FORCE_INLINE size_t Strlen(const AnsiChar *str)
    {
        return ::strlen( str );
    }

    UGE_FORCE_INLINE AnsiChar *Strchr(AnsiChar *str, AnsiChar c)
    {
        return ::strchr( str, c );
    }

    UGE_FORCE_INLINE const AnsiChar *Strchr(const AnsiChar *str, AnsiChar c)
    {
        return ::strchr( str, c );
    }
    
    UGE_FORCE_INLINE UniChar *Strchr(UniChar *str, UniChar c)
    {
        return ::wcschr( str, c );
    }

    UGE_FORCE_INLINE const UniChar *Strchr(const UniChar *str, UniChar c)
    {
        return ::wcschr( str, c );
    }

    UGE_FORCE_INLINE Int32 Vsnprintf(AnsiChar *buffer, size_t count, const AnsiChar *format, va_list arg)
    {
        return ::vsnprintf_s( buffer, count, _TRUNCATE, format, arg);
    }

    UGE_FORCE_INLINE Int32 Vsnprintf(UniChar *buffer, size_t count, const UniChar *format, va_list arg)
    {
        return ::_vsnwprintf_s( buffer, count, _TRUNCATE, format, arg );
    }
}