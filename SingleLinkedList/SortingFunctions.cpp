#include "AllFunctions.h"

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
