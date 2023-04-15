#include "University.h"

#include <utility>
#include <iostream>
#include "validationFunctions.h"
#include "Messages.h"

const std::string &University::getTitle() const {
    return title;
}

void University::setTitle(const std::string &title) {
    University::title = title;
}

std::vector<Faculty> &University::getFaculties() {
    return faculties;
}

void University::setFaculties(const std::vector<Faculty> &faculties) {
    University::faculties = faculties;
}

University::University(std::string title) : title(std::move(title)) {}

University::University() {}

void University::addFaculty() {
    Faculty faculty;
    char permission;
    faculty.setTitle(validateString("введите название факультета", true));
    showInfoMessage("создать кафедры прямо сейчас?(1 - да, 2 - нет)");
    choice(permission);
    if (permission == '1') {
        showInfoMessage("введите кол-во создаваемых кафедр");
        int quantity = validation();
        for (int i = 0; i < quantity; ++i) {
            faculty.addDepartment();
        }
    }
    faculties.push_back(faculty);
}

Faculty *University::findFaculty(const std::string &data) {
    for (Faculty &f: faculties) {
        if (f.getTitle() == data)
            return &f;
    }
    showErrorMessage("факультет не был найден");
    return nullptr;
}

bool University::deleteFaculty(const std::string &data) {
    int index = -1;
    Faculty f;
    for (int i = 0; i < faculties.size(); ++i) {
        f = faculties.at(i);
        if (f.getTitle() == data) {
            f.deleteAll();
            index = i;
            break;
        }
    }
    if (index != -1) {
        faculties.erase(faculties.begin() + index);
        return true;
    } else showErrorMessage("такого факультета не существует");
    return false;
}

void University::deleteAll() {
    for (Faculty f: faculties) {
        f.deleteAll();
    }
    faculties.clear();
}

void University::writeToFile(bool isItSafe) {
    std::string path;
    if (!isItSafe) path = "D:\\Coding\\Programming-projects-LETI\\HierarchicalStructureOfDataStorage\\data.bin";
    else path = "D:\\Coding\\Programming-projects-LETI\\HierarchicalStructureOfDataStorage\\cmake-build-debug\\data.bin";
    std::ofstream out(path, std::ios_base::binary | std::ios_base::out);
    out << std::bitset<8>((int) 'U') << ' ' << std::endl;
    writeStringToFile(out, title);
    for (Faculty &faculty: faculties)
        faculty.writeToFile(out);
    out.close();
}

bool University::readFromFile(bool isItSafe) {
    std::string path;
    if (!isItSafe) {
        path = "D:\\Coding\\Programming-projects-LETI\\HierarchicalStructureOfDataStorage\\data.bin";
        writeToFile(true);
    } else path = "D:\\Coding\\Programming-projects-LETI\\HierarchicalStructureOfDataStorage\\cmake-build-debug\\data.bin";
    std::ifstream in(
            path,
            std::ios_base::binary | std::ios_base::in);
    try {
        if (readAndCheckIdentity(in, 'U')) {
            deleteAll();
            title = readStringFromFile(in);
            char status;
            Faculty *nowF = nullptr;
            Department *nowD = nullptr;
            Group *nowG = nullptr;
            bool notMistake = true, mistake = false;
            while (!in.eof()) {
                status = readIdentity(in);
                if (status == 0) break;
                if (mistake) {
                    std::cout << 1;
                    notMistake = false;
                }
                if (notMistake) {
                    switch (status) {
                        case 'F': {
                            Faculty faculty(readStringFromFile(in));
                            faculties.push_back(faculty);
                            nowF = &faculties.at(faculties.size() - 1);
                        }
                            break;
                        case 'D': {
                            Department department(readStringFromFile(in));
                            if (nowF != nullptr) {
                                nowF->getDepartments().push_back(department);
                                nowD = &nowF->getDepartments().at(nowF->getDepartments().size() - 1);
                            } else mistake = true;
                        }
                            break;
                        case 'G': {
                            Group group(readIntFromFile(in));
                            if (nowD != nullptr) {
                                nowD->getGroups().push_back(group);
                                nowG = &nowD->getGroups().at(nowD->getGroups().size() - 1);
                            } else mistake = true;
                        }
                            break;
                        case 'S': {
                            Student student;
                            student.setFirstname(readStringFromFile(in));
                            student.setSurname(readStringFromFile(in));
                            student.setPatronymic(readStringFromFile(in));
                            if (readIntFromFile(in) == 0) student.setGender(MEN);
                            else student.setGender(WOMEN);
                            if (nowG != nullptr) {
                                nowG->getStudents().push_back(student);
                            } else mistake = true;
                        }
                            break;
                    }
                } else {
                    showErrorMessage("данные в файле хранятся в неправильном формате");
                    in.close();
                    readFromFile(true);
                    return false;
                }
            }
        } else {
            showErrorMessage("данные в файле хранятся в неправильном формате");
            in.close();
            readFromFile(true);
            return false;
        }
        in.close();
        return true;
    }
    catch (std::invalid_argument exception) {
        showErrorMessage("данные в файле хранятся в неправильном формате");
        readFromFile(true);
        return false;
    }
}

std::vector<std::string> University::findStudent(int mode) {
    std::vector<std::string> students;
    std::string gender;
    switch (mode) {
        case 0: {
            std::string surname = validateString("введите фамилию студента для поиска", false);
            for (Faculty &f: faculties)
                for (Department &d: f.getDepartments())
                    for (Group &g: d.getGroups())
                        for (Student &s: g.getStudents())
                            if (s.getSurname() == surname) {
                                gender = (s.getGender() == MEN) ? " - men" : " - women";
                                students.push_back(
                                        s.getFirstname() + " " + s.getSurname() + " " + s.getPatronymic() + gender + " "
                                        + std::to_string(g.getNumber()) + " " + d.getTitle() + " " + f.getTitle());
                            }
        }
            break;
        case 1: {
            std::string name = validateString("введите имя студента для поиска", false);
            for (Faculty &f: faculties)
                for (Department &d: f.getDepartments())
                    for (Group &g: d.getGroups())
                        for (Student &s: g.getStudents())
                            if (s.getFirstname() == name) {
                                gender = (s.getGender() == MEN) ? " - men" : " - women";
                                students.push_back(
                                        s.getFirstname() + " " + s.getSurname() + " " + s.getPatronymic() + gender + " "
                                        + std::to_string(g.getNumber()) + " " + d.getTitle() + " " + f.getTitle());
                            }
        }
            break;
        case 2: {
            std::string patronymic = validateString("введите отчество студента для поиска", false);
            for (Faculty &f: faculties)
                for (Department &d: f.getDepartments())
                    for (Group &g: d.getGroups())
                        for (Student &s: g.getStudents())
                            if (s.getPatronymic() == patronymic) {
                                gender = (s.getGender() == MEN) ? " - men" : " - women";
                                students.push_back(
                                        s.getFirstname() + " " + s.getSurname() + " " + s.getPatronymic() + gender + " "
                                        + std::to_string(g.getNumber()) + " " + d.getTitle() + " " + f.getTitle());
                            }
        }
            break;
        case 3 : {
            Gender gen;
            char permission;
            showInfoMessage("мужчина или женщина?(1/2)");
            choice(permission);
            if (permission == '1') gen = MEN;
            else gen = WOMEN;
            for (Faculty &f: faculties)
                for (Department &d: f.getDepartments())
                    for (Group &g: d.getGroups())
                        for (Student &s: g.getStudents())
                            if (s.getGender() == gen) {
                                gender = (s.getGender() == MEN) ? " - men" : " - women";
                                students.push_back(
                                        s.getFirstname() + " " + s.getSurname() + " " + s.getPatronymic() + gender + " "
                                        + std::to_string(g.getNumber()) + " " + d.getTitle() + " " + f.getTitle());
                            }
        }
            break;
    }
    return students;
}
