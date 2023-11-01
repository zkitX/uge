#ifndef __CORESYSTEM_LOG_H__
#define __CORESYSTEM_LOG_H__

#include <chrono>

#include "logQueue.h"
#include "logThread.h"
#include "threads/readWriteSpinLock.h"

namespace uge
{
    namespace log
    {
        typedef std::chrono::system_clock::time_point logTime_t;
        enum LogMode : UByte
        {
            LogMode_ASync,
            LogMode_Sync
        };

        enum LogLevel : UByte
        {
            LogLevel_Fatal,
            LogLevel_Error,
            LogLevel_Warning,
            LogLevel_Info,
            LogLevel_Debug,
            LogLevel_Trace
        };

        enum LogCategory
        {
            LogCategory_Core,

            LogCategory_MAX
        };

        struct LogCategoryPairs
        {
            LogCategory m_category;
            const char* m_name;
        };
        extern LogCategoryPairs g_logCategories[];

        struct LogLine
        {
            UInt64                  m_frame; // Our current frame
            logTime_t               m_time;
            UInt32                  m_threadId;
            LogLevel                m_level;
            LogCategory             m_category;
            AnsiChar                m_buffer[4096];
        };

        class LogSink
        {
        public:
            virtual void SinkLog(const char* formattedMsg, const LogLine& logLine ) = 0;
            virtual void Flush() = 0;

        protected:
            virtual ~LogSink();
        };

        const UInt32 c_logSinkMax = 8;

        class Log
        {
        public:
            Log();
            ~Log();

            void Init( LogMode mode );
            void Deinit();

            void Enable();
            void Disable();
            Bool IsEnabled() const;
            Bool CanLog( LogLevel level, LogCategory category ) const
            {
                return m_enabled && (level <= m_level) && (m_categoryMask & (1 << category));
            }

            void LogMessage( LogLevel level, LogCategory category, const char* format, ... );
            void LogMessage( LogLevel level, LogCategory category, const char* format, va_list args );

            void ForceFlush( LogMode mode );

            void RegisterSink( LogSink* sink );
            void UnregisterSink( LogSink* sink );

            void SetLevel( LogLevel level );
            void RestoreLevel();
            void ToggleLogCategory( LogCategory category, Bool enable = true );
            
        private:
            void QueueLog( LogLine&& logLine);
            Bool TryQueueLog( LogLine&& logLine );
            void SinkLog( const char* formattedMsg, const LogLine& logLine );

            Bool                   m_enabled;
            Bool                   m_initialized;
            LogLevel               m_level;
            LogMode                m_mode;
            UInt64                 m_categoryMask;

            RWSpinLock             m_sinkLock;

            LogSink*               m_sinks[c_logSinkMax];

            LogThread*             m_logThreadPtr;
            LogThread              m_logThreadInstance;

            LogQueue< LogLine >    m_logQueue;
        };

        Log& GetLog();
    }
}

#endif
