#ifndef __CORESYSTEM_CASSERT_H__
#define __CORESYSTEM_CASSERT_H__

#include "settings/types.h"

enum EAssertType
{
    AssertType_None,
    AssertType_Assert,
    AssertType_Sanity
};

namespace uge
{
    namespace dbg
    {
        class CAssert
        {
        public:
            CAssert()
                : m_assertType( AssertType_None ),
                  m_isHandlingAssert( false )
            {
            }
            void OnAssert( const AnsiChar* filename, UInt32 line, const AnsiChar* expression, const AnsiChar* message, ... );

        protected:
            friend class CStackTrace;
            AnsiChar m_buffer[1024];
            EAssertType m_assertType;
            Bool m_isHandlingAssert;
        };

        extern CAssert g_assert;
    };
}

#define UGE_ASSERT(cond, msg, ...)\
    do {\
        if (!(cond)) {\
            uge::dbg::g_assert.OnAssert( __FILE__, __LINE__, #cond, msg, ##__VA_ARGS__ );\
            __debugbreak();\
        }\
    } while (false)

#endif