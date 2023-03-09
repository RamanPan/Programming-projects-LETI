#include "AllFunctions.h"


Element *createList(int &lengthList) {
    system("cls");
    std::cout << "Введите кол-во создаваемых элементов" << std::endl;
    lengthList = validationWithArgument(MIN_ELEMENTS_QUANTITY,MAX_ELEMENTS_QUANTITY);
    Element *current = nullptr, *next = nullptr;
    for (int i = lengthList; i > 0; --i) {
        current = new Element;
        current->number = i;
        current->next = next;
        next = current;
    }
    return current;
}

Element *addElementToList(int index, Element *startList, Element *elementBefore, int &lengthList) {
    Element *newElement = new Element;
    lengthList++;
    std::cout << "Введите значение элемента" << std::endl;
    newElement->number = validation();
    if (startList == nullptr) {
        newElement->next = nullptr;
        startList = newElement;
        return startList;
    }
    if (index == -1) {
        newElement->next = startList;
        return newElement;
    }
    Element *current = (elementBefore == nullptr) ? getElementByIndex(index, startList) : elementBefore;
    newElement->next = current->next;
    current->next = newElement;
    return newElement;
}

Element *insertAFewElements(int index, Element *startList, int &lengthList) {
    std::cout << "Введите кол-во добавляемых элементов" << std::endl;
    int quantityElements = validationWithArgument(MIN_ELEMENTS_QUANTITY,MAX_ELEMENTS_QUANTITY), i = 0;
    Element *addedElement = nullptr;
    if (startList == nullptr || index == -1) {
        i = 1;
        startList = addElementToList(index, startList, nullptr, lengthList);
        if (index == -1) index++;
    }
    for (; i < quantityElements; ++i) {
        addedElement = addElementToList(index, startList, addedElement, lengthList);
    }
    return startList;
}
