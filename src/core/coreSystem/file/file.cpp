#include "file.h"

#include <share.h>

namespace uge
{
    namespace file
    {
        CORESYSTEM_API Bool FileOpen(FILE **file, const AnsiChar *fileName, const AnsiChar *mode)
        {
            *file = ::_fsopen(fileName, mode, SH_DENYNO);
            return *file != nullptr;
        }

        CORESYSTEM_API Bool FileClose(FILE *file)
        {
            return ::fclose(file) == 0;
        }

        CORESYSTEM_API Bool FileFlush(FILE *file)
        {
            return ::fflush(file) == 0;
        }

        CORESYSTEM_API void FilePrint(FILE *file, const AnsiChar *buffer)
        {
            ::fputs(buffer, file);
        }
    }
}