#include "build.h"

#include "log.h"

namespace uge
{
    namespace log
    {
        Log::Log()
        : m_enabled(false)
        , m_initialized(false)
        , m_level(LogLevel_Info)
        , m_categoryMask(UINT64_MAX)
        , m_logThreadPtr(nullptr)
        {
            Memzero(m_sinks, sizeof(m_sinks));
            m_logThreadPtr = &m_logThreadInstance;
        }

        Log::~Log()
        {
        }

        void Log::Init(LogMode mode)
        {
            m_enabled = true;
            m_mode = mode;

            if (m_mode == LogMode_ASync)
            {
                m_logThreadPtr->Start(this);
            }

            m_initialized = true;
        }

        void Log::Deinit()
        {
            if (m_initialized)
            {
                ForceFlush(LogMode_ASync);
                m_enabled = false;

                if (m_mode == LogMode_ASync)
                {
                    m_logThreadPtr->Stop();
                }

                m_initialized = false;
            }
        }

        void Log::Enable()
        {
            if (m_initialized)
            {
                m_enabled = true;
            }
        }

        void Log::Disable()
        {
            if (m_initialized)
            {
                m_enabled = false;
            }
        }

        Bool Log::IsEnabled() const
        {
            return m_enabled;
        }

        void Log::LogMessage(LogLevel level, LogCategory category, const char *format, ...)
        {
            if (CanLog(level, category))
            {
                va_list argList;
                va_start(argList, format);
                LogMessage(level, category, format, argList);
                va_end(argList);
            }
        }

        void Log::LogMessage(LogLevel level, LogCategory category, const char *format, va_list args)
        {
            if (CanLog(level, category))
            {
                LogLine logMsg
                {
                    0,
                    std::chrono::system_clock::now(),
                    uge::ThreadId::GetCurrentThread().Get(),
                    level,
                    category
                };

                Vsnprintf(logMsg.m_buffer, sizeof(logMsg.m_buffer), format, args);
                QueueLog(std::move(logMsg));

                if (m_mode == LogMode_Sync)
                {
                    ForceFlush(LogMode_Sync);
                }
            }
        }

        void Log::ForceFlush(LogMode mode)
        {
        }

        void Log::RegisterSink(LogSink *sink)
        {
            UGE_ASSERT(sink != nullptr, "Invalid sink pointer");
            
            ScopedLock<RWSpinLock> lock(m_sinkLock);
            for (UInt32 i = 0; i != c_logSinkMax; ++i)
            {
                if (m_sinks[i] == nullptr)
                {
                    m_sinks[i] = sink;
                    return;
                }
            }
        }

        void Log::UnregisterSink(LogSink *sink)
        {
            UGE_ASSERT(sink != nullptr, "Invalid sink pointer");

            ScopedLock<RWSpinLock> lock(m_sinkLock);
            auto iter = std::remove(std::begin(m_sinks), std::end(m_sinks), sink);
            if (iter != std::end(m_sinks))
            {
                *iter = nullptr;
            }
        }

        void Log::SetLevel(LogLevel level)
        {
            m_level = level;
        }

        void Log::RestoreLevel()
        {
            m_level = LogLevel_Info;
        }

        void Log::ToggleLogCategory(LogCategory category, Bool enable)
        {
            if (enable)
            {
                m_categoryMask |= (1 << category);
            }
            else
            {
                m_categoryMask &= ~(1 << category);
            }
        }

        void Log::QueueLog(LogLine &&logLine)
        {
            if (!m_logQueue.QueueMessage(std::move(logLine)))
            {
                std::chrono::system_clock::time_point lastOperation = std::chrono::system_clock::now();

                do {
                    m_logQueue.Wait(lastOperation);
                }
                while (!m_logQueue.QueueMessage(std::move(logLine)));
            }
        }
        Bool Log::TryQueueLog(LogLine &&logLine)
        {
            return m_logQueue.QueueMessage(std::move(logLine));
        }

        void Log::SinkLog(const char *formattedMsg, const LogLine &logLine)
        {
            ScopedSharedLock<RWSpinLock> lock(m_sinkLock);
            for (UInt32 i = 0; i != c_logSinkMax; ++i)
            {
                if (!m_sinks[i])
                {
                    break;
                }

                m_sinks[i]->SinkLog(formattedMsg, logLine);
            }
        }
    }
}
