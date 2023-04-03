#include <iostream>
#include "FileManager.h"
#include "constants.h"

void writeStringToFile(std::ofstream &out, const std::string &string) {
    for (char i: string) {
        out << std::bitset<8>(i) << ' ';
    }
    out << std::bitset<8>(SPLIT_USUAL_VALUE) << ' ' << std::endl;
}

std::string readStringFromFile(std::ifstream &in) {
    std::string string, bs;
    char a;
    while (true) {
        in >> bs;
        a = std::bitset<8>(bs).to_ulong();
        if (a == SPLIT_USUAL_VALUE) break;
        string += a;
    }
    return string;
}

int readIntFromFile(std::ifstream &in) {
    std::string dataFromFile;
    in >> dataFromFile;
    return std::bitset<16>(dataFromFile).to_ulong();
}
char readIdentity(std::ifstream &in) {
    std::string dataFromFile;
    in >> dataFromFile;
    return std::bitset<8>(dataFromFile).to_ulong();
}
bool readAndCheckIdentity(std::ifstream &in, char identity) {
    std::string dataFromFile;
    in >> dataFromFile;
    return identity == std::bitset<8>(dataFromFile).to_ulong();
}
