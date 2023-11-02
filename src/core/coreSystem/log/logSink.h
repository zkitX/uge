#ifndef __CORESYSTEM_LOGSINK_H__
#define __CORESYSTEM_LOGSINK_H__

namespace uge
{
    namespace log
    {
        struct LogLine;
        
        class LogSink
        {
        public:
            virtual void SinkLog(const char* formattedMsg, const LogLine& logLine ) = 0;
            virtual void Flush() = 0;

        protected:
            virtual ~LogSink();
        };
    }
}

#endif // __CORESYSTEM_LOGSINK_H__