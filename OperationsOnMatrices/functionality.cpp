#include <cstdio>
#include <conio.h>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "functionality.h"
#include "constants.h"

using namespace std;

template<typename Type>
void outputMatrix(const int *N, const int *M, Type matrix[][MAX_MATRIX_SIZE]) {
    for (int i = 0; i < *N; ++i)
        for (int j = 0; j < *M; ++j) {
            cout.precision(3);
            cout << setfill(' ') << setw(7) << matrix[i][j] << " ";
            if (j == *M - 1) printf("\n");
        }
}

