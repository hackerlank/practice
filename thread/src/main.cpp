#include "base.h"
#include <unistd.h>

int main()
{
    Thread *thread = new Thread();
    if(thread)
    {
        thread->start();
        for(int i = 0; i < 100000;++i)
        {
            bool flag = (i % 5 == 0) ? true : false;
            thread->setLoop(flag);
        }
        thread->complete = true;
        thread->final();
    }
    return 0;
}
