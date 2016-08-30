/*
 * File: Pathfinder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Pathfinder application
 * for Assignment #5.
 */

// [TODO: complete this implementation]

#include <iostream>
#include <string>
#include <fstream>
#include "console.h"
#include "filelib.h"
#include "gevents.h"
#include "ginteractors.h"
#include "graph.h"
#include "gpathfinder.h"
#include "graphtypes.h"
#include "gwindow.h"
#include "simpio.h"
#include "error.h"
#include "path.h"
#include "pqueue.h"
using namespace std;

/* Constants */

//const string DEFAULT_MAP = "USA.txt";
//const string DEFAULT_IMAGE = "USA.png";

/* Function prototypes */

void ReadFile(string & DEFAULT_IMAGE, Graph<Node, Arc> &graph);
Vector<Arc* > FindShortestPath(Node* start, Node* finish);
Set<Arc *> FindConnectedPath(Graph<Node, Arc> & graph);
void PrintGraph(Graph<Node, Arc> & graph);
void eventLoop(Graph<Node, Arc> graph);

/* Starter version of the main program */

int main() {
    Graph<Node, Arc> graph;
    GWindow gw(WINDOW_WIDTH, WINDOW_HEIGHT);
    initPathfinderGraphics(gw);
    gw.addToRegion(new GButton("Map"), "SOUTH");
    gw.addToRegion(new GButton("Dijkstras"), "SOUTH");
    gw.addToRegion(new GButton("Kruskals"), "SOUTH");
    gw.addToRegion(new GButton("Quit"), "SOUTH");
    //drawPathfinderMap(DEFAULT_IMAGE);
    eventLoop(graph);
    return 0;
}

/*
 * Function: eventLoop
 * Usage: eventLoop();
 * -------------------
 * Waits for events to occur and then executes the appopriate action.
 * Note that this function never returns.  The program exits only when
 * a command executes the exitGraphics function.
 */

void eventLoop(Graph<Node, Arc> graph) {
   while (true) {
      GActionEvent e = waitForEvent(ACTION_EVENT);
      string cmd = e.getActionCommand();
      if (cmd == "Quit") exitGraphics();
      else if(cmd == "Map") {
          string DEFAULT_IMAGE;
          ReadFile(DEFAULT_IMAGE, graph);
      }

      else if(cmd == "Dijkstras") {
          string depart = getLine("Type the name of start city.");
          Node* departNode = graph.getNode(depart);
          string arrive = getLine("Type the name of arrival city.");
          Node* arriveNode = graph.getNode(arrive);
          Vector<Arc* > path ;
          path = FindShortestPath(departNode, arriveNode);
          for(int i=0; i<path.size(); i++) {
              drawPathfinderNode(path.get(i)->start->nodePosition,
                                 HIGHLIGHT_COLOR, path.get(i)->start->name);
              drawPathfinderArc(path.get(i)->start->nodePosition,
                                path.get(i)->finish->nodePosition, HIGHLIGHT_COLOR);
              if(i==path.size()-1) {
                  drawPathfinderNode(path.get(i)->finish->nodePosition,
                                     HIGHLIGHT_COLOR, path.get(i)->finish->name);
              }
          }
      }

      else if(cmd == "Kruskals") {
          Set<Arc* > set = FindConnectedPath(graph);
          for(Arc* arc : set) {
              drawPathfinderNode(arc->start->nodePosition,
                                 HIGHLIGHT_COLOR, arc->start->name);
              drawPathfinderArc(arc->start->nodePosition,
                                arc->finish->nodePosition, HIGHLIGHT_COLOR);
              drawPathfinderNode(arc->finish->nodePosition,
                                 HIGHLIGHT_COLOR, arc->finish->name);
          }
      }
   }
}

/* reads the file line by line and draws the image in the file onto the GCanvs,
 * creats individual structs for each node, individual structs for all arcs,
 * and helps draws the map onto the canvas when the map button is clicked.
 */

void ReadFile(string & DEFAULT_IMAGE, Graph<Node, Arc> & graph) {
    ifstream infile;
    promptUserForFile(infile, "Input File: ");
    string line;
    getline(infile, line);  //first line of the file containing the name of the image file
    DEFAULT_IMAGE = line;
    drawPathfinderMap(DEFAULT_IMAGE);
    getline(infile, line);  //second line of the file containing "NODES"
    if(line != "NODES") {
        error("Input file is malformed.");
    }

    TokenScanner scanner;
    getline(infile, line);
    while(line != "ARCS") {
        scanner.setInput(line);
        Node* node = new Node;
        scanner.ignoreWhitespace();
        node->name = scanner.nextToken();
        scanner.ignoreWhitespace();
        int X_value = stringToInteger(scanner.nextToken());
        scanner.ignoreWhitespace();
        int Y_value = stringToInteger(scanner.nextToken());
        GPoint pt(X_value, Y_value);
        node->nodePosition = pt;
        graph.addNode(node);
        drawPathfinderNode(node->nodePosition, DIM_COLOR, node->name);
        getline(infile, line);
    }

    if(line != "ARCS") {
        error("Input file is malformed.");
    }

    getline(infile, line);
    while(line != "") {
        scanner.setInput(line);
        Arc* arc = new Arc;
        Arc* arcRev = new Arc;
        scanner.ignoreWhitespace();
        Node* startNode = graph.getNode(scanner.nextToken());
        arc->start = startNode;
        scanner.ignoreWhitespace();
        Node* endNode = graph.getNode(scanner.nextToken());
        arc->finish = endNode;
        scanner.ignoreWhitespace();
        int costStrToInt = stringToInteger(scanner.nextToken());
        arc->cost = costStrToInt;
        //adding the arc in A->B
        graph.addArc(arc);
        //adding the arc in B->A
        arcRev->start = endNode;
        arcRev->finish = startNode;
        arcRev->cost = costStrToInt;
        graph.addArc(arcRev);
        drawPathfinderArc(startNode->nodePosition, endNode->nodePosition, DIM_COLOR);
        getline(infile, line);
    }
    PrintGraph(graph);
}

//Prints all the nodes, arcs, and cost associated with each arc onto the canvas
void PrintGraph(Graph<Node, Arc> & graph) {
    for (Arc* arc : graph.getArcSet()) {
        cout << arc->start->name << " " << arc->finish->name << " " << arc->cost << endl;
    }
}

//using Dijstras algorithm to find the shortes distance
Vector<Arc* > FindShortestPath(Node* start, Node* finish) {
    Path path;
    PriorityQueue< Path > queue;
    Map<string, double> fixed;
    while(start != finish) {
        if(!fixed.containsKey(start->name)) {
            fixed.put(start->name, path.getCost());
            for(Arc* arc : start->arcs) {
                if(!fixed.containsKey(arc->finish->name)) {
                    path.addArcToPath(arc);
                    queue.enqueue(path, path.getCost());
                    path.deleteArcFromPath();
                }
            }
        }
        //if no path exists
        if(queue.isEmpty()) {
            path.clear();
            return path.getPathVec();
        }
        path = queue.dequeue();
        start = path.getPathVec()[path.getPathVec().size() - 1]->finish;
    }
    return path.getPathVec();
}

Set<Arc *> FindConnectedPath(Graph<Node, Arc> & graph) {
    PriorityQueue< Arc* > queue;
    Map<string, Set<string> > connectedMap;

    //gets all the arcs from the graph into the pqueue with the cost as priority
    for(Arc * arc : graph.getArcSet()) {
        queue.enqueue(arc, arc->cost);
    }

    /* gets all the nodes from the graph into the map as its keys having mapped to its
     * own names individually as set of connected arcs.
     */
    for(Node * node : graph.getNodeSet()) {
        Set<string> connectedSet;
        connectedSet.add(node->name);
        connectedMap.put(node->name, connectedSet);
    }

    cout << "size of queue of arcs is: " << queue.size() << endl;
    cout << "map of nodes connected to their sets: " << connectedMap.toString() << endl;

    Vector <Set<string> > vec;
    Set<string> tempSet;
    Set<Arc* > consideredArc;
    vec.add(tempSet);
    while(!queue.isEmpty()) {
        Arc* dequeueArc = queue.dequeue();
        cout<<"dequeued Arc: " << dequeueArc->start->name
           << "->" << dequeueArc->finish->name <<endl;
        cout << endl;
        bool contains = false;
        for(int i = 0; i < vec.size(); i++) {
            //cout << vec.toString() << endl;
            if(vec.get(i).contains(dequeueArc->start->name)
                && vec.get(i).contains(dequeueArc->finish->name)) {
                contains = true;
                break;
            }
        }
        if(contains==false) {
            //considers the arc
            consideredArc.add(dequeueArc);
            cout << "arc considered " << dequeueArc->start->name
                << "->" << dequeueArc->finish->name << endl;

            //loads the temp set with all the elements from the set of A and the set of B
            tempSet = connectedMap.get(dequeueArc->start->name)
                    + connectedMap.get(dequeueArc->finish->name);
            vec.add(tempSet);
            cout << "temp arc set contains: " <<  tempSet.toString() << endl;

            /* updates every set associated with all the nodes in the temp set
             * with the union of the temp set and the set of the node
             */
            for(string str : tempSet) {
                connectedMap.put(str, connectedMap.get(str) + tempSet);
            }
            cout << "map of nodes connected to their sets: "
                << connectedMap.toString() << endl;
            cout << endl;
        }
    }
    return consideredArc;
}

/*
 *code which helps the user to click on two nodes
 *to calculate the shortest distance using dijaktras

Set<Node* > nodeSet;
nodeSet = graph.getNodeSet();
Node* depart;
GPoint start;
cout << "Please click the departures point." << endl;
start = getMouseClick();
for(Node* node : nodeSet) {
    if(node->nodePosition == start) {
        depart = node;
    }
}
Node* arrive;
GPoint finish;
cout << "please click on the destination point." << endl;
finish = getMouseClick();
for(Node* node : nodeSet) {
    if(node->nodePosition == finish) {
        arrive = node;
    }
}
*/

