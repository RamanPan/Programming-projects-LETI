#ifndef HIERARCHICALSTRUCTUREOFDATASTORAGE_FACULTY_H
#define HIERARCHICALSTRUCTUREOFDATASTORAGE_FACULTY_H

#include <string>
#include "Department.h"

class Faculty {
private:
    std::string title;
    std::vector<Department> departments;
public:
    explicit Faculty(const std::string &title);

    Faculty();

    void addDepartment();

    Department *findDepartment(const std::string& data);

    void deleteDepartment(const std::string& data);

    void deleteAll();

    const std::string &getTitle() const;

    void writeToFile(std::ofstream &out);

    void readFromFile(std::istream &in);


    void setTitle(const std::string &title);

    std::vector<Department> &getDepartments();

    void setDepartments(const std::vector<Department> &departments);
};

#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_FACULTY_H
