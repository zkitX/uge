#ifndef __CORESYSTEM_LOGTHREAD_H__
#define __CORESYSTEM_LOGTHREAD_H__

namespace uge::log
{
    class CLog;

    class CORESYSTEM_API LogThread : public Thread
    {
    public:
        LogThread();
        virtual ~LogThread();

        virtual void Start(CLog *log);
        virtual void Stop();

        virtual void ThreadFunc();

    private:
        CLog *m_log;
        Bool m_running;
    };
}

#endif