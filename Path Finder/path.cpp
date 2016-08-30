/*
 * File: path.cpp
 * --------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the path.h interface.
 */

#include <iostream>
#include "path.h"
using namespace std;

/////////////////////////////////////////////////////////////////////
// Your task in this part of the assignment is to write the code   //
// that implements your path.h interface.  For the benefit of      //
// future programmers who will need to work on this interface,     //
// you should also write an extended comment (presumably replacing //
// this to-do box) that documents the design decisions you made    //
// in structuring the Path class as you did.                       //
/////////////////////////////////////////////////////////////////////

Path::Path() {
    pathCost = 0;
}

Path::~Path() {
    vec.clear();
}

Vector<Arc* > Path::getPathVec() {
    return vec;
}

void Path::addArcToPath(Arc* arc) {
    pathCost += arc->cost;
    vec.add(arc);
}

void Path::deleteArcFromPath() {
    pathCost = pathCost - vec.get(vec.size() - 1)->cost;
    vec.remove(vec.size() - 1);
}

int Path::getCost() {
    return pathCost;
}

bool Path::isEmpty() {
    return vec.isEmpty();
}

void Path::clear() {
    vec.clear();
    pathCost = 0;
}

string Path::toString() {
    string str = "";
    for(int i=0; i<vec.size(); i++) {
        if(i==vec.size()-1) {
            str += " " + vec.get(i)->start->name + " " + vec.get(i)->finish->name + " }";
        }
        else if(i==0) {
            str += "{ " + vec.get(i)->start->name;
        }
        else {
            str += vec.get(i)->start->name + " ";
        }
    }
    return str;
}
