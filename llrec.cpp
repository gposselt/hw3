#include "llrec.h"


//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot) {

    smaller = nullptr;
    larger = nullptr;

    if (head == nullptr) {
        return;
    }

    Node* tempNext = head->next;

    if (head->val > pivot) {
        larger = head;
        head = nullptr;
        larger->next = nullptr;
        return llpivot(tempNext, smaller, larger->next, pivot);

    }

    smaller = head;
    head = nullptr;
    smaller->next = nullptr;
    llpivot(tempNext, smaller->next, larger, pivot);
}


