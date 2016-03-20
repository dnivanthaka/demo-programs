/*
 * =====================================================================================
 *
 *       Filename:  Button.h
 *
 *    Description:  Button Definition Header
 *
 *        Version:  1.0
 *        Created:  12/24/2011 09:35:54 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#ifndef __BUTTON_DEF__
#define __BUTTON_DEF__
    class Button 
    {
        private:
            SDL_Rect box;

            SDL_Rect *clip;

        public:
            Button( int x, int y, int w, int h );

            void handle_events();

            void show();

    }
#endif
