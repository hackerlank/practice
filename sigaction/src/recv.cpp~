#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void processSig(int signum,siginfo_t *info,void *cont)
{
    std::cout << "process signum:" << signum << "sendPid:" << info->si_pid << "val:" << info->si_int << std::endl;
}

int main()
{
    bool ret = false;
    do
    {
        std::cout << "pidID:" << getpid() << std::endl;
        struct sigaction action;
        action.sa_flags = SA_SIGINFO;
        sigemptyset(&action.sa_mask);
        action.sa_sigaction = &processSig;
        if(sigaction(SIGINT,&action,NULL))
        {
            std::cout << "sigaction error" << std::endl;
            break;
        }
        ret = true;
        pause();
    }while(false);
    return ret ? 0 : 1;
}
