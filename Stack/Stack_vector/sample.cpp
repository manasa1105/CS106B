
#include <iostream>
#include <string>
#include "error.h"
#include "sample.h"
using namespace std;

stack::stack() {
}

stack::~stack() {
    vec.clear();
}

int stack::size() {
    return vec.size();
}

bool stack::isEmpty() {
    return vec.isEmpty();
}

void stack::clear() {
    vec.clear();
}

void stack::push(int value) {
    vec.insert(0, value);
}

int stack::pop() {
    if(vec.isEmpty()) {
        error("Can't pop from an empty stack.");
        return -1;
    }
    else {
        int value = vec.get(0);
        vec.remove(0);
        return value;
    }
}

int stack::peek() {
    if(vec.isEmpty()) {
        error("Can't peek into an empty stack.");
        return -1;
    }
    else {
        return vec.get(0);
    }
}

void stack::print() {
    cout << "Current stack is " << vec.toString() << endl;
}

