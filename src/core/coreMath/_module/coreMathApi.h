#ifndef __COREMATH_API_H__
#define __COREMATH_API_H__

#if UGE_DLL
    #if UGE_COREMATH_EXPORT
        #define COREMATH_API __declspec(dllexport)
        #define COREMATH_TEMPLATE
    #else
        #define COREMATH_API __declspec(dllimport)
        #define COREMATH_TEMPLATE extern
    #endif // UGE_COREMATH_EXPORT
#else
    #define COREMATH_API
    #define COREMATH_TEMPLATE extern
#endif // UGE_DLL

#endif // __COREMATH_API_H__