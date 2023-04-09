

#ifndef HIERARCHICALSTRUCTUREOFDATASTORAGE_UNIVERSITY_H
#define HIERARCHICALSTRUCTUREOFDATASTORAGE_UNIVERSITY_H

#include <string>
#include "Faculty.h"

class University {
private:
    std::string title;
    std::vector<Faculty> faculties;
public:
    University();

    explicit University(std::string title);

    void addFaculty();

    Faculty *findFaculty(const std::string &data);

    bool deleteFaculty(const std::string &data);

    const std::string &getTitle() const;

    void setTitle(const std::string &title);

    std::vector<Faculty> &getFaculties();

    void deleteAll();

    std::vector<std::string> findStudent(int mode);

    void writeToFile(bool isItSafe);

    bool readFromFile(bool isItSafe);

    void setFaculties(const std::vector<Faculty> &faculties);
};

#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_UNIVERSITY_H
