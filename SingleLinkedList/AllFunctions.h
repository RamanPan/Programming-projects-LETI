#ifndef SINGLELINKEDLIST_ALLFUNCTIONS_H
#define SINGLELINKEDLIST_ALLFUNCTIONS_H

#include "constants.h"
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <iostream>


struct Element {
    int number;
    Element *next;
};

void showMenu(int position, int lengthList, Element *startList);

void showList(Element *startList);

Element *addElementToList(int index, Element *startList, Element *elementBefore, int &lengthList);

Element *insertAFewElements(int index, Element *startList, int &lengthList);

Element *getElementByIndex(int index, Element *startList);

void showHelloMessage();

void consoleInterface();

Element *createList(int &counterElements, int &lengthList);

void deleteList(Element *startList, int &lengthList);

Element *deleteElement(int index, Element *startList, Element *elementBeforeElementForDelete, int &lengthList);

Element *deletePartOfList(Element *startList, int &lengthList);

Element *reverseList(Element *startList, int lengthList);

Element *sortingListAscending(Element *startList);

Element *sortingListDescending(Element *startList);

Element *partitionForAscending(Element *head, Element *end,
                               Element **newHead,
                               Element **newEnd);

Element *partitionForDescending(Element *head, Element *end,
                                Element **newHead,
                                Element **newEnd);

Element *getTail(Element *cur);

Element *quickSortRecurAscending(Element *head,
                                 Element *end);

Element *quickSortRecurDescending(Element *head,
                                  Element *end);

int getIndex(int &lengthList);

int getIndexForAdd(int &lengthList);

long validation();

bool checkOverflow(double d);

void choice(char &YN);

long validationWithArgument(int min, int max);

#endif //SINGLELINKEDLIST_ALLFUNCTIONS_H
