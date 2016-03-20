/*
 * =====================================================================================
 *
 *       Filename:  simple_boss.cpp
 *
 *    Description:  Demonstrates inheritence
 *
 *        Version:  1.0
 *        Created:  10/20/2012 12:27:45 PM
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

class Enemy
{
    public:
        int m_Damage;

        Enemy();
        void Attack() const;
};

Enemy::Enemy():
    m_Damage(10)
{}

void Enemy::Attack() const
{
    cout << "Attack inflicts" << m_Damage << " damage points!\n";
}

class Boss : public Enemy
{
    public:
        int m_DamageMultiplier;

        Boss();
        void SpecialAttack() const;
};

Boss::Boss():
    m_DamageMultiplier(3)
{}

void Boss::SpecialAttack() const
{
    cout << "Special Attack inflicts " << (m_DamageMultiplier * m_Damage);
    cout << " damage points";
}

int main()
{
    cout << "Creating an enemy.\n";

    Enemy enemy1;
    enemy1.Attack();

    cout << "\nCreating a boss.\n";
    
    Boss boss1;
    boss1.Attack();
    boss1.SpecialAttack();

    return 0;
}
