/*
 * File: pqueue.cpp (array version)
 * --------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a dynamic array as
 * the underlying representation.  Most of the code is already in place.
 * The only thing that is missing is the implementation of the actual
 * commands.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

PriorityQueue::PriorityQueue() {
    capacity = 10;
    count = 0;
    array = new ValuePriorityPair[capacity];
}

PriorityQueue::~PriorityQueue() {
    delete[] array;
}

int PriorityQueue::size() {
    cout << count << endl;
   return count;
}

bool PriorityQueue::isEmpty() {
    if (count == 0) {
        cout << "true" << endl;
        return true;
    }
    else {
        cout << "false" << endl;
    }
    return false;
}

void PriorityQueue::clear() {
    delete[] array;
    array = new ValuePriorityPair[capacity];
    count = 0;
}

void PriorityQueue::enqueue(string value, double priority) {
    int pos = 0;
    if(count == capacity) {
        expandCapacity();
    }
    if(count != 0) {
        for(int i=0; i<count; i++) {
            if(array[pos].priority > priority) {
                break;
            }
            pos++;
        }
        for(int i=count; i>pos; i--) {
            array[i] = array[i-1];
        }
    }
    array[pos].value = value;
    array[pos].priority = priority;
    count++;
}

string PriorityQueue::dequeue() {
    if (count!=0) {
        string dequeuedVal = array[0].value;
        for (int i=0; i<count; i++) {
            array[i] = array[i+1];
        }
        count--;
        cout << dequeuedVal << endl;
        return dequeuedVal;
    }
    else {
        return "Queue is empty";
    }
}

string PriorityQueue::peek() {
    cout << array[0].value << endl;
   return array[0].value;
}

double PriorityQueue::peekPriority() {
    cout << array[0].priority << endl;
   return array[0].priority;
}

string PriorityQueue::list() {
    string queueList = "";
    for(int i=0; i<count; i++) {
        queueList += (array[i].value + " ");
    }
    cout << queueList << endl;
    return queueList;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow the standard
 * paradigm described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      if (array != NULL) delete[] array;
      deepCopy(src);
   }
   return *this;
}
