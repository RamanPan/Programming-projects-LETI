#include "functionality.h"
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <iostream>

void consoleInterface() {
    SetConsoleOutputCP(CP_UTF8);
    bool exitFlag = false, permissionFlag;
    short symbol;
    short position = 1;
    int counterElements, lengthList, index = -1;
    showHelloMessage();
    Element *startElement = createList(counterElements, lengthList), *tempPtr;
    showMenu(position, lengthList, startElement);
    while (!exitFlag) {
        permissionFlag = false;
        symbol = (short) getch();
        if (symbol == FIRST_BYTE_ARROW) symbol = (short) getch();
        switch (symbol) {
            case ARROW_UP:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case W:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case S:
                if (position < MAX_ARROW_POSITION) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case ESC:
                exitFlag = true;
                break;
            case ENTER:
                permissionFlag = true;
                break;
            case ZERO:
                position = 10;
                break;
            case ONE:
                position = 1;
                break;
            case TWO:
                position = 2;
                break;
            case THREE:
                position = 3;
                break;
            case FOUR:
                position = 4;
                break;
            case FIVE:
                position = 5;
                break;
            case SIX:
                position = 6;
                break;
            case SEVEN:
                position = 7;
                break;
            case EIGHT:
                position = 8;
                break;
            case NINE:
                position = 9;
                break;
            default:;
        }
        showMenu(position, lengthList, startElement);
        switch (position) {
            case 1:
                if (permissionFlag) {
                    deleteList(startElement, lengthList);
                    startElement = createList(counterElements, lengthList);
                    showMenu(position, lengthList, startElement);
                }
                break;
            case 2:
                if (permissionFlag) {
                    if (lengthList == 0) {
                        startElement = addElementToList(index, startElement, nullptr, lengthList);
                    } else {
                        index = getIndexForAdd(lengthList);
                        if (index == -1) startElement = addElementToList(index, startElement, nullptr, lengthList);
                        else addElementToList(index, startElement, nullptr, lengthList);
                    }
                    showMenu(position, lengthList, startElement);
                }
                break;
            case 3:
                if (permissionFlag) {
                    if (lengthList == 0) startElement = insertAFewElements(index, startElement, lengthList);
                    else {
                        index = getIndexForAdd(lengthList);
                        if (index == -1) startElement = insertAFewElements(index, startElement, lengthList);
                        else insertAFewElements(index, startElement, lengthList);
                    }
                    showMenu(position, lengthList, startElement);
                }
                break;
            case 4:
                if (permissionFlag) {
                    if (lengthList != 0) {
                        index = getIndex(lengthList);
                        if (index == 0) startElement = deleteElement(index, startElement, nullptr, lengthList);
                        else deleteElement(index, startElement, nullptr, lengthList);
                        if (lengthList == 0) startElement = nullptr;
                        showMenu(position, lengthList, startElement);
                    } else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                        printf("Нельзя удалить элемент из пустого списка!\n");
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                    }
                }
                break;
            case 5:
                if (permissionFlag) {
                    if (lengthList != 0) {
                        tempPtr = deletePartOfList(startElement, lengthList);
                        if (tempPtr != nullptr) startElement = tempPtr;
                        if (lengthList == 0) startElement = nullptr;
                        showMenu(position, lengthList, startElement);
                    } else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                        printf("Нельзя удалять элементы из пустого списка!\n");
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                    }
                }
                break;
            case 6:
                if (permissionFlag && lengthList != 0) {
                    startElement = reverseList(startElement, lengthList);
                    showMenu(position, lengthList, startElement);
                }
                break;
            case 7:
                if (permissionFlag) {
                    startElement = sortingListAscending(startElement);
                    showMenu(position, lengthList, startElement);
                }
                break;
            case 8:
                if (permissionFlag) {
                    startElement = sortingListDescending(startElement);
                    showMenu(position, lengthList, startElement);
                }
                break;
            case 9:
                if (permissionFlag) {
                    deleteList(startElement, lengthList);
                    startElement = nullptr;
                    showMenu(position, lengthList, startElement);
                }
                break;
            case 10:
                if (permissionFlag)
                    exitFlag = true;
                break;
            default:;
        }
    }
}

void showHelloMessage() {
    printf("Приветствую!\n В этой программе вы можете повзаимодействовать с односвязным связным списком.\n");
}

void showMenu(int position, int lengthList, Element *startList) {
    system("cls");
    printf("Выберите действие:\n");
    if (position == 1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("1) Пересоздать список <--\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    } else printf("1) Пересоздать список\n");
    if (position == 2) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("2) Добавить элемент по индексу <--\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    } else printf("2) Добавить элемент по индексу\n");
    if (position == 3) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("3) Вставить список новых элементов <--\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    } else printf("3) Вставить список новых элементов\n");
    if (position == 4) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("4) Удалить элемент по индексу <--\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    } else printf("4) Удалить элемент по индексу\n");
    if (position == 5) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("5) Удалить часть списка <--\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    } else printf("5) Удалить часть списка\n");
    if (position == 6) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("6) Перевернуть список <--\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    } else printf("6) Перевернуть список\n");
    if (position == 7) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("7) Отсортировать список по возрастанию <--\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    } else printf("7) Отсортировать список по возрастанию\n");
    if (position == 8) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("8) Отсортировать список по убыванию <--\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    } else printf("8) Отсортировать список по убыванию\n");
    if (position == 9) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("9) Удалить весь список <--\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    } else printf("9) Удалить весь список\n");
    if (position == 10) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("0) Выход <--\n");
    } else printf("0) Выход\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    printf("Длина списка: %d\n", lengthList);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    printf("Список: ");
    showList(startList);
}

void showList(Element *startList) {
    Element *currentElement = startList;
    while (currentElement != nullptr) {
        std::cout << currentElement->number << " ";
        currentElement = currentElement->next;
    }
    std::cout << std::endl;
}

Element *createList(int &counterElements, int &lengthList) {
    system("cls");
    std::cout << "Введите кол-во создаваемых элементов" << std::endl;
    lengthList = validation();
    counterElements = lengthList;
    Element *current = nullptr, *next = nullptr;
    for (int i = lengthList; i > 0; --i) {
        current = new Element;
        current->number = i;
        current->next = next;
        next = current;
    }
    return current;
}

Element *getElementByIndex(int index, Element *startList) {
    if (index < 0) return nullptr;
    Element *current = startList;
    for (int i = 0; i < index; ++i) {
        current = current->next;
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
    int quantityElements = validation(), i = 0;
    Element *addedElement = nullptr;
    if (startList == nullptr || index == -1) {
        i = 1;
        startList = addElementToList(index, startList, nullptr, lengthList);
        if (index == -1) index++;
//        addedElement = startList;
    }
    for (; i < quantityElements; ++i) {
        addedElement = addElementToList(index, startList, addedElement, lengthList);
    }
    return startList;
}

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

Element *reverseList(Element *startList, int lengthList) {
    Element *arr[lengthList];
    for (int i = 0; i < lengthList; ++i) {
        arr[i] = startList;
        startList = startList->next;
    }
    for (int i = lengthList - 1; i >= 0; --i) {
        if (i != 0) arr[i]->next = arr[i - 1];
        else arr[i]->next = nullptr;
    }

    return arr[lengthList - 1];
}

Element *getTail(Element *cur) {
    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;
    return cur;
}

Element *sortingListAscending(Element *startList) {
    return quickSortRecurAscending(startList, getTail(startList));
}

Element *sortingListDescending(Element *startList) {
    return quickSortRecurDescending(startList, getTail(startList));
}

Element *partitionForAscending(Element *head, Element *end,
                               Element **newHead,
                               Element **newEnd) {
    Element *pivot = end;
    Element *prev = nullptr, *cur = head, *tail = pivot;
    while (cur != pivot) {
        if (cur->number < pivot->number) {
            if ((*newHead) == nullptr)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            Element *tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    if ((*newHead) == nullptr)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

Element *partitionForDescending(Element *head, Element *end,
                                Element **newHead,
                                Element **newEnd) {
    Element *pivot = end;
    Element *prev = nullptr, *cur = head, *tail = pivot;
    while (cur != pivot) {
        if (cur->number > pivot->number) {
            if ((*newHead) == nullptr)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            Element *tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    if ((*newHead) == nullptr)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

Element *quickSortRecurAscending(Element *head,
                                 Element *end) {
    if (!head || head == end)
        return head;
    Element *newHead = nullptr, *newEnd = nullptr;
    Element *pivot;
    pivot = partitionForAscending(head, end, &newHead, &newEnd);
    if (newHead != pivot) {
        Element *tmp = newHead;
        while (tmp->next != pivot) tmp = tmp->next;
        tmp->next = nullptr;
        newHead = quickSortRecurAscending(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    pivot->next = quickSortRecurAscending(pivot->next, newEnd);
    return newHead;
}

Element *quickSortRecurDescending(Element *head,
                                  Element *end) {
    if (!head || head == end)
        return head;
    Element *newHead = nullptr, *newEnd = nullptr;
    Element *pivot;
    pivot = partitionForDescending(head, end, &newHead, &newEnd);
    if (newHead != pivot) {
        Element *tmp = newHead;
        while (tmp->next != pivot) tmp = tmp->next;
        tmp->next = nullptr;
        newHead = quickSortRecurDescending(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    pivot->next = quickSortRecurDescending(pivot->next, newEnd);
    return newHead;
}

int getIndex(int &lengthList) {
    printf("Введите индекс(от 0 до %d)\n", lengthList - 1);
    return validationWithArgument(0, lengthList - 1);
}


int getIndexForAdd(int &lengthList) {
    printf("Введите индекс(от -1 до %d, где -1 - добавление в самое начало)\n", lengthList - 1);
    return validationWithArgument(-1, lengthList - 1);
}

long validation() {
    bool validationFlag = false;
    double result;
    while (!validationFlag) {
        if (scanf("%lf", &result)) {
            if (!checkOverflow(result)) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("Неправильный ввод! Число вышло за границу дозволенного! Попробуйте снова!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            } else validationFlag = true;
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неправильный ввод! Попробуйте снова!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
        fflush(stdin);
    }
    return (long) result;
}

long validationWithArgument(int min, int max) {
    long result;
    do {
        result = validation();
        if (result > max || result < min) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неверный ввод! Значение должно быть от %d до %d\n", min,
                   max);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
    } while (result > max || result < min);
    return result;
}

void choice(char &YN) {
    bool exit = false;
    while (!exit) {
        YN = (char) getchar();
        fflush(stdin);
        if (YN == '1' || YN == '2') exit = true;
        else if (YN != ENTER) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неверный ввод! Значение должно быть либо 1, либо 2 \n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
    }
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}




