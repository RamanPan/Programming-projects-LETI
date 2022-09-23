#ifndef CALCULATOR_FUNCTIONALITY_H
#define CALCULATOR_FUNCTIONALITY_H


#include <stdbool.h>

long add(long firstValue, long secondValue);

long multiply(long firstValue, long secondValue);

long subtraction(long firstValue, long secondValue);

long division(long firstValue, long secondValue);

double exponentiation(long value, int power);

double rooting(long value, int power);

void showMenu(int position, long firstValue, long secondValue);

long validation();

bool validationForRoot(long value);

bool checkOverflow(double d);

bool validationForDivide(long value);


#endif //CALCULATOR_FUNCTIONALITY_H
