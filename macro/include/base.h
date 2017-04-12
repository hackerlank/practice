#ifndef BASE_H
#define BASE_H
#include<cstddef>

void* operator new(size_t size,const char *file,const size_t line); 
void operator delete(void *pv);
#define New new(__FILE__,__LINE__)

#endif

