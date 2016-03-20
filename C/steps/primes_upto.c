/*
 * primes_upto.c
 *
 * Displays all the prime numbers up to and including 1000, using
 * the famous algorithm of Erathostenes. This is a C99 program,
 * not a C90 program
 */

#include <stdio.h>
#include <stdbool.h>

#define SIZE 1001
bool sieve[SIZE];

void fillArray(bool s[], bool value, int n){
    for(int i=0;i<n;i++){
        s[i] = value;
    }
}

void checkOffComposites(bool s[], int n){
    s[0] = false;
    s[1] = false;

    for(int i =2;i * i < n; i++){
        if(s[i]){
            for(int j = i+i;j<n;j+= i){
                s[j] = false;
            }
        }
    }
}


void displayTrueIndices(bool s[], int n){
    for(int i=0;i<n;i++){
        if(s[i]){
            printf( "%8d", i );
        }
    }

    printf("\n");
}

int main(){
    fillArray( sieve, true, SIZE );
    checkOffComposites( sieve, SIZE );
    displayTrueIndices( sieve, SIZE );
    return 0;
}
