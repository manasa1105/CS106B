
#include <iostream>
#include <string>
#include "console.h"
#include "sample.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;


/* Main program */

int main() {
    stack stk;
    stk.push(0);
    stk.push(1);
    stk.push(2);
    stk.push(3);
    stk.pop();
    cout<<stk.size()<<endl;
    stk.print();
    stk.clear();
    stk.peek();
   return 0;
}
