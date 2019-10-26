/* Matrix Multiplication - OpenMP version
 * Group members: Emmy Woods, Chris Cornell, Brandon Roth
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 1000
#define NUM_MAX 10
#define NUMT 100  // how many threads?

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

// dividing up the work. Currently this only works if the work can be evenly
// divided between the threads. 
void *ThreadWork(void *param){
    long threadNum = (long) param;
    int workPerThread = SIZE / NUMT;
    for (int i = threadNum * workPerThread; i < (threadNum+1) * workPerThread; i++){
        //printf("i: %d, threadNum: %d\n", i, threadNum);
        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < SIZE; k++){
              result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

// multiply two matrices
void multiply(int m1[SIZE][SIZE], int m2[SIZE][SIZE], int result[SIZE][SIZE]){
    pthread_t tid[NUMT];
    long i;
    void *status;

    for (i = 0; i < NUMT; i++){
        pthread_create(&tid[i], NULL, ThreadWork, (void *)i);
    }

    // join all the threads
    for(i = 0; i < NUMT; i++){
        pthread_join (tid[i], &status);
    }
}

int main(){
//    srand(time(0));
    fillMatrix(m1);
    fillMatrix(m2);
    multiply(m1, m2, result);

    // 
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
