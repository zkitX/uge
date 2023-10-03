#ifndef __CORESYSTEM_TYPES_H__
#define __CORESYSTEM_TYPES_H__
#pragma once

#include <Windows.h>
#include <cstdint>
#include <cinttypes>

// TODO: Custom assert function
#include <assert.h>

namespace uge
{
    typedef bool            Bool;

    typedef char            Byte;
    typedef unsigned char   UByte;

    typedef short           Int16;
    typedef unsigned short  UInt16;

    typedef int32_t         Int32;
    typedef uint32_t        UInt32;

    typedef int64_t         Int64;
    typedef uint64_t        UInt64;

    typedef float           F32;
    typedef double          F64;

    typedef wchar_t         UniChar;
    typedef char            AnsiChar;

#if defined(UNICODE)
    typedef UniChar         Char;
#define STR(s)              L##s
#else
    typedef AnsiChar        Char;
#define STR(s)              s
#endif
}

#endif // !__CORESYSTEM_TYPES_H__