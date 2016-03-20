#include <iostream>

struct Test {
    int m_Val;
    char s;
    void func1( struct Test *, int );
    void func2( struct Test * );
};



int
main()
{
    std::cout << sizeof( struct Test ) << std::endl;

    return 0;
}

void
Test::func1( struct Test* t, int v )
{
    t->m_Val = v;
}

void
Test::func2( struct Test* t )
{
    std::cout << "Value = " << t->m_Val << std::endl;
}
