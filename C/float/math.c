/*
 * =====================================================================================
 *
 *       Filename:  math.c
 *
 *    Description:  Floating point Arithmetic
 *
 *        Version:  1.0
 *        Created:  05/26/2013 09:25:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <math.h>

int
main( int argc, char *argv[] ){
double x = 10;
double y = sqrt(x);

double tolerance = 0.005;

y = y * y;

//if( x == y ){
if( fabs( x - y ) < tolerance ){
    printf("Square root is exact\n");
}else{
    //printf("Error = %f\n", x - y);
    printf("Error = %g\n", x - y);

}
return 0;
}
