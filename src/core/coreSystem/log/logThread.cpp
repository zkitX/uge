#include "build.h"

#include "logThread.h"
#include "log.h"

namespace uge
{
    namespace log
    {
        const char* c_logThreadName = "LogThread";
        const UInt32 c_logThreadStackSize = 128 * 1024;

        LogThread::LogThread()
            : Thread(c_logThreadName, c_logThreadStackSize)
            , m_log(nullptr)
            , m_running(false)
        {
        }

        LogThread::~LogThread()
        {
        }

        void LogThread::Start(CLog* log)
        {
            m_log = log;
            m_running = true;
            Thread::Init();
            Thread::SetPriority( EThreadPriority::Normal );
        }

        void LogThread::Stop()
        {
            m_running = false;
            Thread::Join();
        }

        void LogThread::ThreadFunc()
        {
            while (m_running)
            {
                while (m_log->ConsumeNextLog())
                {
                    continue;
                }
            }
        }
    }
}