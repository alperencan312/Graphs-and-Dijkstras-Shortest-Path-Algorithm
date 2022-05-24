/*
 * Title: Airport 
 * Author: Alperen Can 
 * ID: 21601740
 * Section: 1
 * Assignment: 4
 * Description: Airport node class used for linked list in the adjacency list implementation of graph
*/
#define INF 99999

class Airport {
private:
    int id;
    int dst;
    int duration;
    Airport *next;
public:
    Airport(int id, int dst, int duration);   
    int getDuration();
    int getID();
   
    friend class AirportLinkedList;
    friend class Graph;
};