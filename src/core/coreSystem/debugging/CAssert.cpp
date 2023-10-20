#include "build.h"

#include "CAssert.h"

namespace uge
{
    namespace dbg
    {
        static CAssert g_assert;

        void CAssert::OnAssert( const AnsiChar* filename, UInt32 line, const AnsiChar* expression, const AnsiChar* message, ... )
        {
            if (m_isHandlingAssert != 0)
            {
                
            }
        }
    }
}
