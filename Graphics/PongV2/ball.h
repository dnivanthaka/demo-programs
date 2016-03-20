/*
 * =====================================================================================
 *
 *       Filename:  ball.h
 *
 *    Description:  Ball and its properties
 *
 *        Version:  1.0
 *        Created:  08/05/2012 04:08:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#ifndef __BALL_H__
#define __BALL_H__

class Ball 
{
    private:
        int m_X, m_Y, m_Width, m_Height;
        float m_VelX, m_VelY;
    public:
        Ball(int, int, int, int, float, float );
        ~Ball();

        void SetDimensions( int, int );
        void Move( float );

        int GetWidth()  { return m_Width; };
        int GetHeight() { return m_Height; };

        void SetX( int v ) { m_X = v; };
        void SetY( int v ) { m_Y = v; };

        int GetX() { return m_X; };
        int GetY() { return m_Y; };

        void SetVelX( float v ) { m_VelX = v; };
        void SetVelY( float v ) { m_VelY = v; };

        float GetVelX() { return m_VelX; };
        float GetVelY() { return m_VelY; };

        void Draw( SDL_Surface *dest );
        void Erase( SDL_Surface *dest );
};

#endif
