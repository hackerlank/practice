#include "base.h"
#include <iostream>
using namespace std;
int main()
{
#if 0
    Base base1("1");
    base1.print();
    {
        Base base2("2");
        base2.print();
        base1 = base2;
    }
    base1.print();
    base1 = base1;
    base1.print();
#endif

#if 0
    Derive derive("3");
    derive.print();
    Base *base = &derive;
    *base = (derive);
    base->print();
    base->func();
    (*base).func();
    Derive *temp = dynamic_cast<Derive*>(base);
    if(temp)
    {
        temp->func();
    }
    std::cout << "end!" << std::endl;
#endif

    const Derive derive("4");
    derive.print();
    static_cast<Derive>(derive).func();




    
    
    
    


    return 0;
}



