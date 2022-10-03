#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "functionality.h"

void showHelloMessage() {
    printf("Добро пожаловать!!!\n");
}

long validation() {
    bool validationFlag = false;
    double result;
    while (!validationFlag) {
        if (scanf("%lf", &result)) {
            if (!checkOverflow(result)) {
                printf("Неправильный ввод! Число вышло за границу дозволенного! Попробуйте снова!\n");
                fflush(stdin);
            } else validationFlag = true;
        } else {
            printf("Неправильный ввод! Попробуйте снова!\n");
            fflush(stdin);
        }
    }
    return (long) result;
}

void generateSpiral(short I, short J, int area[][J], short variation) {
    int k = 1;
    int bfI = 0, bfJ = 0;
    int i, j;
    switch (variation) {
        case 0:
            i = 0;
            j = 0;
            while (k <= I * J) {
                area[i][j] = k;
                if (i == bfI && j < J - bfJ - 1)
                    ++j;
                else if (j == J - bfJ - 1 && i < I - bfI - 1)
                    ++i;
                else if (i == I - bfI - 1 && j > bfJ)
                    --j;
                else
                    --i;
                if ((i == bfI + 1) && (j == bfJ) && (bfJ != J - bfJ - 1)) {
                    ++bfI;
                    ++bfJ;
                }
                ++k;
            }
            break;
        case 1:
            i = 0;
            j = J - 1;
            while (k <= I * J) {
                area[i][j] = k;
                if (i == I - bfI - 1 && j < J - bfJ - 1)
                    ++j;
                else if (j == bfJ && i < I - bfI - 1)
                    ++i;
                else if (i == bfI && j > bfJ)
                    --j;
                else
                    --i;
                if ((i == bfI + 1) && (j == J - bfJ - 1) && (bfJ != J - bfJ - 1)) {
                    ++bfI;
                    ++bfJ;
                }
                ++k;
            }
            break;
        case 2:

            break;
        case 3:

            break;
        default:;
    }
}

bool checkOverflow(double d) {
    return d >= 1 && d <= 12;
}

void outputSpiral(int I, int J, int area[][J]) {
    for (int i = 0; i < I; i++)
        for (int j = 0; j < J; j++) {
            printf("%d ", area[i][j]);
            if (j == J - 1) printf("\n");
        }
}


void showMenu(int position, int I, int J) {
    system("cls");
    printf("Выберите действие:\n");
    printf("1) Изменить длину%s\n", position == 1 ? "<-" : " ");
    printf("2) Изменить ширину%s\n", position == 2 ? "<-" : " ");
    printf("3) Спираль в центр по часовой%s\n", position == 3 ? "<-" : " ");
    printf("4) Спираль в центр против часовой%s\n", position == 4 ? "<-" : " ");
    printf("5) Спираль из центра по часовой%s\n", position == 5 ? "<-" : " ");
    printf("6) Спираль из центра против часовой%s\n", position == 6 ? "<-" : " ");
    printf("7) Выход%s\n", position == 7 ? "<-" : " ");
    printf("Длина = %d, Ширина = %d\n", I, J);
}