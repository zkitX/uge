#ifndef __CORESYSTEM_LOGDEBUGSINK_H__
#define __CORESYSTEM_LOGDEBUGSINK_H__

#include "logSink.h"

namespace uge
{
    namespace log
    {
        class LogDebugSink : public LogSink
        {
        public:
            LogDebugSink();
            virtual ~LogDebugSink();

            virtual void SinkLog(const char* formattedMsg, const LogLine& logLine);
            virtual void Flush();
        };
    }
}

#endif // __CORESYSTEM_LOGDEBUGSINK_H__