
#include "Subject.h"

Subject::Subject(const QString &name, int mark) : name(name), mark(mark) {}

const QString &Subject::getName() const {
    return name;
}

void Subject::setName(const QString &name) {
    Subject::name = name;
}

int Subject::getMark() const {
    return mark;
}

void Subject::setMark(int mark) {
    Subject::mark = mark;
}

Subject::Subject() {}
