#include <iostream>
#include "University.h"
#include "supportFunctions.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    University university("Saint Petersburg Electrotechnical University \"LETI\"");
    consoleInterfaceForUniversity(university);
}
