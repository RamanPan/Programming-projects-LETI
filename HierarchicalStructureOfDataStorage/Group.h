#ifndef HIERARCHICALSTRUCTUREOFDATASTORAGE_GROUP_H
#define HIERARCHICALSTRUCTUREOFDATASTORAGE_GROUP_H

#include "Student.h"
#include <vector>

class Group {
private:
    int number;
    std::vector<Student> students;
public:
    int getNumber() const;

    void setNumber(int number);

    const std::vector<Student> &getStudents() const;

    void setStudents(const std::vector<Student> &students);

    explicit Group(int number);

    Group();
};

#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_GROUP_H
