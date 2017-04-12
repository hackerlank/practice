#include <iostream>
using namespace std;
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
unsigned int accept = 0;

void processSig(int signum)
{
    sigset_t sig;
    sigemptyset(&sig);
    sigpending(&sig);
    std::cout << "begin ismember:" << sigismember(&sig,signum) << std::endl; 
    accept += 1;
    std::cout << "signum:" << signum << " accept:" << accept << std::endl;
    sigemptyset(&sig);
    sigpending(&sig);
    std::cout << "end ismember:" << sigismember(&sig,signum) << std::endl; 
}

int main()
{
   bool ret = false;
   do
   {
#if 0
       //这里是屏蔽
       sigset_t sig;
       sigemptyset(&sig);
       sigaddset(&sig,SIGINT);
       pthread_sigmask(SIG_SETMASK,&sig,NULL);
#endif
       //实时信号跟标准信号不一样
       if(signal(SIGRTMIN+5,processSig) == SIG_ERR)
       {
           std::cout << "signal error" << std::endl;
           break;
       }
       std::cout << "processID:" << getpid() << std::endl;
       pause();
       ret = true;
   }while(false);
   return ret ? 0 : 1;
}

#if 0
int main()
{
    sigset_t sig;
    sigfillset(&sig);
    sigaddset(&sig,SIGUSR1);
    pthread_sigmask(SIG_SETMASK,&sig,NULL);
    int val = 0;
    if(!sigwait(&sig,&val))
    {
        std::cout << "wait sig:" << val << std::endl;
    }
    std::cout << "fuck you !" << std::endl;
    pause();
    return 0;
}
#endif

