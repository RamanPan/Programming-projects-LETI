#include <stdio.h>
#include "functionality.h"
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    long firstValue;
    long secondValue;
    int power;
    short minPosition = 1, maxPosition = 10;
    short position = minPosition;
    int symbol;
    char YN;
    long swap;
    bool exitFlag = false;
    bool permissionFlag;
    printf("Добро пожаловать в калькулятор студента группы 2375 Панаёта Романа,\nкоторый очень хочет сдать всё без ошибок и вылетов!\n");
    printf("Введите первое число!\n");
    firstValue = validation();
    printf("Введите второе число!\n");
    secondValue = validation();
    showMenu(position, firstValue, secondValue);
    while (!exitFlag) {
        permissionFlag = false;
        symbol = getch();
        if (symbol == 224) symbol = getch();
        switch (symbol) {
            case 72:
                if (0 != position - 1)
                    position--;
                else position = maxPosition;
                break;
            case 80:
                if (position < maxPosition) position++;
                else
                    position = minPosition;
                break;
            case 27:
                scanf("%s", &YN);
                if (YN == 'Y') exitFlag = true;
                break;
            case 13:
                permissionFlag = true;
                break;
            case 48:
                position = 10;
                break;
            case 49:
                position = 1;
                break;
            case 50:
                position = 2;
                break;
            case 51:
                position = 3;
                break;
            case 52:
                position = 4;
                break;
            case 53:
                position = 5;
                break;
            case 54:
                position = 6;
                break;
            case 55:
                position = 7;
                break;
            case 56:
                position = 8;
                break;
            case 57:
                position = 9;
                break;
            default:;
        }
        showMenu(position, firstValue, secondValue);
        if (permissionFlag) {
            switch (position) {
                case 1:
                    printf("Результат = %ld\n", add(firstValue, secondValue));
                    break;
                case 2:
                    printf("Результат = %ld\n", multiply(firstValue, secondValue));
                    break;
                case 3:
                    printf("Результат = %ld\n", subtraction(firstValue, secondValue));
                    break;
                case 4:
                    if (secondValue == 0)
                        printf("Деление на ноль!!! Измените число и попробуйте снова!");
                    else
                        printf("Результат = %ld\n", division(firstValue, secondValue));
                    break;
                case 5:
                    printf("Введите степень числа!\n");
                    power = validation();
                    exponentiation(firstValue, power);
                    break;
                case 6:
                    if (validationForRoot(firstValue)) {
                        printf("Введите степень корня!\n");
                        power = validation();
                        if (power <= 0) {
                            printf("Неверная степень! Степень меньше или равна нулю! Попробуйте снова!");
                            break;
                        }
                        rooting(firstValue, power);
                    } else printf("Неверное число! Число меньше нуля! Поменяйте его и попробуйте снова!");
                    break;
                case 7:
                    printf("Введите число для смены!\n");
                    firstValue = validation();
                    showMenu(position, firstValue, secondValue);
                    printf("Первое число успешно изменено!\n");
                    break;
                case 8:
                    printf("Введите число для смены!\n");
                    secondValue = validation();
                    showMenu(position, firstValue, secondValue);
                    printf("Второе число успешно изменено!\n");
                    break;
                case 9:
                    swap = firstValue;
                    firstValue = secondValue;
                    secondValue = swap;
                    showMenu(position, firstValue, secondValue);
                    printf("Числа успешно поменялись!");
                    break;
                case 10:
                    printf("Вы уверены что хотите выйти?(Y/N)\n");
                    scanf("%s", &YN);
                    if (YN == 'Y') exitFlag = true;
                    break;
                default:
                    break;
            }
        }
    }
    printf("Всего хорошего! До скорых будущих расчётов!");
    return 0;
}
