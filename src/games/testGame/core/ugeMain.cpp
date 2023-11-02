#include "build.h"
#include "ugeMain.h"

#define UGE_LOG_CATEGORY uge::log::LogCategory_Game

int main( int argc, char** argv )
{
    uge::log::InitLog();

    uge::log::GetLog().SetLevel( uge::log::LogLevel_Trace );

    while ( true )
    {
        // do stuff
        static uge::UInt32 loop = 50;
        for ( ; loop > 0; --loop )
        {
            UGE_LOG_DEBUG( UGE_LOG_CATEGORY, "Hello %i", loop );
        }
        uge::Thread_Sleep( 1 );
    }

    uge::log::DeinitLog();

    return 0;
}