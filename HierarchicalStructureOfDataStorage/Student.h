#ifndef HIERARCHICALSTRUCTUREOFDATASTORAGE_STUDENT_H
#define HIERARCHICALSTRUCTUREOFDATASTORAGE_STUDENT_H
#include <string>
enum Gender {MEN,WOMEN};
class Student {
private:
    std::string firstname;
    std::string surname;
    std::string patronymic;
    Gender gender;
public:
    Student(const std::string &firstname, const std::string &surname, const std::string &patronymic, Gender gender);
    Student();

    const std::string &getFirstname() const;

    void setFirstname(const std::string &firstname);

    const std::string &getSurname() const;

    void setSurname(const std::string &surname);

    const std::string &getPatronymic() const;

    void setPatronymic(const std::string &patronymic);

    Gender getGender() const;

    void setGender(Gender gender);

};


#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_STUDENT_H
