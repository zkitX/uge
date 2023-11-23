#ifndef __CORESYSTEM_LOGSINK_H__
#define __CORESYSTEM_LOGSINK_H__

namespace uge::log
{
    struct LogLine;

    class CORESYSTEM_API LogSink
    {
    public:
        virtual void SinkLog(const char *formattedMsg, const LogLine &logLine) = 0;
        virtual void Flush() = 0;

    protected:
        virtual ~LogSink();
    };
}

#endif // __CORESYSTEM_LOGSINK_H__