/*
 * =====================================================================================
 *
 *       Filename:  hw14.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/25/2011 12:52:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>

using namespace std;

int 
main( int argc, char **argv )
{
    int i, vec_size, tmp, sum_part = 0;

    vector<int> list;
    // no size specified: vector contains no elements

    cout << "Enter the vector size: " << flush;
    cin >> vec_size;

    //list.resize( vec_size );

    for(i=0;i<vec_size;i++){
        cout << "Enter number " << (i + 1) << ": " << flush;
        cin >> tmp;
        list.push_back( tmp );
        //list.insert( i, tmp );
    }

    cout << "Partial sums: "; 
    for( vector<int>::iterator i = list.begin();
         i != list.end();
         i++){
        sum_part += *i;
        cout << " " << sum_part;  
        //cout << *i << endl;     
    }

    cout << endl;
    
    return 0;
}
