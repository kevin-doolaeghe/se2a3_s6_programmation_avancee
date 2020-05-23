#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------

#define SIZE 1448

//----------------------------------------------

void ex1() {
    int M[SIZE][SIZE];
    init_matrice(M); // Limite SIZE = 1447

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            M[i][j] = i + j;
        }
    }

    //----------------

    int *v = malloc (SIZE * sizeof(int));

    for (int i = 0; i < SIZE; i++) {
        v[i] = i * i;
    }

    free(v);

    //----------------

    int **mat = malloc(SIZE * sizeof(int *));

    for (int i = 0; i < SIZE; i++) {
        mat[i] = malloc(SIZE * sizeof(int));
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mat[i][j] = i + j;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        free(mat[i]);
        mat[i] = NULL;
    }

    free(mat);
    mat = NULL;
}

void ex2() {
    int **mat = malloc(SIZE * sizeof(int *));

    for (int i = 0; i < SIZE; i++) {
        mat[i] = malloc(SIZE * sizeof(int));
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mat[i][j] = i + j;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        free(mat[i]);
        mat[i] = NULL;
    }

    free(mat);
    mat = NULL;
}

//----------------------------------------------

int main()
{
    printf("Allocation dynamique\n====================\n");

    printf("\nExercice n°1\n============\n\n");
    ex1();

    printf("\nExercice n°2\n============\n\n");
    ex2();

    return 0;
}
