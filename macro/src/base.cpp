#include "base.h"
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void* operator new(size_t size,const char *file,const size_t line)
{
    printf("file\n");
    //std::cout << "file:" << std::endl;
    return malloc(size);
}

void operator delete(void *pv)
{
    printf("fuck\n");
    //std::cout << "fuck" << std::endl;
#if 0
    std::cout << "call delete" << std::endl;
    free pv;
#endif
}


