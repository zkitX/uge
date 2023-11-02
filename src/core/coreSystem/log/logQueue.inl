#ifndef __CORESYSTEM_LOGQUEUE_INL__
#define __CORESYSTEM_LOGQUEUE_INL__

namespace uge
{
    namespace log
    {
        template <typename TLogMessage>
        inline LogQueue<TLogMessage>::LogQueue()
            : m_queuePosition(0),
              m_dequeuePosition(0)
        {
            Memzero(&m_entries, sizeof(m_entries));

            for (UInt32 index = 0; index != c_logQueueSize; ++index)
            {
                m_entries[index].position = index;
            }
        }

        template <typename TLogMessage>
        inline LogQueue<TLogMessage>::~LogQueue()
        {
        }

        template <typename TLogMessage>
        inline Bool LogQueue<TLogMessage>::QueueMessage(TLogMessage &&message)
        {
            Entry *entry = nullptr;
            UInt32 position = m_queuePosition;
            for (;;)
            {
                entry = &m_entries[position & c_logQueueMask];
                UInt32 entryPosition = entry->position;

                const Int32 difference = static_cast<Int32>(entryPosition - position);

                if (difference == 0)
                {
                    const UInt32 newQueuePosition = position + 1;
                    if (atomic::Atomic32::CompareExchange(&m_queuePosition, newQueuePosition, position) == position)
                    {
                        entry->message = std::move(message);
                        atomic::Atomic32::Exchange(&entry->position, newQueuePosition);
                        return true;
                    }
                }
                else if (difference < 0)
                {
                    return false;
                }

                position = m_queuePosition;
            }

            // impossible to get here
            return false;
        }

        template <typename TLogMessage>
        inline Bool LogQueue<TLogMessage>::DequeueMessage(TLogMessage &message)
        {
            Entry *entry = nullptr;
            UInt32 position = m_dequeuePosition;
            for (;;)
            {
                entry = &m_entries[position & c_logQueueMask];
                UInt32 entryPosition = entry->position;

                const Int32 difference = static_cast<Int32>(entryPosition) - static_cast<Int32>(position + 1);

                if (difference == 0)
                {
                    const UInt32 newQueuePosition = position + 1;
                    if (atomic::Atomic32::CompareExchange(&m_dequeuePosition, newQueuePosition, position) == position)
                    {
                        message = std::move(entry->message);
                        atomic::Atomic32::Exchange(&entry->position, position + c_logQueueSize);
                        return true;
                    }
                }
                else if (difference < 0)
                {
                    return false;
                }

                position = m_dequeuePosition;
            }

            // impossible to get here
            return false;
        }

        template <typename TLogMessage>
        inline void log::LogQueue<TLogMessage>::Wait(const std::chrono::system_clock::time_point &lastOperation)
        {
            auto timeSinceLastOperation = std::chrono::system_clock::now() - lastOperation;

            if (timeSinceLastOperation > std::chrono::milliseconds(c_logQueueSpinMs))
            {
                if (timeSinceLastOperation < std::chrono::milliseconds(c_logQueueYieldMs))
                {
                    Thread_Yield();
                }
                else
                {
                    Thread_Sleep(1);
                }
            }
        }
    }
}


#endif