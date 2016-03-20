/*
 * =====================================================================================
 *
 *       Filename:  hw15.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/25/2011 01:46:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include <string>

using namespace std;

class Enemy 
{
    public:
        string name;
        int strength;
        bool alive;

        // inline is not needed its now implicit
        inline bool operator == (const Enemy &e) const
        {
            return ( strength == e.strength ) && 
            ( alive == e.alive );
        }
};
