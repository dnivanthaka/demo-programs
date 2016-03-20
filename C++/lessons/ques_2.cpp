#include <iostream>

struct Test {
    void test_me();
};

void 
Test::test_me()
{
    std::cout << "It Works!!!" << std::endl;
}

int
main()
{
    struct Test t;
    t.test_me();

    return 0;
}
