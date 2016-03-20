/*
 * =====================================================================================
 *
 *       Filename:  private_critter.cpp
 *
 *    Description:  Demonstrates static member variables and functions 
 *
 *        Version:  1.0
 *        Created:  09/09/2012 12:13:11 AM
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

class Critter
{
    public:
        static int s_Total;

        Critter(int hunger = 0);
        static int GetTotal();
        Critter& ostream& operator<<( ostream& os );
        //Critter& ostream& operator<<( ostream& os, const Critter& aCritter );
    private:
        int m_Hunger;
        string m_Name;

};

int Critter::s_Total = 0;

Critter::Critter(int hunger):
    m_Hunger(hunger)
{
    cout << "A critter has been born!";
    ++s_Total;
}

int Critter::GetTotal()
{
    return s_Total;
}

ostream& Critter::operator<<( ostream& os )
{
    os << "Critter Object - ";
    os << "m_Name: " << aCritter.m_Name;
    return os;
}

int main()
{
    cout << "The total number of critters is: ";
    cout << Critter::s_Total << "\n\n";

    Critter crit1, crit2, crit3;

    cout << "\nThe total number of critters is: ";
    cout << Critter::GetTotal() << "\n";

    return 0;
}
