#ifndef FUNC_H
#define FUNC_H
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef DEBUG
#define DEBUG
#endif

#ifdef DEBUG
extern void* operator new (const size_t size,const char *file,const size_t line);
extern void operator delete(void *ptr);
#define Debug_New new(__FILE__,__LINE__)
#else
#define Debug_New new
#endif

#define Delete(x)\
{\
    if(x)\
    {\
        delete x;\
        (x) = NULL;\
    }\
}

#endif
