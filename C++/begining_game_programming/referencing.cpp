/*
 * =====================================================================================
 *
 *       Filename:  referencing.cpp
 *
 *    Description:  Demonstrates using references
 *
 *        Version:  1.0
 *        Created:  09/04/2012 10:25:53 PM
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

int main()
{
    int myScore = 1000;
    int &mikesScore = myScore;

    cout << "myScore is: " << myScore << "\n";
    cout << "mikesScore is: " << mikesScore << "\n\n";
    cout << "Adding 500 to myScore\n";
    myScore += 500;

    cout << "myScore is: " << myScore << "\n";
    cout << "mikesScore is: " << mikesScore << "\n\n";

    cout << "Adding 500 to mikesScore\n";
    mikesScore += 500;

    cout << "myScore is: " << myScore << "\n";
    cout << "mikesScore is: " << mikesScore << "\n\n";
    
    return 0;
}