

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

    explicit University(const std::string &title);

    const std::string &getTitle() const;

    void setTitle(const std::string &title);

    const std::vector<Faculty> &getFaculties() const;

    void setFaculties(const std::vector<Faculty> &faculties);
};
#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_UNIVERSITY_H
