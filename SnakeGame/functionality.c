#include <stdbool.h>
#include <stdio.h>
#include "functionality.h"

long validation() {
    bool validationFlag = false;
    double result;
    while (!validationFlag) {
        if (scanf("%lf", &result)) {
            if (!checkOverflow(result)) {
                printf("Wrong enter! Overflow value! Try again\n");
                fflush(stdin);
            } else validationFlag = true;
        } else {
            printf("Wrong enter! Try again\n");
            fflush(stdin);
        }
    }
    return (long) result;
}

void showMenu(int n, int area[][n]) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            printSymbol((short) area[i][j]);
            if (j == n - 1) printf("\n");
        }
}

void fillingArea(int n, int area[][n]) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {}
}

void showHelloMessage() {
    printf("Добро пожаловать в Змейку!!!\n");
    printf("Краткий гайд:\n");
    printf("Первая змейка обозначается $, вторая @\n");
    printf("Первая змейка ходит на стрелочки, вторая на WASD\n");
    printf("Еда выглядит - e\n");
    printf("Стенки - /\n");
}

void printSymbol(short numberSymbol) {
    switch (numberSymbol) {
        case 36:
            printf("$");
            break;
        case 38:
            printf("&");
            break;
        case 47:
            printf("/");
            break;
        case 101:
            printf("e");
            break;
        default:
            printf(" ");
    }
}


long validationGameArea() {
    long result;
    short minArea = 3, maxArea = 10;
    do {
        result = validation();
        if (result > maxArea || result < minArea)
            printf("Неверный ввод размера поля! Размер поля может принимать значения от %hd до %hd", minArea, maxArea);
    } while (result > maxArea || result < minArea);
    return result;
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}
