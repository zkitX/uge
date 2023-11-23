#include "build.h"
#include "ugeMain.h"

using namespace uge;

#define UGE_LOG_CATEGORY log::LogCategory_Game

int main( int argc, char** argv )
{
    log::InitLog();

    log::GetLog().SetLevel( log::LogLevel_Trace );

    while ( true )
    {
        // do stuff
        static UInt32 loop = 50;
        for ( ; loop > 0; --loop )
        {
            UGE_LOG_DEBUG( UGE_LOG_CATEGORY, "Hello %i", loop );
        }
        uge::Thread_Sleep( 1 );
    }

    log::DeinitLog();

    return 0;
}