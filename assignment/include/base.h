#ifndef BASE_H
#define BASE_H
#include <stddef.h>
class Base
{
    private:
        char *ptr;
        size_t len;
    public:
        Base(const char *val);
        Base(const Base &base);
        void print() const;
        ~Base();
        Base& operator= (const Base& base);
        const char* getPtr() const
        {
            return ptr;
        }
        void init(const char *ptr);
        virtual void func() const;

};

class Derive : public Base
{
    public:
        Derive(const char *val) : Base(val)
        {
        }
        void func() const;
};

#endif



