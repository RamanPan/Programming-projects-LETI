#include "functionality.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

long add(long firstValue, long secondValue) {
    long result = firstValue + secondValue;
    if (checkOverflow(result)) return result;
    else {
        printf("Result overflow! Try again");
        return firstValue;
    }
}

long multiply(long firstValue, long secondValue) {
    long result = firstValue * secondValue;
    if (checkOverflow(result)) return result;
    else {
        printf("Result overflow! Try again");
        return firstValue;
    }
}

long subtraction(long firstValue, long secondValue) {
    long result = firstValue - secondValue;
    if (checkOverflow(result)) return result;
    else {
        printf("Result overflow! Try again");
        return firstValue;
    }
}

long division(long firstValue, long secondValue) {
    if (secondValue == 0) {
        printf("Denominator equals zero!!!");
        exit(3);
    }
    long result = firstValue / secondValue;
    if (checkOverflow(result)) {
        return (long) result;
    } else {
        printf("Result overflow! Try again");
        return firstValue;
    }
}

double exponentiation(long value, int power) {
    double result;
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
        printf("Result = %ld\n", (long) result);
        return (long) result;
    } else {
        printf("Result overflow! Try again");
        return value;
    }
}

double rooting(long value, int power) {
    double rootValue = ((double) value / power);
    double eps = 0.00001;
    double rootNumber = value;
    while (fabs(rootValue - rootNumber) >= eps) {
        rootNumber = value;
        for (int i = 1; i < power; i++) {
            rootNumber = rootNumber / rootValue;
        }
        rootValue = 0.5 * (rootNumber + rootValue);
    }
    if (checkOverflow(rootValue)) {
        printf("Result = %ld\n", (long) rootValue);
        return (long) rootValue;
    } else {
        printf("Result overflow! Try again");
        return value;
    }
}


void showMenu(int position, long firstValue, long secondValue) {
    system("cls");
    printf("Calculator\n");
    printf("First value = %ld, second value = %ld\n", firstValue, secondValue);
    printf("%s1) Add(+)\n", position == 1 ? "->" : " ");
    printf("%s2) Multiply(*)\n", position == 2 ? "->" : " ");
    printf("%s3) Subtract(-)\n", position == 3 ? "->" : " ");
    printf("%s4) Division(/)\n", position == 4 ? "->" : " ");
    printf("%s5) Exponentiation(^)(Enter power)\n", position == 5 ? "->" : " ");
    printf("%s6) Root(Enter root)\n", position == 6 ? "->" : " ");
    printf("%s7) Change first value\n", position == 7 ? "->" : " ");
    printf("%s8) Change second value\n", position == 8 ? "->" : " ");
    printf("%s9) Swap first and second values\n", position == 9 ? "->" : " ");
    printf("%s10) Exit\n", position == 10 ? "->" : " ");
}


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

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}

bool validationForDivide(long value) {
    if (value == 0) {
        printf("Second value equals zero! Change it and try again\n");
        fflush(stdin);
        return false;
    }
    return true;
}

bool validationForRoot(long value) {
    return value >= 0;
}