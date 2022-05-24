/*
 * Title: AirportLinkedList
 * Author: Alperen Can 
 * ID: 21601740
 * Section: 1
 * Assignment: 4
 * Description: Linked list implementation to be used in the adjacency list
*/
#include "AirportLinkedList.h"
#include <iostream>
using namespace std;

AirportLinkedList::AirportLinkedList() {
    head = 0;
    flightCount = 0;
    cost = 0;
}
Airport* AirportLinkedList::getHead(){
    return head;
}
int AirportLinkedList:: getDurationBetween(int dst){
    Airport *tmp = head;
     while(tmp != 0){
        if(tmp->id == dst){
            return tmp->duration;
        }
        tmp = tmp -> next;
    } 
    return -1;
}
int AirportLinkedList:: getCost(){
    return cost;
}

bool AirportLinkedList::insertAirport(int src, int dst, int duration) {
    if(head == 0){
        Airport *vertex = new Airport(src, dst, 0); // duration to itself is 0
        head = vertex;
    }

    Airport *destinationAirport = new Airport(dst, src, duration);

    Airport *tmp = head;
    while(tmp->next != 0){
        if(tmp -> id == dst) // if there is already edge between src -> dst
            return false;
        tmp = tmp -> next;
    }
    if(tmp->id == dst) {
        return false; // check duplicates
    }

    tmp -> next = destinationAirport;
    flightCount++;
    cost += destinationAirport->getDuration();
    return true;
}

void AirportLinkedList::printAirports() {
    Airport *temp = head -> next;
    cout << "List of flights from " << head -> id << endl;
    while (temp != 0){
        cout << "\t" << head -> id << " to " << temp->id << " with a duration of " << temp->duration << endl;
        temp = temp -> next;
    }
    cout << "\tThe number of flights is " << flightCount << endl;

}

int AirportLinkedList::getFlightCount() {
    return flightCount;
}

void AirportLinkedList::setHead(Airport *newHead) {
    this->head = newHead;
}

