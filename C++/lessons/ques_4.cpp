#include <iostream>

struct Test {
    int m_Val;
};

void func1( struct Test *, int );
void func2( struct Test * );

int
main()
{
    struct Test t;
    t.m_Val = 1;

    func1( &t, 5 );
    func2( &t );

    return 0;
}

void
func1( struct Test* t, int v )
{
    t->m_Val = v;
}

void
func2( struct Test* t )
{
    std::cout << "Value = " << t->m_Val << std::endl;
}
