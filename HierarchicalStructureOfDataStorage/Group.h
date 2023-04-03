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

    void addStudent();

    Student *findStudent(const std::string& data);

    bool deleteStudent(const std::string& data);

    void deleteAll();

    void writeToFile(std::ofstream &out);

    std::vector<Student> &getStudents();

    void setStudents(const std::vector<Student> &students);

    explicit Group(int number);

    Group();
};

#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_GROUP_H
