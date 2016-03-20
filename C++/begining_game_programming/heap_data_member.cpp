/*
 * =====================================================================================
 *
 *       Filename:  heap_data_member.cpp
 *
 *    Description:  Demonstrates an object with a dynamically allocated data member
 *
 *        Version:  1.0
 *        Created:  09/10/2012 09:56:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>

using namespace std;

class Critter
{
    public:
        Critter(const string& name="", int age = 0);
        ~Critter();
        Critter(const Critter& c);
        Critter& Critter::operator=(const Critter& c);
        void Greet()const;
    private:
        string* m_pName;
        int m_Age;
};

Critter::Critter(const string& name, int age)
{
    cout << "Constructor called\n";
    m_pName = new string(name);
    m_Age = age;
}

Critter::~Critter()
{
    cout << "Destructor called\n";
    delete m_pName;
}

Critter::Critter(const Critter& c)
{
    cout << "Copy Constructor called\n";
    m_pName = new string( *(c.m_pName) );
    m_Age = c.m_Age;
}

Critter& Critter::operator=(const Critter& c)
{
    cout << "Overloaded Assignment Operator called\n";

    if( this != &c ){
        delete m_pName;

        m_pName = new string( *(c.mpName) );
        m_Age = c.m_Age;
    }

    return *this;
}

void Critter::Greet() const
{
    cout << "I'm " << *m_pName << " and I'm " << m_Age << " years old.\n";
    cout << "&m_pName: " << cout << &m_pName << endl;
}

void testDestructor();
void testCopyConstructor(Critter aCopy);
void testAssignmentOp();

int main()
{
    testDestructor();
    cout << endl;

    Critter crit("Poochie", 5);
    crit.Greet();
    testCopyConstructor(crit);
    crit.Greet();
    cout << endl;

    testAssignmentOp();

    return 0;
}

void testDestructor()
{

}

void testCopyConstructor(Critter aCopy)
{

}

void testAssignmentOp()
{

}
