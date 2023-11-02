#ifndef __CORESYSTEM_LOG_H__
#define __CORESYSTEM_LOG_H__

#include <chrono>

#include "logSink.h"
#include "logQueue.h"
#include "logThread.h"
#include "threads/readWriteSpinLock.h"

namespace uge
{
    namespace log
    {
        typedef std::chrono::system_clock::time_point logTime_t;
        enum LogFlushMode : UByte
        {
            LogMode_ASync
        };

	    enum LogLineType : UByte
	    {
		    LogLineType_Log,
		    LogLineType_Flush
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
            LogCategory_Game,

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
            LogLineType             m_type;
            LogLevel                m_level;
            LogCategory             m_category;
            AnsiChar                m_buffer[4096];
        };

        const UInt32 c_logSinkMax = 8;

        class CLog
        {
        public:
            CLog();
            ~CLog();

            void Init( LogFlushMode mode );
            void Deinit();

            void Enable();
            void Disable();
            Bool IsEnabled() const;
            Bool CanLog( LogLevel level, LogCategory category ) const
            {
                return m_enabled && (level <= m_level) && (m_categoryMask & (1ull << category));
            }

            void PushMessage( LogLevel level, LogCategory category, const char* format, ... );
            void PushMessage( LogLevel level, LogCategory category, const char* format, va_list args );
            void PushFlush( LogFlushMode mode );

            void RegisterSink( LogSink* sink );
            void UnregisterSink( LogSink* sink );

            bool ConsumeNextLog();

            void SetLevel( LogLevel level );
            void RestoreLevel();
            void ToggleLogCategory( LogCategory category, Bool enable = true );
            
        private:

            void ConsumeLogMessage(const LogLine& logLine);
            void ConsumeFlushMessage();
            void QueueLog( LogLine&& logLine);
            Bool TryQueueLog( LogLine&& logLine );
            void SinkLog( const char* formattedMsg, const LogLine& logLine );

            Bool                   m_enabled;
            Bool                   m_initialized;
            LogLevel               m_level;
            LogFlushMode           m_flushMode;
            UInt64                 m_categoryMask;
            std::chrono::system_clock::time_point m_lastFlushTime;

            RWSpinLock             m_sinkLock;

            LogSink*               m_sinks[c_logSinkMax];

            LogThread*             m_logThreadPtr;
            LogThread              m_logThreadInstance;

            LogQueue< LogLine >    m_logQueue;
        };

        CLog& GetLog();
        void InitLog( LogFlushMode mode = LogMode_ASync );
        void DeinitLog();
        void FormatLogMessage( char* buffer, UInt32 bufferSize, const LogLine& logLine );
        void LogMsg( LogLevel level, LogCategory category, const char* format, ... );
        void LogMessage( LogLevel level, const char* message, LogCategory category );
        void LogFlush(LogFlushMode mode = LogMode_ASync);
        Bool CanLog( LogLevel level, LogCategory category );
    }
}

#ifdef UGE_LOG_ENABLED
#define INTERNAL_LOG( level, category, message, ... )\
    do {\
        if ( uge::log::CanLog( level, category ) )\
        {\
            uge::log::LogMsg( level, category, message, ##__VA_ARGS__ );\
        }\
    } while( (void)0,0 )

#define UGE_LOG_FATAL( category, message, ... )     INTERNAL_LOG( uge::log::LogLevel_Fatal, category, message, ##__VA_ARGS__ )
#define UGE_LOG_ERROR( category, message, ... )     INTERNAL_LOG( uge::log::LogLevel_Error, category, message, ##__VA_ARGS__ )
#define UGE_LOG_WARNING( category, message, ... )   INTERNAL_LOG( uge::log::LogLevel_Warning, category, message, ##__VA_ARGS__ )
#define UGE_LOG_INFO( category, message, ... )      INTERNAL_LOG( uge::log::LogLevel_Info, category, message, ##__VA_ARGS__ )
#define UGE_LOG_DEBUG( category, message, ... )     INTERNAL_LOG( uge::log::LogLevel_Debug, category, message, ##__VA_ARGS__ )
#define UGE_LOG_TRACE( category, message, ... )     INTERNAL_LOG( uge::log::LogLevel_Trace, category, message, ##__VA_ARGS__ )

#define UGE_LOG_FLUSH()                             uge::log::LogFlush()

#define UGE_ENABLE_LOG()                            uge::log::GetLog().Enable()

#else
#define INTERNAL_LOG( level, category, message, ...) do {} while( (void)0,0 )
#define UGE_LOG_FATAL( category, message, ... )      do {} while( (void)0,0 )
#define UGE_LOG_ERROR( category, message, ... )      do {} while( (void)0,0 )
#define UGE_LOG_WARNING( category, message, ... )    do {} while( (void)0,0 )
#define UGE_LOG_INFO( category, message, ... )       do {} while( (void)0,0 )
#define UGE_LOG_DEBUG( category, message, ... )      do {} while( (void)0,0 )
#define UGE_LOG_TRACE( category, message, ... )      do {} while( (void)0,0 )
#define UGE_LOG_FLUSH()                              do {} while( (void)0,0 )
#endif

#endif
