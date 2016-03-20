/*
 * =====================================================================================
 *
 *       Filename:  abstract_creature.cpp
 *
 *    Description:  Demonstrates Abstract Classes
 *
 *        Version:  1.0
 *        Created:  09/13/2012 08:50:33 PM
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

class Creature
{
    public:
        Creature(int health = 100);
        virtual void Greet() const = 0;
        virtual void DisplayHealth() const;
    protected:
        int m_Health;
};

Creature::Creature(int health) : m_Health(health)
{}

void Creature::DisplayHealth() const
{
    cout << "Health : " << m_Health << endl;
}

class Orc : public Creature
{
    public:
        Orc(int Health = 120);
        virtual void Greet() const;
};

Orc::Orc(int health) : Creature(health)
{}

void Orc::Greet() const
{
    cout << "The orc grunts hello.\n";
}

int main()
{
    Creature *pCreature = new Orc();
    pCreature->Greet();
    pCreature->DisplayHealth();

    return 0;
}
