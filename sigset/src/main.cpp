#include <iostream>
using namespace std;
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
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

