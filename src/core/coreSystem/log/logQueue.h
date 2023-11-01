#ifndef __CORESYSTEM_LOGQUEUE_H__
#define __CORESYSTEM_LOGQUEUE_H__

#include "threads/atomic.h"

namespace uge
{
    namespace log
    {
        template <typename TLogMessage>
        class LogQueue
        {
        public:
            LogQueue();
            ~LogQueue();  

            Bool QueueMessage( TLogMessage&& message);
            Bool DequeueMessage( TLogMessage& message);
            void Wait(const std::chrono::system_clock::time_point &lastOperation);

        private:
            struct Entry
            {
                atomic::Atomic32 position;
                TLogMessage message;
            };

            constexpr static UInt32 c_logQueueSize = 128;
            constexpr static UInt32 c_logQueueSpinMs = 1;
            constexpr static UInt32 c_logQueueYieldMs = 10;

            atomic::Atomic32    m_queuePosition;
            atomic::Atomic32    m_dequeuePosition;
            Entry               m_entries[c_logQueueSize];
        };
    }
}

#include "logQueue.inl"

#endif