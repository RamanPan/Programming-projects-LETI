#ifndef HIERARCHICALSTRUCTUREOFDATASTORAGE_DEPARTMENT_H
#define HIERARCHICALSTRUCTUREOFDATASTORAGE_DEPARTMENT_H

#include <string>
#include "Group.h"

class Department {
private:
    std::string title;
    std::vector<Group> groups;
public:
    explicit Department(const std::string &title);

    Department();

    const std::string &getTitle() const;

    void setTitle(const std::string &title);

    void addGroup();

    Group *findGroup(int data);

    bool deleteGroup(int data);

    void deleteAll();

    void writeToFile(std::ofstream &out);

    std::vector<Group> &getGroups();

    void setGroups(const std::vector<Group> &groups);
};

#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_DEPARTMENT_H
