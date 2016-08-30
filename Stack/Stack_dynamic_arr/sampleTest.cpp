
#include <iostream>
#include <string>
#include "console.h"
#include "sample.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;


/* Main program */

int main() {
   stack<string> stk;
   stk.push("manu");
   stk.push("deepu");
   stk.push("sunitha");
   stk.push("maddy");
   stk.pop();
   stk.print();
   cout<<"is empty? "<<stk.isEmpty()<<endl;
   cout<<"size: "<<stk.size()<<endl;
   stk.clear();
   cout<<"is empty? "<<stk.isEmpty()<<endl;
   stk.print();
   return 0;
}
