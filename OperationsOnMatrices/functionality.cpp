#include <cstdio>
#include <conio.h>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "functionality.h"
#include "constants.h"

using namespace std;

template<typename Type>
void outputMatrix(const int *N, const int *M, Type **matrix) {
    for (int i = 0; i < *N; ++i)
        for (int j = 0; j < *M; ++j) {
            cout.precision(3);
            cout << setfill(' ') << setw(7) << matrix[i][j] << " ";
            if (j == *M - 1) printf("\n");
        }
}

void outputMatrixWhenInit(const int *N, const int *M, int **matrix) {
    for (int i = 0; i < *N; ++i)
        for (int j = 0; j < *M; ++j) {
            if (matrix[i][j] != STAR) {
                cout.precision(3);
                cout << setfill(' ') << setw(7) << matrix[i][j] << " ";
                if (j == *M - 1) printf("\n");
            } else {
                cout.precision(3);
                cout << setfill(' ') << setw(7) << "*" << " ";
                if (j == *M - 1) printf("\n");
            }
        }
}

void showHelloMessage() {
    printf("Приветствую!\n");
    printf("В этой программе вы можете произвести некоторые полезные действия над матрицами!\n");
}

void showMenu(int position, const int *N, const int *M, const int *R, const int *K) {
    system("cls");
    printf("Выберите действие:\n");
    printf("1) Посмотреть значения в матрицах%s\n", position == 1 ? " <--" : " ");
    printf("2) Сложить/Вычесть матрицы%s\n", position == 2 ? " <--" : " ");
    printf("3) Умножить матрицы в порядке A*B%s\n", position == 3 ? " <--" : " ");
    printf("4) Умножить матрицы в порядке B*A%s\n", position == 4 ? " <--" : " ");
    printf("5) Транспонировать матрицы%s\n", position == 5 ? " <--" : " ");
    printf("6) Посчитать определитель%s\n", position == 6 ? " <--" : " ");
    printf("7) Посчитать обратную матрицу%s\n", position == 7 ? " <--" : " ");
    printf("8) Ввести(сгенерировать или вручную) первую матрицу по новой%s\n", position == 8 ? " <--" : " ");
    printf("9) Ввести(сгенерировать или вручную) вторую матрицу по новой%s\n", position == 9 ? " <--" : " ");
    printf("0) Выход%s\n", position == 10 ? " <--" : " ");
    printf("Размерность первой матрицы: %dx%d\n", *N, *M);
    printf("Размерность первой матрицы: %dx%d\n", *R, *K);
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}

void choice(char &YN) {
    bool exit = false;
    while (!exit) {
        YN = (char)getchar();
        fflush(stdin);
        if (YN == '1' || YN == '2') exit = true;
        else if (YN != ENTER) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неверный ввод! Значение должно быть либо 1, либо 2 \n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
    }
}

long validation() {
    bool validationFlag = false;
    double result;
    while (!validationFlag) {
        if (scanf("%lf", &result)) {
            if (!checkOverflow(result)) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("Неправильный ввод! Число вышло за границу дозволенного! Попробуйте снова!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            } else validationFlag = true;
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неправильный ввод! Попробуйте снова!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
        fflush(stdin);
    }
    return (long) result;
}

long validationWithArgument(short min, short max) {
    long result;
    do {
        result = validation();
        if (result > max || result < min) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неверный ввод! Значение должно быть от %hd до %hd\n", min,
                   max);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
    } while (result > max || result < min);
    return result;
}

void initMatrixValue(const int *N, const int *M, int **matrix, int valueForInit) {
    for (int i = 0; i < *N; i++)
        for (int j = 0; j < *M; j++)
            matrix[i][j] = valueForInit;
}

void createMatrix(int &N, int &M, int **matrix) {
    char YN;
    printf("Введите кол-во строк\n");
    N = validationWithArgument(MIN_MATRIX_SIZE, MAX_MATRIX_SIZE);
    printf("Введите кол-во столбцов \n");
    M = validationWithArgument(MIN_MATRIX_SIZE, MAX_MATRIX_SIZE);
    printf("Сгенерировать значения матрицы или ввести вручную?(1/2)\n");
    choice(YN);
    if (YN == '1') randomizeValuesInMatrix(&N, &M, matrix);
    else initValuesInMatrix(&N, &M, matrix);
}

void randomizeValuesInMatrix(const int *N, const int *M, int **matrix) {
    for (int i = 0; i < *N; ++i)
        for (int j = 0; j < *M; ++j)
            matrix[i][j] = -MINMAX_RANDOMIZE_INTERVAL + rand() % (MINMAX_RANDOMIZE_INTERVAL * 2);
}

void initValuesInMatrix(const int *N, const int *M, int **matrix) {
    initMatrixValue(N, M, matrix, STAR);
    for (int i = 0; i < *N; ++i)
        for (int j = 0; j < *M; ++j) {
            system("cls");
            outputMatrixWhenInit(N, M, matrix);
            printf("Введите элемент матрицы с координатами i = %d, j = %d\n", i + 1, j + 1);
            matrix[i][j] = validationWithArgument(-MINMAX_RANDOMIZE_INTERVAL, MINMAX_RANDOMIZE_INTERVAL);
        }
}

void multiplyMatrix(const int *firstN, const int *firstM, int **firstMatrix, const int *secondN,
                    const int *secondM,
                    int **secondMatrix) {
    if (*firstM != *secondN) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("Невозможно умножить матрицы таких размерностей\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        return;
    }
    int **resultMatrix = createPointerToMatrix<int>(MAX_MATRIX_SIZE);
    initMatrixValue(firstN, secondM, resultMatrix, 0);
    for (int i = 0; i < *firstN; ++i) {
        for (int j = 0; j < *secondM; ++j) {
            for (int m = 0, q = 0; m < *firstM; ++m, ++q) {
                resultMatrix[i][j] += firstMatrix[i][q] * secondMatrix[m][j];
            }
        }
    }
    printf("Полученная матрица:\n");
    outputMatrix<int>(firstN, secondM, resultMatrix);
}

void addOrSubtractMatrix(const int *firstN, const int *firstM, int **firstMatrix, const int *secondN,
                         const int *secondM,
                         int **secondMatrix) {
    if (*firstN != *secondN || *firstM != *secondM) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("Невозможно сложить/вычесть матрицы таких размерностей\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        return;
    }
    char YN;
    bool addOrSub, howSub;
    int **resultMatrix = createPointerToMatrix<int>(MAX_MATRIX_SIZE);
    printf("Сложить или вычесть?(1/2)\n");
    choice(YN);
    if (YN == '1') addOrSub = false;
    else {
        addOrSub = true;
        printf("Вычесть первую матрицу из второй, или вторую из первой?(1/2)\n");
        choice(YN);
        howSub = YN == '1';
    }
    for (int i = 0; i < *firstN; i++)
        for (int j = 0; j < *firstM; j++) {
            if (!addOrSub)resultMatrix[i][j] = firstMatrix[i][j] + secondMatrix[i][j];
            else
                resultMatrix[i][j] = howSub ? secondMatrix[i][j] - firstMatrix[i][j] : firstMatrix[i][j] -
                                                                                       secondMatrix[i][j];

        }
    printf("Полученная матрица:\n");
    outputMatrix<int>(firstN, secondN, resultMatrix);
}

void transposeMatrix(const int *N, const int *M, int **matrix) {
    int **transposeMatrix = createPointerToMatrix<int>(MAX_MATRIX_SIZE);
    for (int i = 0; i < *N; i++)
        for (int j = 0; j < *M; j++)
            transposeMatrix[j][i] = matrix[i][j];
    outputMatrix<int>(M, N, transposeMatrix);
}

int **getM(int **M, int N, int k) {
    int **A = new int *[N - 1];
    for (int i = 1; i < N; i++) {
        A[i - 1] = new int[N - 1];
        int m = 0;
        for (int j = 0; j < N; j++) {
            if (j == k) m++;
            else A[i - 1][j - m] = M[i][j];
        }
    }
    return A;
}

int calculateDeterminant(int **M, int N) {
    if (N == 1) return M[0][0];
    int D = 0;
    for (int i = 0; i < N; i++)
        D += (((i + 1) % 2) ? 1 : -1) * M[0][i] * calculateDeterminant(getM(M, N, i), N - 1);
    return D;
}

void calculateAdditionMatrix(const int *N, int **matrix, int **additionMatrix) {
    int **M = createPointerToMatrix<int>(MAX_MATRIX_SIZE);
    for (int i = 0; i < *N; ++i)
        for (int j = 0; j < *N; ++j) {
            int I = 0, J = 0;
            for (int k = 0; k < *N; ++k) {
                for (int q = 0; q < *N; ++q) {
                    if (k != i && q != j) {
                        M[I][J] = matrix[k][q];
                        J++;
                        if (J == *N - 1) {
                            I++;
                            J = 0;
                        }
                    }
                }
            }
            additionMatrix[i][j] = (int) pow(-1, i + j + 2) * calculateDeterminant(M, *N - 1);
        }

}

template<typename Type>
Type **createPointerToMatrix(int N) {
    Type **A = new Type *[N];
    for (int i = 0; i < N; i++) {
        A[i] = new Type[N];
    }
    return A;
}

void calculateInverseMatrix(const int *N, const int *M, int D, int **matrix) {
    int **additionMatrix = createPointerToMatrix<int>(MAX_MATRIX_SIZE);
    calculateAdditionMatrix(N, matrix, additionMatrix);
    double **inverseMatrix = createPointerToMatrix<double>(MAX_MATRIX_SIZE);
    for (int i = 0; i < *N; ++i)
        for (int j = 0; j < *N; ++j)
            inverseMatrix[i][j] = ((double) 1 / D) * additionMatrix[j][i];
    outputMatrix<double>(N, M, inverseMatrix);
}


void consoleInterface() {
    bool exitFlag = false, permissionFlag;
    short symbol;
    short position = 1;
    showHelloMessage();
    int N, M, R, K;
    int **firstMatrix = createPointerToMatrix<int>(MAX_MATRIX_SIZE);
    int **secondMatrix = createPointerToMatrix<int>(MAX_MATRIX_SIZE);
    system("cls");
    printf("Первая матрица:\n");
    createMatrix(N, M, firstMatrix);
    system("cls");
    printf("Вторая матрица:\n");
    createMatrix(R, K, secondMatrix);
    showMenu(position, &N, &M, &R, &K);
    while (!exitFlag) {
        permissionFlag = false;
        symbol = (short) getch();
        if (symbol == FIRST_BYTE_ARROW) symbol = (short) getch();
        switch (symbol) {
            case ARROW_UP:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case W:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case S:
                if (position < MAX_ARROW_POSITION) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case ESC:
                exitFlag = true;
                break;
            case ENTER:
                permissionFlag = true;
                break;
            case ZERO:
                position = 10;
                break;
            case ONE:
                position = 1;
                break;
            case TWO:
                position = 2;
                break;
            case THREE:
                position = 3;
                break;
            case FOUR:
                position = 4;
                break;
            case FIVE:
                position = 5;
                break;
            case SIX:
                position = 6;
                break;
            case SEVEN:
                position = 7;
                break;
            case EIGHT:
                position = 8;
                break;
            case NINE:
                position = 9;
                break;
            default:;
        }
        showMenu(position, &N, &M, &R, &K);
        switch (position) {
            case 1:
                printf("Первая матрица:\n");
                outputMatrix<int>(&N, &M, firstMatrix);
                printf("Вторая матрица:\n");
                outputMatrix<int>(&R, &K, secondMatrix);
                break;
            case 2:
                if (permissionFlag) addOrSubtractMatrix(&N, &M, firstMatrix, &R, &K, secondMatrix);
                break;
            case 3:
                multiplyMatrix(&N, &M, firstMatrix, &R, &K, secondMatrix);
                break;
            case 4:
                multiplyMatrix(&R, &K, secondMatrix, &N, &M, firstMatrix);
                break;
            case 5:
                printf("Транспонированная первая матрица:\n");
                transposeMatrix(&N, &M, firstMatrix);
                printf("Транспонированная вторая матрица:\n");
                transposeMatrix(&R, &K, secondMatrix);
                break;
            case 6:
                if (N == M) {
                    printf("Определитель первой матрицы: %d\n", calculateDeterminant(firstMatrix, N));
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("Первая матрица не квадратная!\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                }
                if (R == K) {
                    printf("Определитель второй матрицы: %d\n", calculateDeterminant(secondMatrix, R));
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("Вторая матрица не квадратная!\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                }

                break;
            case 7:
                if (N == M) {
                    printf("Обратная первой матрицы:\n");
                    if (N != 1) {
                        int D1 = calculateDeterminant(firstMatrix, N);
                        if(D1 != 0) calculateInverseMatrix(&N, &M, D1, firstMatrix);
                        else {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                            printf("Матрица вырожденная(определитель равен нулю)!\n");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                        }
                    } else printf("%f", (double) ((double) 1 / firstMatrix[0][0]));
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("Первая матрица не квадратная!\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                }
                if (R == K) {
                    printf("Обратная второй матрицы:\n");
                    if (R != 1) {
                        int D2 = calculateDeterminant(secondMatrix, R);
                        if(D2 != 0) calculateInverseMatrix(&R, &K, D2, secondMatrix);
                        else {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                            printf("Матрица вырожденная(определитель равен нулю)!\n");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                        }
                    } else printf("%f", (double) ((double) 1 / secondMatrix[0][0]));
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("Вторая матрица не квадратная!\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                }

                break;
            case 8:
                if (permissionFlag) {
                    createMatrix(N, M, firstMatrix);
                }
                break;
            case 9:
                if (permissionFlag) {
                    createMatrix(R, K, secondMatrix);
                }
                break;
            case 10:
                if (permissionFlag)
                    exitFlag = true;
                break;
            default:;
        }
    }
}

