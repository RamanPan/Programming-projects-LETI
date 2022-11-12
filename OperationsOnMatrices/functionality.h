#include "constants.h"
#include <windows.h>

#ifndef OPERATIONSONMATRICES_FUNCTIONALITY_H
#define OPERATIONSONMATRICES_FUNCTIONALITY_H

long validation();

long validationWithArgument(short min, short max);

void consoleInterface();

void showMenu(int position, const int *N, const int *M, const int *R, const int *K);

void showHelloMessage();

void randomizeValuesInMatrix(const int *N, const int *M, int matrix[][MAX_MATRIX_SIZE]);

void initValuesInMatrix(const int *N, const int *M, int matrix[][MAX_MATRIX_SIZE]);

void transposeMatrix(const int *N, const int *M, int matrix[][MAX_MATRIX_SIZE]);

void outputMatrix(const int *N, const int *M, int matrix[][MAX_MATRIX_SIZE]);

void calculateAdditionMatrix(const int *N, int matrix[][MAX_MATRIX_SIZE], int additionMatrix[][MAX_MATRIX_SIZE]);

void initHollowMatrix(const int *N, const int *M, int matrix[][MAX_MATRIX_SIZE]);

void createMatrix(int &N, int &M, int matrix[][MAX_MATRIX_SIZE]);

int calculateDeterminant(int **M, int N);

int **getM(int **M, int N, int k);

void choice(char &YN);

int **castToPointer(int N, int M, int matrix[][MAX_MATRIX_SIZE]);

void calculateInverseMatrix(const int *N, const int *M, int D, int matrix[][MAX_MATRIX_SIZE]);

void multiplyMatrix(const int *firstN, const int *firstM, int firstMatrix[][MAX_MATRIX_SIZE], const int *secondN,
                    const int *secondM,
                    int secondMatrix[][MAX_MATRIX_SIZE]);

void addOrSubtractMatrix(const int *firstN, const int *firstM, int firstMatrix[][MAX_MATRIX_SIZE], const int *secondN,
               const int *secondM,
               int secondMatrix[][MAX_MATRIX_SIZE]);

#endif //OPERATIONSONMATRICES_FUNCTIONALITY_H
