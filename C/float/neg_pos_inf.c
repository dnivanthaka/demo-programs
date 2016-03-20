/*
 * =====================================================================================
 *
 *       Filename:  neg_pos_inf.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/05/2012 09:25:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include <stdio.h>

int main()
{
    double x = 1e-200;
    double y = 1e-200;

    printf( "Reciprocal of +0 : %g\n", 1/y );
    y = -1e-200 * x;
    printf( "Reciprocal of -0 : %g\n", 1/y );

    return 0;
}
