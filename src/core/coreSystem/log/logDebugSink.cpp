#include "build.h"

#include "logQueue.h"
#include "logDebugSink.h"

namespace uge
{
    namespace log
    {
        LogDebugSink::LogDebugSink()
        {
        }

        LogDebugSink::~LogDebugSink()
        {
        }

        void LogDebugSink::SinkLog(const char* formattedMsg, const LogLine& logLine)
        {
            ::OutputDebugStringA(formattedMsg);
        }

        void LogDebugSink::Flush()
        {
        }
    }
}