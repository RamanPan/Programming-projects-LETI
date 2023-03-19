#include "Group.h"

int Group::getNumber() const {
    return number;
}

void Group::setNumber(int number) {
    Group::number = number;
}

const std::vector<Student> &Group::getStudents() const {
    return students;
}

void Group::setStudents(const std::vector<Student> &students) {
    Group::students = students;
}

Group::Group(int number) : number(number) {}

Group::Group() {}
