#ifndef __CORESYSTEM_SETTINGS_H__
#define __CORESYSTEM_SETTINGS_H__

#if defined( UGE_DEBUG )
    #define UGE_LOG_ENABLED 1
    #define UGE_ASSERTS_ENABLED 1
#elif defined( UGE_RELEASE )
    #define UGE_LOG_ENABLED 0
    #define UGE_ASSERTS_ENABLED 0
#endif

#endif  // __CORESYSTEM_SETTINGS_H__