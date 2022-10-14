#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "functionality.h"
#include "functionality.h"

long validation() {
    bool validationFlag = false;
    double result;
    while (!validationFlag) {
        if (scanf("%lf", &result)) {
            if (!checkOverflow(result)) {
                printf("Неправильный ввод! Число вышло за границу дозволенного! Попробуйте снова!\n");
            } else validationFlag = true;
        } else printf("Неправильный ввод! Попробуйте снова!\n");
        fflush(stdin);
    }
    return (long) result;
}

long validationGameArea() {
    long result;
    short minArea = 2, maxArea = 14;
    do {
        result = validation();
        if (result > maxArea || result < minArea)
            printf("Неверный ввод размера поля! Размер поля может принимать значения от %hd до %hd\n", minArea,
                   maxArea);
    } while (result > maxArea || result < minArea);
    return result;
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}