
#ifndef TESTPROJECT_FUNCTIONALITY_H
#define TESTPROJECT_FUNCTIONALITY_H

#include <stdbool.h>

long add(long firstValue, long secondValue);

long multiply(long firstValue, long secondValue);

long subtraction(long firstValue, long secondValue);

long division(long firstValue, long secondValue);

double exponentiation(long value, int power);

double rooting(long value, int power);

void showMenu(int position);

void clearScreen();

long validation();

bool validationForRoot(long value);

long validationForDivide();

#endif //TESTPROJECT_FUNCTIONALITY_H
