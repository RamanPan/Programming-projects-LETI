#ifndef HIERARCHICALSTRUCTUREOFDATASTORAGE_MESSAGES_H
#define HIERARCHICALSTRUCTUREOFDATASTORAGE_MESSAGES_H

#include <string>

void showErrorMessage(const std::string &message);

void showInfoMessage(const std::string &message);

long validation();

long validationWithArgument(int min, int max);

bool checkOverflow(double d);

#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_MESSAGES_H
