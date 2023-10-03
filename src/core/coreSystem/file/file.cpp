#include "file.h"

#include <share.h>

namespace uge { namespace file
{
    Bool FileOpen( FILE** file, const Char* fileName, const Char* mode )
    {
#ifdef UNICODE
        * file = ::_wfsopen( fileName, mode, SH_DENYNO );
#else
        *file = ::_fsopen( fileName, mode, SH_DENYNO );
#endif
        return *file != nullptr;
    }

    Bool FileClose( FILE* file )
    {
        return ::fclose( file ) == 0;
    }

    Bool FileFlush( FILE* file )
    {
        return ::fflush( file ) == 0;
    }

    void FilePrint( FILE* file, const Char* buffer )
    {
#ifdef UNICODE
        ::fputws( buffer, file );
#else
        ::fputs( buffer, file );
#endif
    }
}}