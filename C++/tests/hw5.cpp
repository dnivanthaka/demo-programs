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

void maxmin( double *a, double &min, double &max, int size )
{
    for(int i=0;i<size;i++){
       if(i == 0){
           min = a[i];
           max = a[i];
           continue;
       }

       if( a[i] > max )
           max = a[i];
       if( a[i] < min )
           min = a[i];
    }
}

int main(int argc, char **argv)
{
    double min, max;
    double a[5] = { 11.1, 5.3, 7.3, -1.5, -6.5 };

    maxmin( a, min, max, 5 );

    cout << "Max = " << max << endl;
    cout << "Min = " << min << endl;

    return 0;
}
