#ifndef __CORESYSTEM_LOGTHREAD_H__
#define __CORESYSTEM_LOGTHREAD_H__

namespace uge
{
    namespace log
    {
        class CLog;

        class LogThread : public Thread
        {
        public:
            LogThread();
            virtual ~LogThread();
            
            virtual void Start(CLog* log);
            virtual void Stop();

            virtual void ThreadFunc();
        private:
            CLog* m_log;
            Bool m_running;
        };
    }
}

#endif