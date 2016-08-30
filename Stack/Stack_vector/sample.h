
#ifndef _sample_h
#define _sample_h

#include  <vector.h>
#include "error.h"

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
    void push(int value);

    //removes the firstmost value in from the stack
    int pop();

    //shows what the first value in the stack is
    int peek();

    //prints stack
    void print();

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

private:
    Vector<int> vec;

};

#endif
