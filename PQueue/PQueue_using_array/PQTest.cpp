/*
 * File: PQTest.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This is the starter file for the test program for Assignment #5.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "pqueue.h"
#include "simpio.h"
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

/* Function prototypes */

void helpCommand();

/* Main program */

int main() {
   PriorityQueue pq;
   while (true) {
      string cmd = getLine("> ");
      if (cmd == "help") {
         helpCommand();
      }
      else if(cmd.substr(0, 7) == "enqueue") {
          double priority = stringToDouble(cmd.substr(cmd.length()-1, 1));
          string cmdSubstr = cmd.substr(8);
          string value = cmdSubstr.substr(0, cmdSubstr.length()-2);
          pq.enqueue(value, priority);
      }
      else if(cmd == "dequeue") {
          pq.dequeue();
      }
      else if(cmd == "peek") {
          pq.peek();
      }
      else if(cmd == "peekPriority") {
          pq.peekPriority();
      }
      else if(cmd == "isEmpty") {
          pq.isEmpty();
      }
      else if(cmd == "size") {
          pq.size();
      }
      else if(cmd == "clear") {
          pq.clear();
      }
      else if(cmd == "list") {
          pq.list();
      }
      else {
          cout << "Undefined command: " << cmd << endl;
      }
   }
   return 0;
}

/*
 * Function: helpCommand
 * ---------------------
 * Displays a list of the required commands.  If you extend this program,
 * you should add new entries to this function.
 */

void helpCommand() {
   cout << "enqueue value priority -- Enqueues value at priority" << endl;
   cout << "dequeue -- Dequeues the most urgent item" << endl;
   cout << "peek -- Peeks at the first item without removing it" << endl;
   cout << "peekPriority -- Reports the priority of the first item" << endl;
   cout << "clear -- Clears the queue" << endl;
   cout << "size -- Reports the size of the queue" << endl;
   cout << "isEmpty -- Reports whether the queue is empty" << endl;
   cout << "list -- Lists the elements of the queue" << endl;
   cout << "help -- Prints this message" << endl;
}
