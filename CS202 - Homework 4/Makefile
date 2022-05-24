CC=g++
CFLAGS=-Wall -Wextra -std=c++11

hw4: main.o Graph.o AirportLinkedList.o
	$(CC) $(CFLAGS) main.o Graph.o AirportLinkedList.o Airport.o -o hw4

main.o: main.cpp Graph.h
	$(CC) $(CFLAGS) -c main.cpp

Graph.o: Graph.h Graph.cpp AirportLinkedList.h 
	$(CC) $(CFLAGS) -c Graph.cpp

AirportLinkedList.o: AirportLinkedList.h AirportLinkedList.cpp Airport.o
	$(CC) $(CFLAGS) -c AirportLinkedList.cpp
	
Airport.o: Airport.cpp Airport.h
	$(CC) $(CFLAGS) -c Airport.cpp

clean:
	rm *.o hw4


