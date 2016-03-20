/*
 * =====================================================================================
 *
 *       Filename:  hw5.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/24/2011 06:57:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

void rotate1( int *a, int *b, int *c )
{
    int tmp;

    tmp = *c;
    *c = *b;
    *b = *a;
    *a = tmp;
}
void rotate2( int &a, int &b, int &c )
{
    int tmp;

    tmp = c;
    c = b;
    b = a;
    a = tmp;
}

int main(int argc, char **argv)
{
    int a, b, c;

    a = 1;
    b = 2;
    c = 3;

    //rotate1( &a, &b, &c );
    rotate2( a, b, c );

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    return 0;
}
