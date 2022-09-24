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

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}
