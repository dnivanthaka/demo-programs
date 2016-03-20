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
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    int i, j, t, arr_width, arr_height;
    int row_total, column_total;
    int col_1_total = 0, 
        col_2_total = 0, 
        col_3_total = 0, 
        col_4_total = 0;

    vector< vector<int> > v;

    ifstream file("data.txt");

    if( file.is_open() ){
        file >> arr_height;
        //file.seek;
        file >> arr_width;

        for(i=0;i<arr_height;i++){
            vector<int> tmp;
            for(j=0;j<arr_width;j++){
                file >> t;
                tmp.push_back( t );    
            }
            v.push_back( tmp );
        }
        //cout << arr_height << endl;
        //cout << arr_width << endl;
        //cout << "Vector size = " << v.size() << endl;

        for(i=0;i<v.size();i++){
            row_total = 0;
            vector<int> tmp = v.at( i );
            for(j=0;j<tmp.size();j++){
                cout << "Value = " << tmp.at(j) << endl;
                row_total += tmp.at(j);
            }

            col_1_total += tmp.at( 0 );
            col_2_total += tmp.at( 1 );
            col_3_total += tmp.at( 2 );
            col_4_total += tmp.at( 3 );

            cout << "Row " << i + 1 << " total = " << row_total << endl;
        }

        cout << "Column 1 total = " << col_1_total << endl;
        cout << "Column 2 total = " << col_2_total << endl;
        cout << "Column 3 total = " << col_3_total << endl;
        cout << "Column 4 total = " << col_4_total << endl;

        file.close();
    }else{
        cout << "Error opening input file." << endl;
    }


    return 0;
}
