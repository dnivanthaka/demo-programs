/*
 * =====================================================================================
 *
 *       Filename:  rand.cpp
 *
 *    Description:  Electronic Dice
 *
 *        Version:  1.0
 *        Created:  08/29/2012 08:59:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    srand( static_cast<unsigned int>(time(0)) );
    int randomNumber = (rand() % 6) + 1;

    cout << "Electronic Dice Demo" << endl;
    cout << "You rolled " << randomNumber << endl;
    cout << RAND_MAX << endl;

    return 0;
}
