#include "functionality.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

long add(long firstValue, long secondValue) {
    long result = firstValue + secondValue;
    if (checkOverflow(result)) return result;
    else {
        printf("Результат вышел за границу допустимого значения! Попробуйте снова!");
        return firstValue;
    }
}

long multiply(long firstValue, long secondValue) {
    long result = firstValue * secondValue;
    if (checkOverflow(result)) return result;
    else {
        printf("Результат вышел за границу допустимого значения! Попробуйте снова!");
        return firstValue;
    }
}

long subtraction(long firstValue, long secondValue) {
    long result = firstValue - secondValue;
    if (checkOverflow(result)) return result;
    else {
        printf("Результат вышел за границу допустимого значения! Попробуйте снова!");
        return firstValue;
    }
}

long division(long firstValue, long secondValue) {
    long result = firstValue / secondValue;
    if (checkOverflow(result)) {
        return (long) result;
    } else {
        printf("Результат вышел за границу допустимого значения! Попробуйте снова!");
        return firstValue;
    }
}

double exponentiation(long value, int power) {
    double result;
    if (value == 0 && power == 0) {
        printf("Значение нуль в степени нуля является неопределенностью!");
        return 0;
    }
    if (power == 0) result = 1;
    else {
        bool positiveOrNegative;
        if (power < 0) positiveOrNegative = 0;
        else positiveOrNegative = 1;
        double exponentiationValue = value;
        while (abs(power) != 1) {
            exponentiationValue *= value;
            if (positiveOrNegative) power--;
            else power++;
        }
        if (positiveOrNegative) result = exponentiationValue;
        else result = 1 / exponentiationValue;
    }
    if (checkOverflow(result)) {
        printf("Результат = %ld\n", (long) result);
        return (long) result;
    } else {
        printf("Результат вышел за границу допустимого значения! Попробуйте снова!");
        return value;
    }
}

double rooting(long value, int power) {
    double rootValue = pow(value, (double) 1 / power);
    if (checkOverflow(rootValue)) {
        printf("Результат = %ld\n", (long) rootValue);
        return (long) rootValue;
    } else {
        printf("Результат вышел за границу допустимого значения! Попробуйте снова!");
        return value;
    }
}


void showMenu(int position, long firstValue, long secondValue) {
    system("cls");
    printf("Калькулятор 'Расчёт БИСТРО и ЧЁТКА'\n");
    printf("Первое число = %ld, Второе число = %ld\n", firstValue, secondValue);
    printf("%s1) Сложение(+)\n", position == 1 ? "->" : " ");
    printf("%s2) Умножение(*)\n", position == 2 ? "->" : " ");
    printf("%s3) Вычитание(-)\n", position == 3 ? "->" : " ");
    printf("%s4) Деление(/)\n", position == 4 ? "->" : " ");
    printf("%s5) Возведение в степень(^)(С вводом степени)\n", position == 5 ? "->" : " ");
    printf("%s6) Извлечение корня(С вводом степени корня)\n", position == 6 ? "->" : " ");
    printf("%s7) Смена первого числа\n", position == 7 ? "->" : " ");
    printf("%s8) Смена второго числа\n", position == 8 ? "->" : " ");
    printf("%s9) Обмен значениями первого и второго числа\n", position == 9 ? "->" : " ");
    printf("%s0) Выход\n", position == 10 ? "->" : " ");
}


long validation() {
    bool validationFlag = false;
    double result;
    while (!validationFlag) {
        if (scanf("%lf", &result)) {
            if (!checkOverflow(result)) {
                printf("Неправильный ввод! Число вышло за границу дозволенного! Попробуйте снова!\n");
            } else validationFlag = true;
        } else {
            printf("Неправильный ввод! Попробуйте снова!\n");
        }
        fflush(stdin);
    }
    return (long) result;
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}


bool validationForRoot(long value) {
    return value >= 0;
}