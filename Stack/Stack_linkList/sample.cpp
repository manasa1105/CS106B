
#include <iostream>
#include <string>
#include "error.h"
#include "sample.h"
using namespace std;

stack::stack() {
    count = 0;
    head = NULL;
}

stack::~stack() {
    DeleteAll(head);
}

int stack::size() {
    return count;
}

bool stack::isEmpty() {
    return (count==0);
}

void stack::clear() {
    DeleteAll(head);
    count=0;
}

void stack::push(int value) {
    InsertNode(head, 0, value);
    count++;
}

int stack::pop() {
    if(count==0) {
        error("Can't pop from an empty stack.");
        return -1;
    }
    else {
        int val = head->value;
        count--;
        DeleteNode(head, 0);
        return val;
    }
}

int stack::peek() {
    return head->value;
}

void stack::print() {
    PrintList(head);
}

void stack::DeleteAll(node * &head) {
    while(true) {
        if(head==NULL) {
            break;
        }
        node *cell = head;
        head = head->next;
        delete cell;
    }
}

void stack::InsertNode(node * &head, int pos, int val) {
    node *cell = new node;
    cell->value = val;
    if(pos==0) {
        cell->next = head;
        head = cell;
    }
    else {
        node *nextNode = head;
        for(int i=0; i<pos-1; i++) {
            nextNode = nextNode->next;
        }
        cell->next = nextNode->next;
        nextNode->next = cell;
    }
}

void stack::DeleteNode(node * &head, int pos) {
    if(pos==0) {
        node *cell = head;
        head = head->next;
        delete cell;
    }
    else {
        node *nextNode = head;
        for(int i=0; i<pos-1; i++) {
            nextNode = nextNode->next;
        }
        node *cell = nextNode->next;
        nextNode->next = nextNode->next->next;
        delete cell;
    }
}

void stack::PrintList(node *head) {
    for(node *cur = head; cur!=NULL; cur=cur->next) {
        cout<<cur->value<<endl;
    }
}


