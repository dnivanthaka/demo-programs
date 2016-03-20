/*
 * =====================================================================================
 *
 *       Filename:  screen_utils.h
 *
 *    Description:  Screen Utils
 *
 *        Version:  1.0
 *        Created:  02/20/2012 09:57:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#ifndef __SCREEN_UTILS__
#define __SCREEN_UTILS__
void screen_print( int, int, char * );
void screen_print_char( int x, int y, char );
void screen_clear();
void screen_cur_reset();
void screen_enable_echo();
void screen_disable_echo();
#endif
