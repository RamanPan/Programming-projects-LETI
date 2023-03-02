#include "AllFunctions.h"

Element *deleteElement(int index, Element *startList, Element *elementBeforeElementForDelete, int &lengthList) {
    Element *elementForDelete, *newStartList;
    lengthList--;
    if (index == 0) {
        elementForDelete = startList;
        newStartList = startList->next;
        delete elementForDelete;
        return newStartList;
    }
    if (elementBeforeElementForDelete == nullptr) {
        elementBeforeElementForDelete = getElementByIndex(index - 1, startList);
        elementForDelete = elementBeforeElementForDelete->next;
        elementBeforeElementForDelete->next = elementForDelete->next;
    } else {
        elementForDelete = elementBeforeElementForDelete->next;
        elementBeforeElementForDelete->next = elementForDelete->next;
    }
    delete elementForDelete;
    return elementBeforeElementForDelete;
}

Element *deletePartOfList(Element *startList, int &lengthList) {
    if (lengthList == 1) {
        return deleteElement(0, startList, nullptr, lengthList);
    }
    std::cout << "Введите диапазон удаления" << std::endl;
    printf("Левая граница(от 0 до %d)\n", lengthList - 2);
    int leftLimit = validationWithArgument(0, lengthList - 2);
    printf("Правая граница(от %d до %d)\n", leftLimit, lengthList - 1);
    int rightLimit = validationWithArgument(leftLimit, lengthList - 1);
    Element *elementBeforeForDelete = nullptr;
    while (leftLimit <= rightLimit) {
        if (leftLimit != 0) {
            elementBeforeForDelete = deleteElement(leftLimit, startList, elementBeforeForDelete, lengthList);
            leftLimit++;
        } else {
            startList = deleteElement(leftLimit, startList, elementBeforeForDelete, lengthList);
            rightLimit--;
        }
    }
    return (leftLimit == 0) ? startList : nullptr;
}


void deleteList(Element *startList, int &lengthList) {
    Element *elementForDelete;
    while (startList != nullptr) {
        elementForDelete = startList;
        startList = startList->next;
        delete elementForDelete;
    }
    lengthList = 0;
}
