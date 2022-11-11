#include "constants.h"
#ifndef OPERATIONSONMATRICES_FUNCTIONALITY_H
#define OPERATIONSONMATRICES_FUNCTIONALITY_H
void showMenu(int position, int N, int M, int R, int K);

long validation();

long validationWithArgument(short max);

void consoleInterface();

void showHelloMessage();

void randomizeValuesInMatrix(int N,int M, int matrix[][MAX_MATRIX_SIZE]);

void initValuesInMatrix(int N,int M, int matrix[][MAX_MATRIX_SIZE]);

void outputMatrix(int N, int M, int matrix[][MAX_MATRIX_SIZE]);

void calculateDeterminant(int N, int M, int matrix[][MAX_MATRIX_SIZE]);

void calculateInverseMatrix(int N, int M, int matrix[][MAX_MATRIX_SIZE]);

void multiplyMatrix(int firstN, int firstM, int firstMatrix[][MAX_MATRIX_SIZE], int secondN, int secondM, int secondMatrix[][MAX_MATRIX_SIZE]);

void addMatrix(int firstN, int firstM, int firstMatrix[][MAX_MATRIX_SIZE], int secondN, int secondM, int secondMatrix[][MAX_MATRIX_SIZE]);
#endif //OPERATIONSONMATRICES_FUNCTIONALITY_H
