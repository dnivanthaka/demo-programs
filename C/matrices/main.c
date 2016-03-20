#include <stdio.h>

void multiply( int (*)[], int (*)[], int (*)[] );
void transpose( int (*)[], int (*)[] );

int
main( int argc, char *argv[] )
{
    int i, j;

    int mat_a[2][2] = {
                        {1, 2},
                        {3, 4}
                      };
    int mat_b[2][2] = {
                        {5, 6},
                        {7, 8}
                      };

    //int (*mat_c)[];
    int mat_c[2][2] = {
                        {0, 0},
                        {0, 0}
                      };

    /*
    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            printf("%d ", mat_a[i][j]);
        }
    }
    */

    printf("\n%d\n", (int)sizeof(mat_a[0][0]));
    //multiply( mat_a, mat_b, mat_c );
    transpose(mat_a, mat_c);

    return 0;
}

// Calculates the dot product matix
void
multiply( int (*mat_a)[2], int (*mat_b)[2], int (*mat_c)[2] )
{
    // mat_c = mat_a * mat_b

    int i, j, k;

    //for(i=0;i<2;i++){
    //    for(j=0;j<2;j++){
    //        printf("%d ", mat_a[i][j]);
    //    }
    //}
    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            //printf("%d ", mat_a[i][j]);
            for(k=0;k<2;k++){
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
            }
        }
    }
    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            printf("%d ", mat_c[i][j]);
        }
    }
}

void
transpose(int (*mat_a)[2], int (*mat_c)[2])
{
    int i, j;

    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            mat_c[i][j] = mat_a[j][i];
        }
    }
    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            printf("%d ", mat_c[i][j]);
        }
    }
}

void
vector_multiplication(int (*mat_a)[2], int (*mat_b)[2])
{
    // mat_b is the column vector matrix
}
