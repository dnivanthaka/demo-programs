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

bool equals(int *array1, int *array2, int size)
{
    bool is_equal;

    for(int i=0;i<size;i++){
        if( array1[i] != array2[i] )
            is_equal = false;
    }

    return is_equal;
}

int main(int argc, char **argv)
{
    int a, b, c;

    a = 1;
    b = 2;
    c = 3;

    //rotate1( &a, &b, &c );
    //rotate2( a, b, c );

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    return 0;
}
