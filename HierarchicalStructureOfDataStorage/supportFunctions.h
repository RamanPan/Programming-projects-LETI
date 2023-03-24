#ifndef HIERARCHICALSTRUCTUREOFDATASTORAGE_SUPPORTFUNCTIONS_H
#define HIERARCHICALSTRUCTUREOFDATASTORAGE_SUPPORTFUNCTIONS_H

#include "University.h"
#include <windows.h>

void showMenuForUniversity(int position, University &university);

void showMenuForFaculty(int position, Faculty &faculty);

void showMenuForDepartment(int position, Department &department);

void showMenuForGroup(int position, Group &group);

void consoleInterfaceForUniversity(University &university);

void consoleInterfaceForFaculty(Faculty &faculty, University &university);

void consoleInterfaceForDepartment(Department &department, University &university);

void consoleInterfaceForGroup(Group &group, University &university);

#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_SUPPORTFUNCTIONS_H
