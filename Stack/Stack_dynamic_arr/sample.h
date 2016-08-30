
#ifndef _sample_h
#define _sample_h

#include "error.h"
#include "strlib.h"
using namespace std;

template <typename type>
class stack {

public:

    //stack contructor
    stack();

    //stack destructor
    ~stack();

    //returns the size of the stack
    int size();

    //returns the true if the stack is empty
    bool isEmpty();

    //clears all the elements from the stack
    void clear();

    //adds a value of the valuetype to the begining of the stack
    void push(type value);

    //removes the firstmost value in from the stack
    type pop();

    //shows what the first value in the stack is
    type peek();

    //prints stack
    void print();

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

private:

    type *array;
    int capacity;
    int count;
    void expandCapacity();

};

template <typename type>
stack<type>::stack() {
    capacity = 5;
    count = 0;
    array = new type[capacity];
}

template <typename type>
stack<type>::~stack() {
    delete [] array;
}

template <typename type>
int stack<type>::size() {
    return count;
}

template <typename type>
bool stack<type>::isEmpty() {
    return (count==0);
}

template <typename type>
void stack<type>::clear() {
    count=0;
}

template <typename type>
void stack<type>::push(type value) {
    if(count>=capacity) {
        expandCapacity();
    }
    array[count] = value;
    count++;
}

template <typename type>
type stack<type>::pop() {
    if(count==0) {
        error("Can't pop from an empty stack.");
        return array[0];
    }
    else {
        type value = array[count-1];
        count--;
        return value;
    }
}

template <typename type>
type stack<type>::peek() {
    if(count==0) {
        error("Can't peek into an empty stack.");
        return array[0];
    }
    else {
        return array[count-1];
    }
}


template <typename type>
void stack<type>::print() {
    string str = "";
    for(int i=0; i<count; i++) {
        str += (integerToString(array[i]) + " ");
    }
    cout << "Current stack is: " << str << endl;
}

template <typename type>
void stack<type>::expandCapacity() {
    capacity = capacity*2;
    type *tempArray = array;
    array = new type[capacity];
    for(int i=0; i<count; i++) {
        array[i] = tempArray[i];
    }
    delete [] tempArray;
}


#endif
