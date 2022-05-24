/*
 * Title: Graph
 * Author: Alperen Can 
 * ID: 21601740
 * Section: 1
 * Assignment: 4
 * Description: Graph header file, using AirportLinkedList and array, adjacency list
*/
#include "AirportLinkedList.h"
#include <iostream>
using namespace std;

class Graph{

private:
    int numVertices;
    AirportLinkedList *adjList;
    int findSmallestWeight(int weight[], int vertexSet[]);
    int getTotalCost();
    bool isEveryVertexVisited(int visited[], int length);
public:
    Graph(int numVertices);
    void addEdge(int source, int dst, int duration);
    void listFlights(int u);
    void shortestPath(int src, int dst);
    void printShortestPath( int dst, int predecessor[]);
    Graph minimizeCost();
    
};



