/*
 * =====================================================================================
 *
 *       Filename:  game_lobby.cpp
 *
 *    Description:  Simulates a Game Lobby where players wait
 *
 *        Version:  1.0
 *        Created:  09/14/2012 10:56:24 PM
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

class Player
{
    public:
        Player(const string& name = "");
        string GetName() const;
        Player* GetNext() const;
        void SetNext(Player* next);

    private:
        string m_Name;
        Player* m_pNext;
};

Player::Player(const string& name):m_Name(name), m_pNext(0)
{}

string Player::GetName() const
{
    return m_Name;
}

Player* Player::GetNext const
{
    return m_pNext;
}

void Player::SetNext(Player* next)
{
    m_pNext = next;
}

class Lobby
{
    friend ostream& operator<<(ostream& os, const Lobby& aLobby);

    public:
        Lobby();
        ~Lobby();
        void AddPlayer();
        void RemovePlayer();
        void Clear();
    private:
        Player* m_pHead;
};

void Lobby::AddPlayer()
{
    cout << "Please enter the name of the player: ";
    string name;
    cin >> name;
    Player* pNewPlayer = new Player(name);

    if(m_pHead == 0)
    {
        m_pHead = pNewPlayer;
    }else
    {
        Player* pIter = m_pHead;
        while( pIter-> GetNext() != 0  )
        {
            pIter = pIter->GetNext();
        }

        pIter->SetNext( pNewPlayer );
    }
}

void Lobby::RemovePlayer()
{
    if( m_pHead == 0 )
    {
        cout << "The game lobby is empty. No one to remove!\n";
    }else
    {
        Player* pTemp = m_pHead;
        m_pHead = m_pHead->GetNext();
        delete pTemp;
    }
}

void Lobby::Clear()
{
    while( m_pHead != 0 )
    {
        RemovePlayer();
    }
}

ostream& operator<<(ostream& os, const Lobby& aLobby)
{
    Player* pIter = aLobby.m_pHead;
    os << "\nHere's who's in the game lobby:\n";
    if( pIter == 0 )
    {
        os << "The lobby is empty\n";
    }
    else
    {
        while( pIter != 0 )
        {
            os << pIter->GetName() << endl;
            pIter = pIter->GetNext();
        }
    }

    return os;
}
