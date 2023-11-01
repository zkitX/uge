#ifndef __CORESYSTEM_LOGTHREAD_H__
#define __CORESYSTEM_LOGTHREAD_H__

namespace uge
{
    namespace log
    {
        class Log;

        class LogThread : public Thread
        {
        public:
            LogThread();
            virtual ~LogThread();
            
            virtual void Start(Log* log);
            virtual void Stop();

            virtual void ThreadFunc();
        private:
            Log* m_log;
            Bool m_running;
        };
    }
}

#endif