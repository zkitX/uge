#ifndef __CORESYSTEM_FILE_H__
#define __CORESYSTEM_FILE_H__

#include <stdio.h>

namespace uge
{
    namespace file
    {
        Bool FileOpen( FILE** file, const AnsiChar* fileName, const AnsiChar* mode );
        Bool FileClose( FILE* file );
        Bool FileFlush( FILE* file );
        void FilePrint( FILE* file, const AnsiChar* buffer );
    }
}

#endif