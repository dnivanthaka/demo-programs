/*
 * =====================================================================================
 *
 *       Filename:  Strategy.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/25/2011 11:27:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#ifndef __STRATEGY_H__
#define __STRATEGY_H__

class Strategy 
{
   public:
        // = 0 to make it pure virtual
        virtual int rand( int ) = 0;
};

#endif
