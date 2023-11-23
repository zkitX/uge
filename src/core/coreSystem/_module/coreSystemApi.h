#ifndef __CORESYSTEM_API_H__
#define __CORESYSTEM_API_H__

#if UGE_DLL
    #if UGE_CORESYSTEM_EXPORT
        #define CORESYSTEM_API __declspec(dllexport)
        #define CORESYSTEM_TEMPLATE
    #else
        #define CORESYSTEM_API __declspec(dllimport)
        #define CORESYSTEM_TEMPLATE extern
    #endif // UGE_CORESYSTEM_EXPORT
#else
    #define CORESYSTEM_API
    #define CORESYSTEM_TEMPLATE extern
#endif // UGE_DLL

#endif // __CORESYSTEM_API_H__