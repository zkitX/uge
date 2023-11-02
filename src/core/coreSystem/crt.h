#ifndef __UGE_CORESYSTEM_CRT_H__
#define __UGE_CORESYSTEM_CRT_H__

namespace uge
{
    void Memcpy( void* __restrict dest, const void* __restrict source, size_t size );

    void* Memset( void* ptr, UInt32 x, size_t n );

    void* Memzero( void* ptr, size_t n );

    void* Malloc( size_t size );

    Bool Strcpy(UniChar* dest, const UniChar* src, size_t destSize, size_t srcSize = -1);
    Bool Strcpy(AnsiChar* dest, const AnsiChar* src, size_t destSize, size_t srcSize = -1);

    Bool Strcat(UniChar* dest, const UniChar* src, size_t destSize, size_t srcSize = -1);
    Bool Strcat(AnsiChar* dest, const AnsiChar* src, size_t destSize, size_t srcSize = -1);

    size_t Strlen(const UniChar* str);
    size_t Strlen(const AnsiChar* str);

    AnsiChar* Strchr(AnsiChar* str, AnsiChar c);
    const AnsiChar* Strchr(const AnsiChar* str, AnsiChar c);
    UniChar* Strchr(UniChar* str, UniChar c);
    const UniChar* Strchr(const UniChar* str, UniChar c);

    Int32 Vsnprintf(AnsiChar* buffer, size_t count, const AnsiChar* format, va_list arg);
    Int32 Vsnprintf(UniChar* buffer, size_t count, const UniChar* format, va_list arg);
}

#include "crt.inl"

#endif
