#ifndef __CORESYSTEM_LOGQUEUE_H__
#define __CORESYSTEM_LOGQUEUE_H__

#include "logLine.h"
#include "threads/threads.h"
#include "threads/atomic.h"

namespace uge::log
{
    struct LogLine;

    template <typename TLogMessage>
    class LogQueue
    {
    public:
        LogQueue();
        ~LogQueue();

        Bool QueueMessage(TLogMessage &&message);
        Bool DequeueMessage(TLogMessage &message);
        void Wait(const std::chrono::system_clock::time_point &lastOperation);

    private:
        struct Entry
        {
            AtomicInt position;
            TLogMessage message;
        };

        constexpr static UInt32 c_logQueueSize = 128;
        constexpr static UInt32 c_logQueueSpinMs = 1;
        constexpr static UInt32 c_logQueueYieldMs = 10;
        constexpr static UInt32 c_logQueueMask = c_logQueueSize - 1;

        AtomicInt m_queuePosition;
        AtomicInt m_dequeuePosition;
        Entry m_entries[c_logQueueSize];
    };
}

#include "logQueue.inl"

#endif