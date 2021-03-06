#include "thread.h"

Thread::Thread(const std::string &name,const bool joinable) : m_name(name),m_id(0),m_complete(false),m_join(joinable),m_live(false)
{
    pthread_mutex_init(&m_mutex,NULL);
    pthread_cond_init(&m_cond,NULL);
}

bool Thread::start()
{
    bool ret = false;
    do
    {
        if(m_live)
        {
            break;
        }
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr,m_join ? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED);
        ret = pthread_create(&m_id,&attr,threadProc,this) == 0 ? true : false;
        pthread_attr_destroy(&attr);
    }while(false);
    return ret;
}

void* Thread::threadProc(void *arg)
{
    do 
    {
        Thread *thread = reinterpret_cast<Thread*>(arg);
        if(!thread)
        {
            break;
        }
        if(thread->live() || thread->complete())
        {
            break;
        }
        thread->setLive();
        thread->run();
        thread->setDie();
        pthread_exit(NULL);
        if(thread->join())
        {
            pthread_join(thread->id(),NULL);
        }
    }while(false);
    return NULL;
}

void Thread::add(const int task)
{
    pthread_mutex_lock(&m_mutex);
    m_task.push_back(task);
    pthread_cond_broadcast(&m_cond);
    pthread_mutex_unlock(&m_mutex);
}

void Thread::run()
{
    while(!m_complete)
    {
        pthread_mutex_lock(&m_mutex);
        while(m_task.empty())
        {
            pthread_cond_wait(&m_cond,&m_mutex);
        }
        for(auto iter = m_task.begin();iter != m_task.end();++iter)
        {
            std::cout << "id:" << m_id << " task:" << *iter << std::endl;
        }
        m_task.clear();
        pthread_mutex_unlock(&m_mutex);
    }
}

Thread::~Thread()
{
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_cond);
}


