#include <iostream>
#include <signal.h>
#include <stdlib.h>
using namespace std;

int main(int argc,char *argv[])
{
    bool ret = false;
    do
    {
        if(argc < 2)
        {
            std::cout << "argc error:" << std::endl;
            break;
        }
        int pidID = atol(argv[1]);
        for(int i = 0;i < 500;i++)
        {
            kill(pidID,SIGRTMIN+5);
        }
        ret = true;
    }while(false);
    return ret ? 0 : 1;
    
}
