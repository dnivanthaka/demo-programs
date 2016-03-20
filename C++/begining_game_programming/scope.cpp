/*
 * =====================================================================================
 *
 *       Filename:  scope.cpp
 *
 *    Description:  Variable scoping Demonstration
 *
 *        Version:  1.0
 *        Created:  09/02/2012 11:02:28 PM
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

void func();

int main(int argc, char *argv[])
{
    int var = 5;
    cout << "In main var is: " << var << "\n";

    func();

    cout << "Back in main() var is: " << var << "\n\n";

    {
        cout << "In main() in a new scope var is: " << var << "\n\n";
        cout << "Creating new var in new scope.\n";
        int var = 10;

        cout << "In main() in a new scope var is: " << var << "\n\n";
    }

    cout << "At end of main() var created in a new scope no longer exists.\n";
    cout << "At end of main() var is: " << var << "\n";

    return 0;
}

void func()
{
    int var = -5;
    cout << "In func() var is: " << var << "\n\n";
}
