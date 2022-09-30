#ifndef CALCULATOR_FUNCTIONALITY_H
#define CALCULATOR_FUNCTIONALITY_H

#include <stdbool.h>

void add(long firstValue, long secondValue);

void multiply(long firstValue, long secondValue);

void subtraction(long firstValue, long secondValue);

void division(long firstValue, long secondValue);

void exponentiation(long value, int power);

void rooting(long value, int power);

void showMenu(int position,long firstValue, long secondValue);

long validation();

bool validationForRoot(long value);

bool checkOverflow(double d);

bool validationForDivide(long value);


#endif //CALCULATOR_FUNCTIONALITY_H