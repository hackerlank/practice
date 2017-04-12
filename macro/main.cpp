#include <iostream>
#include <cassert>
#include <stdlib.h>
using namespace std;

class A
{
};


void* operator new(size_t size)
{
    std::cout << "new" << std::endl;
    return malloc(size);
}

void operator delete(void *pv)
{
    std::cout << "delete" << std::endl;
    free(pv);
}

int main()
{
    A *ptr = new A();
    delete ptr;
    return 0;
}


