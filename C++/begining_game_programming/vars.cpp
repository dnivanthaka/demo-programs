/*
 * =====================================================================================
 *
 *       Filename:  vars.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/26/2012 06:27:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <iostream>

int main( int argc, char *argv[] )
{
    std::cout << "Size of int = " << sizeof(int) << " Bytes." << std::endl;
    std::cout << "Size of unsigned int = " << sizeof(unsigned int) << " Bytes." << std::endl;
    std::cout << "Size of short int = " << sizeof(short int) << " Bytes." << std::endl;
    std::cout << "Size of long int = " << sizeof(long int) << " Bytes." << std::endl;
    return 0;
}
