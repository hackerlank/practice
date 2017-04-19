#ifndef THREAD_H
#define THREAD_H
#include <iostream>
using namespace std;
#include <pthread.h>
#include <vector>

class Thread
{
    private:
        std::string m_name;
        pthread_t m_id;
        pthread_cond_t m_cond;
        pthread_mutex_t m_mutex;
        volatile bool m_complete;
        bool m_join;
        volatile bool m_live;
        std::vector<int> m_task;
    public:
        Thread(const std::string &name,const bool joinable = true);
        static void* threadProc(void *arg);
        bool complete() const
        {
            return m_complete;
        }
        bool live() const
        {
            return m_live;
        }
        void setComplete()
        {
            m_complete = true;
        }
        void setLive()
        {
            pthread_mutex_lock(&m_mutex);
            m_live = true;
            pthread_cond_broadcast(&m_cond);
            pthread_mutex_unlock(&m_mutex);
        }
        void setDie()
        {
            pthread_mutex_lock(&m_mutex);
            m_live = false;
            pthread_cond_broadcast(&m_cond);
            pthread_mutex_unlock(&m_mutex);
        }
        bool join() const
        {
            return m_join;
        }
        pthread_t id() const
        {
            return m_id;
        }
        void add(const int task);
        void run();
        bool start();
        ~Thread();

};


#endif
