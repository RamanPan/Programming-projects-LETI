#include <stdio.h>
#include "functionality.h"
int main() {
    printf("Добро пожаловать в Змейку!!!\n");
    printf("Введите размерность поля!!!\n");
    int n = validation();
    int gameArea[n][n];
    return 0;
}
