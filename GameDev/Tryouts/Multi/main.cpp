/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Test Main
 *
 *        Version:  1.0
 *        Created:  05/04/2013 12:14:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>

#include "consts.h"
#include "person.h"

int main( int argc, char *argv[])
{
    struct record rec1;

    printf("%d\n\n", CONST_VAL);

    rec1.emp_id = 1;
    strcpy(rec1.name, "Test User");
    rec1.age = 25;

    char *n = "Test Username";

    change_name( &rec1, const_cast<char *>(n) );

    printf("emp_id = %d\n", rec1.emp_id);
    printf("name   = %s\n", rec1.name);
    printf("age    = %d\n", rec1.age);

    return 0;
}
