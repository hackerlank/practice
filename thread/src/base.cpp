#include "base.h"
#include <iostream>
using namespace std;

Thread::Thread(const bool join) : id(0),complete(false),alive(false),join(join)
{
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    loop = false;
}

bool Thread::start()
{
    bool ret = false;
    do 
    {
        if(alive || complete)
        {
            break;
        }
        if(pthread_create(&id,NULL,func,(void*)this))
        {
            break;
        }
        std::cout << "begin wait alive for true" << std::endl;
        pthread_mutex_lock(&mutex);
        while(!alive)
        {
            std::cout << "waiting alive for true" << std::endl;
            pthread_cond_wait(&cond,&mutex);
        }
        pthread_mutex_unlock(&mutex);
        std::cout << "end wait alive for true" << std::endl;
        ret = true;
    }while(false);
    return ret;
}

void* Thread::func(void *arg)
{
    do 
    {
        Thread *thread = reinterpret_cast<Thread*>(arg);
        if(!thread)
        {
            break;
        }
        std::cout << "\nbegin set alive for true" << std::endl;
        thread->alive = true;
        pthread_cond_broadcast(&thread->cond);
        std::cout << "\nend set alive for true" << std::endl;
        //mysql_thread_init();
        thread->run();
        //mysql_thread_end();
    }while(false);
}

bool Thread::run()
{
    if(!complete)
    {
        unsigned int val = 0;
        std::cout << "\nthread run begin" << std::endl;
        while(true)
        {
            pthread_mutex_lock(&mutex);
            while(!loop)
            {
                val += 1;
                pthread_cond_wait(&cond,&mutex);
            }
            pthread_mutex_unlock(&mutex);
            std::cout << "val:" << val << std::endl;
        }

    }
    std::cout << "thread run end" << std::endl;
    return true;
}

void Thread::final()
{
    pthread_join(id,NULL);
}

void Thread::setLoop(const bool flag)
{
    loop = flag;
    pthread_cond_broadcast(&cond);
}
