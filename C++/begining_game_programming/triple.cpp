/*
 * =====================================================================================
 *
 *       Filename:  triple.cpp
 *
 *    Description:  Demonstrates function overloading
 *
 *        Version:  1.0
 *        Created:  09/04/2012 09:19:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>

using namespace std;

int triple(int number);
string triple(string text);

int main()
{
    cout << "Tripling 5: " << triple(5) << "\n\n";
    cout << "Tripling 'gamer': " << triple("gamer");

    return 0;
}

int triple( int number )
{
    return (number * 3);
}

int triple( string text )
{
    return ( text + text + text );
}
