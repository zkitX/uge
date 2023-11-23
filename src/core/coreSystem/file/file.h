#ifndef __CORESYSTEM_FILE_H__
#define __CORESYSTEM_FILE_H__

#include <stdio.h>

namespace uge
{
    namespace file
    {
        CORESYSTEM_API Bool FileOpen( FILE** file, const AnsiChar* fileName, const AnsiChar* mode );
        CORESYSTEM_API Bool FileClose( FILE* file );
        CORESYSTEM_API Bool FileFlush( FILE* file );
        CORESYSTEM_API void FilePrint( FILE* file, const AnsiChar* buffer );
    }
}

#endif