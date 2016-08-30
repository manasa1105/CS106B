/*
 * File: graphtypes.h
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * ------------------------------------------
 * This file defines the basic Node and Arc types.  Depending on your
 * data structure design, your implementation may need to add fields
 * to these types to keep track of information required by the
 * Pathfinder application.
 */

#ifndef _graphtypes_h
#define _graphtypes_h

#include <string>
#include "graph.h"
#include "gtypes.h"
#include "map.h"
#include "set.h"

struct Node;     /* Forward references to these two types so  */
struct Arc;      /* that the C++ compiler can recognize them. */

/*
 * Type: Node
 * ----------
 * This type represents an individual node.
 */

struct Node {
   std::string name;
   Set<Arc *> arcs;
   //Set<std::string> nodesConnected;
   GPoint nodePosition;
};

/*
 * Type: Arc
 * ---------
 * This type represents an individual arc.
 */

struct Arc {
   Node *start;
   Node *finish;
   double cost;
};

#endif
