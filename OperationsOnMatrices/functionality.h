#include "constants.h"
#include <windows.h>

#ifndef OPERATIONSONMATRICES_FUNCTIONALITY_H
#define OPERATIONSONMATRICES_FUNCTIONALITY_H

long validation();

long validationWithArgument(short min, short max);

void consoleInterface();

void showMenu(int position, const int *N, const int *M, const int *R, const int *K);

void showHelloMessage();

void randomizeValuesInMatrix(const int *N, const int *M, int **matrix);

void initValuesInMatrix(const int *N, const int *M, int **matrix);

void transposeMatrix(const int *N, const int *M, int **matrix);

void outputMatrix(const int *N, const int *M, int **matrix);

void calculateAdditionMatrix(const int *N, int **matrix, int **additionMatrix);

void initMatrixValue(const int *N, const int *M, int **matrix, int valueForInit);

void createMatrix(int &N, int &M, int **matrix);

void outputMatrixWhenInit(const int *N, const int *M, int **matrix);

int calculateDeterminant(int **M, int N);

int **getM(int **M, int N, int k);

void choice(char &YN);

template<typename Type>
Type **createPointerToMatrix(int N);

void calculateInverseMatrix(const int *N, const int *M, int D, int **matrix);

void multiplyMatrix(const int *firstN, const int *firstM, int **firstMatrix, const int *secondN,
                    const int *secondM,
                    int **secondMatrix);

void addOrSubtractMatrix(const int *firstN, const int *firstM, int **firstMatrix, const int *secondN,
                         const int *secondM,
                         int **secondMatrix);

#endif //OPERATIONSONMATRICES_FUNCTIONALITY_H
