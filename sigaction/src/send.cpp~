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
            std::cout << "argc error" << std::endl;
            break;
        }
        int pidID = atol(argv[1]);
        sigval val;
        val.sival_int = 10;
        if(sigqueue(pidID,SIGINT,val))
        {
            std::cout << "siqqueue error" << std::endl;
            break;
        }
        ret = true;
    }while(false);
    return ret ? 0 : 1;
    
}
