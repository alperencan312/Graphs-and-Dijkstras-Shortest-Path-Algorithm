/*
 * Title: AirportLinkedList
 * Author: Alperen Can 
 * ID: 21601740
 * Section: 1
 * Assignment: 4
 * Description: Linked list header file to be used in the adjacency list
*/
#include "Airport.h"

class AirportLinkedList {
private:
    Airport *head;
    int flightCount;
    int cost;
public:
    AirportLinkedList();
    bool insertAirport(int src, int dst, int duration);
    void printAirports();
    int getFlightCount();
    int getDurationBetween(int dst);
    Airport* getHead();
    void setHead(Airport *newHead);
    int getCost();
};


