/*
 * =====================================================================================
 *
 *       Filename:  paddle.cpp
 *
 *    Description: Paddle and its properties  
 *
 *        Version:  1.0
 *        Created:  08/05/2012 04:07:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include "SDL/SDL.h"

#include "globals.h"
#include "paddle.h"


Paddle::Paddle( int x, int y, int w, int h, float xv, float yv )
{
    m_X = x;
    m_Y = y;
    m_Width  = w;
    m_Height = h;
    m_VelX = xv;
    m_VelY = yv;
}

Paddle::~Paddle(){}

void Paddle::Move( float dt )
{
    // dt is in milliseconds
    m_X += m_VelX * ( dt / 1000.f );
    m_Y += m_VelY * ( dt / 1000.f );
}

void Paddle::Draw( SDL_Surface *dest )
{
    SDL_Rect tmp;

    tmp.w = m_Width;
    tmp.h = m_Height;
    tmp.x = m_X;
    tmp.y = m_Y;

    SDL_FillRect( dest, &tmp, SDL_MapRGB( dest->format, 0xFF, 0xFF, 0xFF ) );
}

void Paddle::Erase( SDL_Surface *dest )
{
    SDL_Rect tmp;

    tmp.w = m_Width;
    tmp.h = m_Height;
    tmp.x = m_X;
    tmp.y = m_Y;

    SDL_FillRect( dest, &tmp, SDL_MapRGB( dest->format, 0x00, 0x00, 0x00 ) );
}

