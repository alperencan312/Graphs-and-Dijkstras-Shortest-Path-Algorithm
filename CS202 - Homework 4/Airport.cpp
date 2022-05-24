/*
 * Title: Airport 
 * Author: Alperen Can 
 * ID: 21601740
 * Section: 1
 * Assignment: 4
 * Description: Airport node class used for linked list in the adjacency list implementation of graph
*/
#include "Airport.h"

Airport::Airport(int id, int dst, int duration){
       this->id = id;
       this->dst = dst;
       this -> duration = duration;
       this->next = 0;
}

int Airport::getDuration(){
   return duration;
}
int Airport:: getID(){
    return id;
}