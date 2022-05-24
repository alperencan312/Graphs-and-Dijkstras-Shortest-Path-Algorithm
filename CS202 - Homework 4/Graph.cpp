/*
 * Title: Graph
 * Author: Alperen Can 
 * ID: 21601740
 * Section: 1
 * Assignment: 4
 * Description: Graph implementation using AirportLinkedList and array, adjacency list
*/
#include "Graph.h"
//Constructor takes number of vertices and assigns null to each head of linked list
Graph:: Graph(int numVertices){
    this->numVertices = numVertices;
    adjList = new AirportLinkedList[numVertices];
    for(int i = 0; i < numVertices; i++){
        adjList[i].setHead(0); //set all linkedlists to NULL 
    }
}

// Return total cost of operations for MST 
int Graph::getTotalCost(){
    int total = 0;
    for(int i =0; i < numVertices; i++)
        total += adjList[i].getCost();
    return total / 2; // every edge appears twice, double counting so div by 2
}

// Add two way edges since it's an undirected graph
void Graph::addEdge(int src, int dst, int duration) {

    bool srcTest = adjList[src].insertAirport(src, dst, duration);
    bool dstTest = adjList[dst].insertAirport(dst, src, duration);

    if(srcTest && dstTest){
        cout << "\nInserted a new flight between " << src << " and " << dst << endl;
        cout << "\tNumber of flights from " << src << " is " << adjList[src].getFlightCount() << endl;
    }
    else{
        cout << "There is already a path between " << src << " and " << dst << endl;
    }
}

void Graph::listFlights(int u){
    adjList[u].printAirports();
}

int Graph::findSmallestWeight(int *weight, int *vertexSet) {
    int smallest = INF;
    int index = -1;
    for(int i = 0; i < numVertices; i++){
        if(weight[i] < smallest && vertexSet[i] == -1){
            smallest = weight[i];
            index = i;
        }
    }
    return index;
}

// Dijkstra's Algorithm Implementation
void Graph::shortestPath(int src, int dst) {
    int weight[numVertices];
    int vertexSet[numVertices];
    int predecessor[numVertices];
    for(int i = 0; i < numVertices; i++){
        vertexSet[i] = -1; // -1 means not visited
        predecessor[i] = -1; // -1 means there is not a direct connection between source and vertex i
        weight[i] = INF; //inaccessible nodes have INF cost
    }
    // Step 1: Construct the weight array
    // O(|V|) worst case when source has edges to every vertex
    Airport *srcAirport = adjList[src].getHead();
    while(srcAirport != 0){
        weight[srcAirport->getID()] = srcAirport->getDuration();
        srcAirport = srcAirport->next;
    }
    vertexSet[src] = src; // only src in the vertexSet
    // Step 2: 
    // Outer loop is O(|V|) where |V| is number of vertices
    for(int step = 1; step < numVertices; step++){
        int v = findSmallestWeight(weight, vertexSet); // O(|V|) to find smallest weight
        vertexSet[v] = v; // add v to the vertexset
        Airport *uAirport = adjList[v].getHead(); // search for all vertices u adjacent to v
        // O(|V|) in the worst case when there is edges to every vertex
        while(uAirport != 0){
            if(weight[uAirport->getID()] > weight[v] + uAirport->getDuration()){
                weight[uAirport->getID()] = weight[v] + uAirport->getDuration(); // update weight
                predecessor[uAirport->getID()] = v; // to indicate a path from v to u
            }
            uAirport = uAirport->next;
        }
    }
    // Check if every vertex is in the vertexSet, i.e. visited.
    for(int i =0;i<numVertices; i++){
        if(vertexSet[i] == -1){
            cout << "No paths between " << src <<  " and " << dst << endl;
            return;
        }
    }
    /* Print the path */ 
    cout << "The shortest path from " << src <<  " to " << dst << endl;
    int dstCopy = dst;  
    int stack[numVertices]; // to reverse the path 
    for(int i = 0; i < numVertices; i++) {stack[i] = -1;}

    int count = 1;
    while(predecessor[dstCopy] != -1){
        stack[count] = predecessor[dstCopy]; // get destinations predecessor, save it to stack
        dstCopy = predecessor[dstCopy]; // update predecessor
        count++;
    }
    stack[0] = dst; stack[count] = src;
    // stack : [dst, dst n -1, dst n - 2 , ... ,dst 1, src ]
    // Print starting from the last occupied index
    for(int i = count; i > 0 ; i--){
        int takeoff = stack[i]; 
        int landing = stack[i-1];
        cout << "\t" << takeoff << " to " << landing << " with a duration " << adjList[takeoff].getDurationBetween(landing) << endl;
    }
    cout << "\tTotal flight duration of path: " << weight[dst] << endl;
}



// Prim's Algorithm Implementation
Graph Graph::minimizeCost(){
    int prevCost = this->getTotalCost();
    cout << "\nCreating and inserting new edges to Minimum Spanning Tree.." << endl;
    Graph MST = Graph(numVertices);

    int visited[numVertices];
    int mst[numVertices];
    for(int i = 0; i < numVertices; i++){
        visited[i] = -1; // -1 means not visited
        mst[i] = -1; // -1 means not vertex i is not in the MST yet
    }

    int V = 0; // start from vertex 0, works with other start vertices as well.
    int mstCount = 0; // number of vertices in the MST so far
    visited[V] = V; // set as visited 
    mst[mstCount] = V; // put inital vertex in the MST
    mstCount++; 
    
    // assuming a connected graph, traverse until MST's vertice no != original vertice no
    // Total Runtime = O(|V|^3/2 ) = O(|V|^3)
    // Outer loop is O(|V|)
    while(mstCount != numVertices){
        int to, from, leastDuration = INF;
        // Runs (V+1)/2 times on average -> (1+2+3+...+V) / V = (V+1) /2 -> O((V+1)/2) = O(V) 
        for(int i = 0; i < mstCount; i++){ // traverse vertices added to mst
            Airport *v = adjList[mst[i]].getHead()->next; // duration to itself 0, start with the next
            // traverse and find the shortest duration in the discovered part of mst
            // Worst case O(V), a vertex can have edges to every other vertex
            while(v != 0){
                if (v -> getDuration() < leastDuration && visited[v->getID()] == -1){
                    leastDuration = v -> getDuration();
                    from = mst[i];
                    to = v->getID();
                }
                v = v -> next;
            }
        }

        MST.addEdge(from, to, leastDuration);
        visited[to] = to; // mark the vertex visited 
        mst[mstCount] = to; // add vertice to mst
        mstCount++; // increment the number of vertices in mst
    } 
    cout << "\nFinished adding edges to the Minimum Spanning Tree..." << endl;
    cout << "\nTotal cost of the operations before minimization : " << prevCost << endl;
    cout << "Total cost of the operations after minimization : " << MST.getTotalCost() << endl;

    return MST; //return the newly created MST
}

