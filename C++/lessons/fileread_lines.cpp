#include <iostream>
#include <fstream>
#include <string>


int 
main()
{
    std::ifstream file("test.txt");
    std::string word;

    if( ! file ){
        std::cerr << "Error opening file" << std::endl;
        return -1;
    }

    while( file >> word )
        std::cout << word << std::endl;

    return 0;
}
