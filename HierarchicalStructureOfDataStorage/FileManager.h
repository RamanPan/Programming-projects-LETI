#ifndef HIERARCHICALSTRUCTUREOFDATASTORAGE_FILEMANAGER_H
#define HIERARCHICALSTRUCTUREOFDATASTORAGE_FILEMANAGER_H

#include <fstream>
#include <string>
#include <bitset>

void writeStringToFile(std::ofstream &out, const std::string &string);

std::string readStringFromFile(std::ifstream &in);

bool readAndCheckIdentity(std::ifstream &in, char identity);

#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_FILEMANAGER_H
