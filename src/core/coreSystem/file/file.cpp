#include "file.h"

#include <share.h>

namespace uge
{
    namespace file
    {
        Bool FileOpen(FILE **file, const AnsiChar *fileName, const AnsiChar *mode)
        {
            *file = ::_fsopen(fileName, mode, SH_DENYNO);
            return *file != nullptr;
        }

        Bool FileClose(FILE *file)
        {
            return ::fclose(file) == 0;
        }

        Bool FileFlush(FILE *file)
        {
            return ::fflush(file) == 0;
        }

        void FilePrint(FILE *file, const AnsiChar *buffer)
        {
            ::fputs(buffer, file);
        }
    }
}