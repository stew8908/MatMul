/* Matrix Multiplication - OpenMP version
 * Group members: Emmy Woods, Chris Cornell, Brandon Roth
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 1000
#define NUM_MAX 10

/* The three arrays to hold matrices are global variables. I had them declared insi$
 * the main function, but the largest matrix I could use that way was 835x835.
 * This is due to a user limit of 8192 mebibytes on the stack, found with ulimit -a.
 * By making them global variables, I've taken them out of main's stack frame, and
 * put them into the data segment, which is unlimited in size.
 */
int m1[SIZE][SIZE]; // matrix 1
int m2[SIZE][SIZE]; // matrix 2
int result[SIZE][SIZE] = {0}; // result matrix

// print a matrix
void printMatrix(int matrix[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// fill a matrix with random numbers
void fillMatrix(int matrix[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            matrix[i][j] = rand() % NUM_MAX;
        }
    }
}

// multiply two matrices
void multiply(int m1[SIZE][SIZE], int m2[SIZE][SIZE], int result[SIZE][SIZE]){
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++){
        #pragma omp parallel for
        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < SIZE; k++){
              result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

int main(){
//    srand(time(0));
    fillMatrix(m1);
    fillMatrix(m2);
    multiply(m1, m2, result);

    printf("square matrix size: %d, random numbers under: %d\n", SIZE, NUM_MAX);

    /* uncomment to print matrices
    printf("Matrix 1:\n");
    printMatrix(m1);
    printf("Matrix 2:\n");
    printMatrix(m2);
    printf("Result matrix:\n");
    printMatrix(result);
    */
}
