
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
    stk.push(4);
    stk.push(5);
    stk.push(6);
    stk.push(7);
    stk.push(8);
    stk.push(9);
    stk.push(10);
    stk.pop();
    stk.print();
    cout << "peek: "<< stk.peek()<<endl;
    cout<<"is empty? "<<stk.isEmpty()<<endl;
    cout<<"size: "<<stk.size()<<endl;
    stk.clear();
    cout<<"is empty? "<<stk.isEmpty()<<endl;
    stk.print();
   return 0;
}
