#ifndef __CORESYSTEM_COMPILER_H__
#define __CORESYSTEM_COMPILER_H__
#pragma once

#define UGE_FUNCTION __FUNCTION__

#define UGE_ALIGN(alignment)                        __declspec(align(alignment))

#define UGE_ALIGNED_CLASS(type, alignment)          class UGE_ALIGN(alignment) type
#define UGE_ALIGNED_STRUCT(type, alignment)         struct UGE_ALIGN(alignment) type
#define UGE_ALIGNED_VAR(type, alignment)            UGE_ALIGN(alignment) type
#define UGE_ALIGNED_TYPEDEF(type, alignment, name)  typedef UGE_ALIGN(alignment) type name

#define UGE_NOINLINE                __declspec( noinline )
#define UGE_INLINE                  inline
#define UGE_FORCE_INLINE            __forceinline

#define UGE_RESTRICT_RETURN         __declspec( restrict )
#define UGE_RESTRICT_PARAMS         __declspec( noalias )
#define UGE_RESTRICT_LOCAL          __restrict

#define UGE_CDECL                   __cdecl
#define UGE_STDCALL                 __stdcall
#define UGE_FASTCALL                __fastcall
#define UGE_VECTORCALL              __vectorcall

#endif