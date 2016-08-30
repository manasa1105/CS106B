/*
 * File: path.h
 * ------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the interface for a Path class that encapsulates
 * the idea of a multistep path.
 */

/////////////////////////////////////////////////////////////////////
// Your task in this part of the assignment is to design a Path    //
// class that supports the implementation of Dijkstra's algorithm. //
// As noted in the assignment handout, your class must meet the    //
// following conditions:                                           //
//                                                                 //
// 1. The class must not export any public instance variables.     //
//    All data required to store the path must be private to the   //
//    class.                                                       //
//                                                                 //
// 2. The method that returns the total cost of the path must      //
//    run in constant time.                                        //
//                                                                 //
// 3. The class must export a toString method that returns a       //
//    string composed of the nodes on the path separated by        //
//    arrows formed by the two-character sequence ->.              //
//                                                                 //
// 4. Any heap storage allocated by this class must be freed       //
//    when the object is deleted.                                  //
//                                                                 //
// Beyond those restrictions, you are free to design and implement //
// this class as you see fit.                                      //
/////////////////////////////////////////////////////////////////////

#ifndef _path_h
#define _path_h

#include "graphtypes.h"

class Path {

public:

    //stack contructor
    Path();

    //stack destructor
    ~Path();

    //returns the path stored
    Vector<Arc* > getPathVec();

    //adds arc to the path and updates the cost
    void addArcToPath(Arc* arc);

    //deletes the last arc that was put into the vector
    void deleteArcFromPath();

    //returns the cost of the path
    int getCost();

    //returns true if the vector(path) is empty
    bool isEmpty();

    //clears the vector
    void clear();

    //converts the vector of path to a redable format
    std::string toString();

private:

    Vector<Arc* > vec;
    int pathCost;

};

#endif
