/*
 * pi.c
 *
 * Makes an approximation to pi by generating
 * a million random points in the unit square and
 * computing the ratio of those inside the unit
 * circle to the total number in the square
 * That value should be pretty close to Pi/4.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// This should be a parameter
#define NUMBER_OF_PROBES 1000000

double squareOfDistanceToOrigin( double x, double y ){
    return x * x + y * y;
}

// Returns a random value in (-1..1)
double randomValue(){
    return 2.0 * rand() / RAND_MAX - 1.0;
}

int main(){
    int i;
    int inside = 0;

    for(i=0;i<NUMBER_OF_PROBES;i++){
        double x = randomValue();
        double y = randomValue();

        if(squareOfDistanceToOrigin(x, y) < 1.0){
            inside++;
        }
    }

    printf( "Pi is about %12.10f (actual to 10 digits is %12.10f)\n",
        4.0 * ((double)inside / NUMBER_OF_PROBES), M_PI );

    return 0;
}
