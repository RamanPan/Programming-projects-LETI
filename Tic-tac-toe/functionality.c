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

long validationWithArgument(short max) {
    long result;
    short minArea = 2, maxArea = max;
    do {
        result = validation();
        if (result > maxArea || result < minArea)
            printf("Неверный ввод размера поля! Размер поля может принимать значения от %hd до %hd\n", minArea,
                   maxArea);
    } while (result > maxArea || result < minArea);
    return result;
}

void showHelloMessage() {
    printf("Приветствую!\n");
    printf("Это игра 'Крестики и нолики'\n");
    printf("Перед игрой вам нужно ввести высоту и ширину игрового поля\n");
    printf("Затем выбрать кол-во очков для победы крестиков и для победы ноликов\n");
    printf("Очки для победы не могут быть больше чем высота и ширина поля\n");
    printf("Если на поле не осталось места - игра завершается ничьей\n");
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}