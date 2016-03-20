/*
 * =====================================================================================
 *
 *       Filename:  person.cpp
 *
 *    Description:  person
 *
 *        Version:  1.0
 *        Created:  05/04/2013 01:16:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include "person.h"


extern const int CONST_VAL;
extern int global_var;

void change_name( struct record *rec, const char *new_name )
{
    int i;
    //printf("%d\n", CONST_VAL);
    i = CONST_VAL;
    i++;
    i = global_var;
    strcpy( rec->name, new_name );
}
