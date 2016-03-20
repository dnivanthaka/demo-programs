/*
 * =====================================================================================
 *
 *       Filename:  person.h
 *
 *    
 *
 *        Version:  1.0
 *        Created:  05/04/2013 01:21:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include <string.h>
#include "consts.h"

struct record{
    int emp_id;
    char name[100];
    unsigned short age;
};

void change_name( struct record *, const char * );
