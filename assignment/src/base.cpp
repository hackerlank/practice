#include "base.h"
#include <iostream>
#include <string.h>
using namespace std;

Base::Base(const char *val) : ptr(NULL),len(0)
{
    init(val);
    std::cout << "call Base::Base" << std::endl;
}

Base::Base(const Base &base) : ptr(NULL),len(0) 
{
    std::cout << "call Base::&Base" << std::endl;
}



Base::~Base()
{
    if(ptr)
    {
        delete ptr;
        ptr = NULL;
    }
    len = 0;
}

void Base::print() const
{
    std::cout << "ptr: " << ptr << " len:" << len << std::endl;
}

Base& Base::operator= (const Base& base)
{
    if(&base == this)
    {
        std::cout << "operator self:" << std::endl;
        return *this;
    }
    if(ptr)
    {
        delete ptr;
        ptr = NULL;
        len = 0;
    }
    const char *pt = base.getPtr();
    if(pt)
    {
        init(pt);
    }
    return *this;
}

void Base::init(const char *val)
{
    if(val)
    {
        len = strlen(val);
        ptr = new char[len + 1];
        bzero(ptr,len+1);
        strncpy(ptr,val,len);
    }
}

void Base::func() const
{
    std::cout << "Base::func" << std::endl;
}

void Derive::func() const
{
    std::cout << "Derive::func" << std::endl;
}
