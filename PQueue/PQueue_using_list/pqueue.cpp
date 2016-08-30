/*
 * File: pqueue.cpp (linked-list version)
 * --------------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a linked list as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

PriorityQueue::PriorityQueue() {
}

PriorityQueue::~PriorityQueue() {
    clear();
}

int PriorityQueue::size() {
    int count = 0;
    for(ValuePriorityPair *cur = head; cur != NULL; cur=cur->next) {
        count++;
    }
    return count;
}

bool PriorityQueue::isEmpty() {
    return head == NULL;
}

void PriorityQueue::clear() {
    while(true) {
        if(head == NULL) {
            break;
        }
        ValuePriorityPair *cell = head;
        head = head->next;
        delete cell;
    }
}

void PriorityQueue::enqueue(string value, double priority) {
    ValuePriorityPair *cell = new ValuePriorityPair;
    cell->value = value;
    cell->priority = priority;
    if (head == NULL) {
        cell->next = NULL;
        head = cell;
        return;
    }
    ValuePriorityPair *prevCell = NULL;
    bool insertDone = false;
    for (ValuePriorityPair *cur = head; cur != NULL; cur=cur->next) {
        if(cur->priority > priority) {
            if(prevCell == NULL) {
                cell->next = head;
                head = cell;
            }
            else {
                cell->next = prevCell->next;
                prevCell->next = cell;
            }
            insertDone = true;
            break;
        }
        prevCell = cur;
    }
    if (!insertDone) {
        cell->next = NULL;
        prevCell->next = cell;
    }
}

string PriorityQueue::dequeue() {
    if(head == NULL) {
        return "The queue is empty";
    }
    ValuePriorityPair *cell = head;
    string dequeuedVal = cell->value;
    head = head->next;
    delete cell;
    return dequeuedVal;
}

string PriorityQueue::peek() {
    if(head == NULL) {
        return "The queue is empty";
    }
    return head->value;
}

double PriorityQueue::peekPriority() {
    if(head == NULL) {
        return "The queue is empty";
    }
    return head->priority;
}

string PriorityQueue::list() {
    string str = "";
    for(ValuePriorityPair *cur = head; cur!=NULL; cur=cur->next) {
        str += (cur->value + " ");
    }
    return str;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow a standard paradigm,
 * as described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      clear();
      deepCopy(src);
   }
   return *this;
}
