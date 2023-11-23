#include "build.h"

#include "log.h"
#include "logDebugSink.h"

namespace uge::log
{
    /**
     * @brief Array of strings representing the different logger levels.
     */
    const char *c_loggerLevelString[] =
        {
            "[Fatal]",
            "[Error]",
            "[Warning]",
            "[Info]",
            "[Debug]",
            "[Trace]"};

    CLog::CLog()
        : m_enabled(false), m_initialized(false), m_level(LogLevel_Info), m_categoryMask(UINT64_MAX), m_lastFlushTime(std::chrono::system_clock::now()), m_logThreadPtr(nullptr)
    {
        Memzero(m_sinks, sizeof(m_sinks));
        m_logThreadPtr = &m_logThreadInstance;
    }

    CLog::~CLog()
    {
    }

    /**
     * Initializes the Log object with the specified mode.
     *
     * @param mode The mode to initialize the Log object with.
     */
    void CLog::Init(LogFlushMode mode)
    {
        m_enabled = true;
        m_flushMode = mode;

        if (m_flushMode == LogMode_ASync)
        {
            m_logThreadPtr->Start(this);
        }

        m_initialized = true;
    }

    /**
     * @brief Deinitializes the logging system.
     *
     * This function deinitializes the logging system by flushing any remaining log messages,
     * disabling logging, stopping the logging thread (if running in asynchronous mode), and
     * marking the system as uninitialized.
     */
    void CLog::Deinit()
    {
        if (m_initialized)
        {
            PushFlush(LogMode_ASync);
            m_enabled = false;

            if (m_flushMode == LogMode_ASync)
            {
                m_logThreadPtr->Stop();
            }

            m_initialized = false;
        }
    }

    /**
     * @brief Disables logging if it has NOT been initialized.
     */
    void CLog::Enable()
    {
        if (m_initialized)
        {
            m_enabled = true;
        }
    }

    /**
     * @brief Disables logging if it has been initialized.
     */
    void CLog::Disable()
    {
        if (m_initialized)
        {
            m_enabled = false;
        }
    }

    /**
     * @brief Returns a boolean value indicating whether logging is enabled or not.
     *
     * @return Bool - true if logging is enabled, false otherwise.
     */
    Bool CLog::IsEnabled() const
    {
        return m_enabled;
    }

    /**
     * Logs a message with the specified log level and category.
     *
     * @param level The log level of the message.
     * @param category The log category of the message.
     * @param format The format string of the message.
     * @param ... The variable arguments to be formatted according to the format string.
     */
    void CLog::PushMessage(LogLevel level, LogCategory category, const char *format, ...)
    {
        if (CanLog(level, category))
        {
            va_list argList;
            va_start(argList, format);
            PushMessage(level, category, format, argList);
            va_end(argList);
        }
    }

    /**
     * @brief Logs a message with the specified log level, category, format and arguments.
     *
     * @param level The log level of the message.
     * @param category The category of the message.
     * @param format The format string of the message.
     * @param args The arguments to be formatted into the message.
     */
    void CLog::PushMessage(LogLevel level, LogCategory category, const char *format, va_list args)
    {
        if (CanLog(level, category))
        {
            LogLine logMsg{
                0,
                std::chrono::system_clock::now(),
                uge::ThreadId::GetCurrentThread().Get(),
                LogLineType_Log,
                level,
                category};

            Vsnprintf(logMsg.m_buffer, sizeof(logMsg.m_buffer), format, args);
            QueueLog(std::move(logMsg));
        }
    }

    /**
     * @brief Pushes a flush log message to the log queue.
     *
     * @param mode The log mode to use.
     */
    void CLog::PushFlush(LogFlushMode mode)
    {
        if (m_enabled)
        {
            LogLine logMsg{
                0,
                std::chrono::system_clock::now(),
                uge::ThreadId::GetCurrentThread().Get(),
                LogLineType_Flush,
                LogLevel_Info,
                LogCategory_Core};

            QueueLog(std::move(logMsg));
        }
    }

    /**
     * @brief Registers a new log sink to receive log messages.
     *
     * @param sink Pointer to the log sink to register.
     */
    void CLog::RegisterSink(LogSink *sink)
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

    /**
     * @brief Unregisters a log sink from the logger.
     *
     * @param sink Pointer to the log sink to unregister.
     */
    void CLog::UnregisterSink(LogSink *sink)
    {
        UGE_ASSERT(sink != nullptr, "Invalid sink pointer");

        ScopedLock<RWSpinLock> lock(m_sinkLock);
        auto iter = std::remove(std::begin(m_sinks), std::end(m_sinks), sink);
        if (iter != std::end(m_sinks))
        {
            *iter = nullptr;
        }
    }

    /**
     * @brief Consumes the next log message from the log queue.
     *
     * @return true if a log message was consumed, false otherwise.
     */
    bool CLog::ConsumeNextLog()
    {
        bool result = false;

        LogLine message;
        if (m_logQueue.DequeueMessage(message))
        {
            m_lastFlushTime = std::chrono::system_clock::now();
            message.m_type == LogLineType_Log ? ConsumeLogMessage(message) : ConsumeFlushMessage();
            result = true;
        }

        if (!result)
        {
            m_logQueue.Wait(m_lastFlushTime);
        }

        return result;
    }

    /** @brief Sets the logging level for the Log object.
     * The logging level determines which log messages will be printed.
     * Messages with a level lower than the set level will be ignored.
     *
     * @param level The logging level to set.
     */
    void CLog::SetLevel(LogLevel level)
    {
        m_level = level;
    }

    /**
     * @brief Restores the log level to the default value of LogLevel_Info.
     */
    void CLog::RestoreLevel()
    {
        m_level = LogLevel_Info;
    }

    /**
     * @brief Toggles the logging of a specific category.
     *
     * @param category The category to toggle.
     * @param enable Whether to enable or disable the logging of the category.
     */
    void CLog::ToggleLogCategory(LogCategory category, Bool enable)
    {
        if (enable)
        {
            m_categoryMask |= (1ull << category);
        }
        else
        {
            m_categoryMask &= ~(1ull << category);
        }
    }

    /**
     * @brief Consumes a log line by formatting it and sinking it to the appropriate log sink.
     *
     * @param logLine The log line to consume.
     */
    void CLog::ConsumeLogMessage(const LogLine &logLine)
    {
        char formattedMsg[4096];

        FormatLogMessage(formattedMsg, sizeof(formattedMsg), logLine);
        SinkLog(formattedMsg, logLine);
    }

    /**
     * @brief Flushes all the log sinks.
     *
     * This function acquires a shared lock on the sink lock and then iterates over all the log sinks
     * and calls their Flush() function.
     *
     * @return void
     */
    void CLog::ConsumeFlushMessage()
    {
        ScopedSharedLock<RWSpinLock> lock(m_sinkLock);

        for (UInt32 i = 0; i != c_logSinkMax; ++i)
        {
            if (!m_sinks[i])
            {
                break;
            }

            m_sinks[i]->Flush();
        }
    }

    /**
     * @brief Queues a log message to be written to the log.
     *
     * @param logLine The log message to be queued.
     */
    void CLog::QueueLog(LogLine &&logLine)
    {
        if (!m_logQueue.QueueMessage(std::move(logLine)))
        {
            std::chrono::system_clock::time_point lastOperation = std::chrono::system_clock::now();

            do
            {
                m_logQueue.Wait(lastOperation);
            } while (!m_logQueue.QueueMessage(std::move(logLine)));
        }
    }

    /**
     * @brief Queues a log message to be written to the log.
     *
     * @param logLine The log message to be queued.
     * @return True if the message was queued successfully, false otherwise.
     */
    Bool CLog::TryQueueLog(LogLine &&logLine)
    {
        return m_logQueue.QueueMessage(std::move(logLine));
    }

    /**
     * @brief Sends the formatted message and log line to all registered sinks.
     *
     * @param formattedMsg The formatted message to be sent to the sinks.
     * @param logLine The log line containing metadata about the log message.
     */
    void CLog::SinkLog(const char *formattedMsg, const LogLine &logLine)
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

    namespace priv
    {
        /**
         * @brief Creates a new instance of CLog and returns a pointer to it.
         *
         * @return CLog* Pointer to the created CLog instance.
         */
        CLog *CreateLog()
        {
            static CLog *s_log = ::new (std::malloc(sizeof(CLog))) CLog;
            return s_log;
        }
    }

    /**
     * @brief Returns a reference to the CLog object.
     *
     * @return CLog& reference to an instance of CLog.
     */
    CLog &GetLog()
    {
        static CLog *s_logPointer = nullptr;
        if (!s_logPointer)
        {
            s_logPointer = priv::CreateLog();
        }

        return *s_logPointer;
    }

    LogDebugSink s_debugSink;

    /**
     * @brief Initializes the logging system.
     *
     * @param mode The flush mode to use.
     */
    void InitLog(LogFlushMode mode)
    {
        auto &log = GetLog();
        if (IsDebuggerPresent())
        {
            log.RegisterSink(&s_debugSink);
        }

        log.Init(mode);
    }

    /**
     * @brief Deinitializes the logging system.
     */
    void DeinitLog()
    {
        auto &log = GetLog();
        log.Deinit();
        log.UnregisterSink(&s_debugSink);
    }

    /**
     * @brief Formats the log message with timestamp, log level and message buffer.
     *
     * @param buffer The buffer to store the formatted log message.
     * @param bufferSize The size of the buffer.
     * @param logLine The log line containing the message, timestamp and log level.
     */
    void FormatLogMessage(char *buffer, UInt32 bufferSize, const LogLine &logLine)
    {
        auto time = std::chrono::system_clock::to_time_t(logLine.m_time);
        std::tm localTime;
        localtime_s(&localTime, &time);

        strftime(buffer, bufferSize, "[%Y.%m.%d %X]", &localTime);
        Strcat(buffer, c_loggerLevelString[logLine.m_level], bufferSize);
        Strcat(buffer, " ", bufferSize);
        Strcat(buffer, logLine.m_buffer, bufferSize);
        Strcat(buffer, "\n", bufferSize);
    }

    /**
     * @brief Logs a message with the specified log level and category.
     *
     * @param level The log level of the message.
     * @param category The log category of the message.
     * @param format The format string of the message.
     * @param ... The variable arguments to be formatted according to the format string.
     */
    void LogMsg(LogLevel level, LogCategory category, const char *format, ...)
    {
        va_list argList;
        va_start(argList, format);
        GetLog().PushMessage(level, category, format, argList);
        va_end(argList);
    }

    /**
     * @brief Logs a message with the specified log level and category.
     *
     * @param level The log level of the message.
     * @param message The message to be logged.
     * @param category The category of the message.
     */
    void LogMessage(LogLevel level, const char *message, LogCategory category)
    {
        auto &log = GetLog();
        if (!log.CanLog(level, category))
        {
            return;
        }

        const char *currentLine = message;
        while (const char *nextLine = Strchr(currentLine, '\n'))
        {
            const UInt32 currentLineLength = std::min<UInt32>(nextLine - currentLine, sizeof(LogLine::m_buffer) - 1);

            LogMsg(level, category, "%.*s", currentLineLength, currentLine);

            currentLine = nextLine + 1;
        }

        LogMsg(level, category, "%s", currentLine);
    }

    /**
     * @brief Flushes the log buffer.
     *
     * @param mode The flush mode to use.
     */
    void LogFlush(LogFlushMode mode)
    {
        GetLog().PushFlush(mode);
    }

    Bool CanLog(LogLevel level, LogCategory category)
    {
        return GetLog().CanLog(level, category);
    }
}
