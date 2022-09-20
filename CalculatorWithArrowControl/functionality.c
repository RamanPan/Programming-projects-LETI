#include "functionality.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


long add(long firstValue, long secondValue) { return firstValue + secondValue; }

long multiply(long firstValue, long secondValue) { return firstValue * secondValue; }

long subtraction(long firstValue, long secondValue) { return firstValue - secondValue; }

long division(long firstValue, long secondValue) {
    if (secondValue == 0) {
        printf("Denominator equals zero!!!");
        exit(3);
    }
    double result = (double)firstValue / secondValue;
    printf("Result = %f\n", result);
    return (long)result;
}

double exponentiation(long value, int power) {
    if (power == 0) return 1;
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
        if (positiveOrNegative) return exponentiationValue;
        else return 1 / exponentiationValue;
    }
}

double rooting(long value, int power) {
    if (value < 0) {
        printf("Value in root < 0!!!");
        exit(3);
    } else {
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
        printf("Result = %f\n", rootValue);
        return rootValue;
    }
}

void showMenu(int position) {
    clearScreen();
    printf("%s1) Add(+)\n", position == 1 ? ">" : " ");
    printf("%s2) Multiply(*)\n", position == 2 ? ">" : " ");
    printf("%s3) Subtract(-)\n", position == 3 ? ">" : " ");
    printf("%s4) Division(/)\n", position == 4 ? ">" : " ");
    printf("%s5) Exponentiation(^)\n", position == 5 ? ">" : " ");
    printf("%s6) Root\n", position == 6 ? ">" : " ");
    printf("%s7) Change value\n", position == 7 ? ">" : " ");
    printf("%s8) Exit\n", position == 8 ? ">" : " ");
}

void clearScreen() {
    for (int i = 0; i < 6; i++)
        printf("\n");
}

long validation() {
    bool validationFlag = false;
    long result;
    while (!validationFlag) {
        if (scanf("%ld", &result)) validationFlag = true;
        else {
            printf("Wrong enter! Try again\n");
            fflush(stdin);
        }
    }
    return result;
}

long validationForDivide() {
    bool validationFlag = false;
    long result;
    while (!validationFlag) {
        result = validation();
        if (result != 0) validationFlag = true;
        else {
            printf("Wrong enter! Value equals zero! Try again\n");
            fflush(stdin);
        }
    }
    return result;
}

bool validationForRoot(long value) {
    return value >= 0;
}