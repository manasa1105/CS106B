/*
 * File: pqueue.cpp (heap version)
 * -------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a heap as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods and to make a change to the definition of the
 * assignment operator so that it deletes any old storage.
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
    return count;
}

bool PriorityQueue::isEmpty() {
    if (count == 0) {
        return true;
    }
    return false;
}

void PriorityQueue::clear() {
    delete[] array;
    array = new ValuePriorityPair[capacity];
    count = 0;
}

void PriorityQueue::enqueue(string value, double priority) {
    if(count == capacity) {
        expandCapacity();
    }
    count++;
    array[count-1].value = value;
    array[count-1].priority = priority;
    checkParent(count-1);
}

void PriorityQueue::checkParent(int pos) {
    //if the node is not the root node
    if(pos > 0) {
        //if parent node is small then swap them
        if(array[(pos-1)/2].priority > array[pos].priority) {
            ValuePriorityPair temp = array[pos];
            array[pos] = array[(pos-1)/2];
            array[(pos-1)/2] = temp;
            checkParent((pos-1)/2);
        }
    }
}

string PriorityQueue::dequeue() {
    string dequeuedVal = "Queue is empty";
    if(count != 0) {
        dequeuedVal = array[0].value;
        array[0] = array[count-1];
        count--;
        checkChildren(0);
    }
    cout << dequeuedVal << endl;
    return dequeuedVal;
}

//check for the children and swap positions (smallest with larger) if required
void PriorityQueue::checkChildren(int pos) {
    int swapPosition;
    if(pos > count) {
        return;
    }
    else {
        swapPosition = SwapPos(pos);
        if(swapPosition != -1) {
            ValuePriorityPair temp = array[pos];
            array[pos] = array[swapPosition];
            array[swapPosition] = temp;
            checkChildren(swapPosition);
        }
    }
}

//private method to swap the parent node with any of its child node when required
int PriorityQueue::SwapPos(int pos) {
    int swapPosition = -1;
        int smallerNode;
        int NumOfChildren = NumberOfChildren(pos);
        if(NumOfChildren == 2)
            smallerNode = smallerChildNode(2*pos+1, 2*pos+2);
        else if(NumOfChildren == 1)
            smallerNode = 2*pos+1;

        if(NumOfChildren > 0) {
            if(array[smallerNode].priority < array[pos].priority)
                swapPosition = smallerNode;
        }
        return swapPosition;
}

//private method to help get the smaller child of the two children(left and right)
int PriorityQueue::smallerChildNode(int left, int right) {
    if(array[left].priority < array[right].priority)
        return left;
    else
        return right;
}

//checking for the number of children for a perticular node (at position pos)
int PriorityQueue::NumberOfChildren(int pos) {
    if(2*pos+2 < count)
        return 2;
    else if(2*pos+1 < count)
        return 1;
    else
        return 0;
}


/*
string PriorityQueue::dequeue() {
    if(count != 0) {
        string dequeuedVal = array[0].value;
        array[0] = array[count-1];
        count--;
        checkChildren(0);
        cout << dequeuedVal << endl;
        return dequeuedVal;
    }
    else {
        cout << "Queue is empty" << endl;
        return "Queue is empty";
    }
}

void PriorityQueue::checkChildren(int pos) {
    //main base case (the node is not a leaf node (atleast one child is available))
    if ((2*pos)+1 < count) {
        //if both left child and right child are available for the node
        if((2*pos)+1 < count && (2*pos)+2 < count) {
            if ((array[(2*pos)+1].priority < array[(2*pos)+2].priority)
                    && (array[(2*pos)+1].priority < array[pos].priority)) {
                ValuePriorityPair temp = array[pos];
                array[pos] = array[(2*pos)+1];
                array[(2*pos)+1] = temp;
                checkChildren((2*pos)+1);
            }
            else if((array[(2*pos)+2].priority < array[(2*pos)+1].priority)
                    && (array[(2*pos)+2].priority < array[pos].priority)) {
                ValuePriorityPair temp = array[pos];
                array[pos] = array[(2*pos)+2];
                array[(2*pos)+2] = temp;
                checkChildren((2*pos)+2);
            }
        }
        //possible base case(if only left child is available for the node)
        else if((2*pos)+1 < count && (2*pos)+2 > count) {
            if (array[(2*pos)+1].priority < array[pos].priority) {
                ValuePriorityPair temp = array[pos];
                array[pos] = array[(2*pos)+1];
                array[(2*pos)+1] = temp;
            }
        }
    }
}
*/

string PriorityQueue::peek() {
    return array[0].value;
}

double PriorityQueue::peekPriority() {
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
 * The constructor and assignment operators follow a standard paradigm,
 * as described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      // TODO: Include code to delete any data from the old queue
      deepCopy(src);
   }
   return *this;
}



