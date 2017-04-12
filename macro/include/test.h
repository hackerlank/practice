#ifndef TEST_H
#define TEST_H
#if 0
#include "base.h"
#include <iostream>
#include <new>
#include <stdlib.h>
using namespace std;
#endif



class Test
{
    public:
        Test()
        {
        }
#if 0
    public:
        static void* operator new(size_t size)
        {
            std::cout << "call new" << std::endl;
            return malloc(size);
        }
        static void operator delete(void *p)
        {
            std::cout << "fuck you" << std::endl;
        }
#endif
};

#endif
