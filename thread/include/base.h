#ifndef BASE_H
#define BASE_H
#include <pthread.h>

class Thread
{
    public:
        pthread_t id;
        volatile bool complete;
        volatile bool alive;
        volatile bool join;
        pthread_mutex_t mutex;
        pthread_cond_t  cond;
        bool loop;
    public:
        Thread(const bool join = true); 
        bool start();
        bool run();
        void final();
        static void* func(void *arg);
        void setLoop(const bool flag);
};

#endif
