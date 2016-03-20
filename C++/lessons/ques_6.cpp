#include <iostream>

class Test {
    private:
    int m_Val;

    public:
    void func1();
    void func2();
};

void
Test::func1()
{
    std::cout << "Setting value" << std::endl;
    this->m_Val = 5;
    std::cout << "Calling Member 2" << std::endl;
    this->func2();
}

void
Test::func2()
{
    std::cout << "In function2" << std::endl;
}



int
main()
{
    class Test t;

    t.func1();

    return 0;
}
