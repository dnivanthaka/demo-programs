/*
 * =====================================================================================
 *
 *       Filename:  polymorphic_bad_guy.cpp
 *
 *    Description:  Demonstrate calling member functions dynamically
 *
 *        Version:  1.0
 *        Created:  09/12/2012 09:04:52 PM
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
        virtual ~Enemy();
        void virtual Attac() const;
    protected:
        int *m_pDamage;
};

Enemy::Enemy(int damage)
{
    m_pDamage = new int(damage);
}

Enemy::~Enemy()
{
    cout << "In Enemy destructor, deleting m_pDamage\n";
    delete m_pDamage;
    m_pDamage = 0;
}

void Enemy::Attack() const
{
    cout << "An enemy attacks and inflicts " << *m_pDamage << " Damage points";
}

class Boss : public Enemy
{
    public:
        Boss(int multiplier = 3);
        virtual ~Boss();
        void virtual Attack() const;

    protected:
        int *m_pMultiplier;

};

Boss::Boss(int multiplier)
{
    m_pMultiplier = new int(multiplier);
}

Boss::~Boss()
{
    cout << "In Boss Destructor, deleting m_pMultiplier\n";
    delete m_pMultiplier;
    m_pMultiplier = 0;
}

void Boss::Attack const
{
    cout << "A boss attacks and inflicts " << (*m_pDamage) * (m_pMultiplier);
        << " damage points.";
}
