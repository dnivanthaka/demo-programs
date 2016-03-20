/*
 * =====================================================================================
 *
 *       Filename:  overriding_boss.cpp
 *
 *    Description:  Demonstrates calling and overriding base member functions
 *
 *        Version:  1.0
 *        Created:  10/20/2012 07:01:40 PM
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
        Enemy(int damage = 10);
        void virtual Taunt() const;
        void virtual Attack() const;

    private:
        int m_Damage;
};

Enemy::Enemy(int damage):
    m_Damage(damage)
{}

void Enemy::Taunt() const
{
    cout << "The enemy says he will fight you.\n";
}

void Enemy::Attack() const
{
    cout << "Attack! Inflicts " << m_Damage << " damage points.";
}

class Boss : public Enemy
{
    public:
        Boss(int damage = 30);
        void virtual Taunt() const;
        void virtual Attack() const;
};

Boss::Boss(int damage): 
    Enemy(damage)
{}


void Boss::Taunt() const
{
    cout << "The boss says he will end your pitful existance.\n";
}

void Boss::Attack() const
{
    Enemy::Attack();
    cout << "And laughs heartily at you.\n";
}

int main()
{
    cout << "Enemy object:\n";
    Enemy anEnemy;
    anEnemy.Taunt();
    anEnemy.Attack();

    cout << "\n\nBoss object:\n";
    Boss aBoss;
    aBoss.Taunt();
    aBoss.Attack();

    return 0;
}