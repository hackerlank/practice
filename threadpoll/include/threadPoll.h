#ifndef THREAD_POLL_H
#define THREAD_POLL_H
#include "thread.h"
#include <map>

class ThreadPoll 
{
    private:
        static ThreadPoll *inst;
        std::map<size_t,Thread*> m_thread;
    public:
        static ThreadPoll& getInst();
        ~ThreadPoll();
        void loop();
    private:
        bool createThread();
        ThreadPoll();

};



#endif
