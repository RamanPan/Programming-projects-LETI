#include <stdio.h>
#include <windows.h>
#include "functionality.h"
int main() {
    SetConsoleOutputCP(CP_UTF8);
    printf("Добро пожаловать в Змейку!!!\n");
    printf("Краткий гайд:\n");
    printf("Первая змейка обозначается $, вторая @:\n");
    printf("Первая змейка ходит на стрелочки, вторая на WASD:\n");
    printf("Еда выглядит - e\n");
    printf("Стенки - /\n");
    printf("Введите размерность поля!!!\n");
    const long n = validationGameArea();
    int gameArea[n][n];
    return 0;
}
