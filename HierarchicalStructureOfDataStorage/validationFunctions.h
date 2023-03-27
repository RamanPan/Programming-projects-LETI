#ifndef HIERARCHICALSTRUCTUREOFDATASTORAGE_VALIDATIONFUNCTIONS_H
#define HIERARCHICALSTRUCTUREOFDATASTORAGE_VALIDATIONFUNCTIONS_H

#include "windows.h"
#include "constants.h"
#include "Messages.h"
#include <string>


long validation();

long validationWithArgument(int min, int max);

std::string validateString(std::string message, bool validate);

void choice(char &YN);

bool checkOverflow(double d);


#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_VALIDATIONFUNCTIONS_H
