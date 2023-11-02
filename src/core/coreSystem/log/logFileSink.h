#ifndef __CORESYSTEM_LOGFILESINK_H__
#define __CORESYSTEM_LOGFILESINK_H__

#include "logSink.h"
#include <stdio.h>

namespace uge
{
    namespace log
    {
        class LogFileSink : public LogSink
        {
        public:
            LogFileSink();
            virtual ~LogFileSink();

            virtual void SinkLog(const char* formattedMsg, const LogLine& logLine);
            virtual void Flush();
            
            Bool OpenFile(const char* filename, const char* mode = "w");
            Bool CloseFile();

        private:
            FILE* m_file;
        };
    }
}

#endif // __CORESYSTEM_LOGFILESINK_H__