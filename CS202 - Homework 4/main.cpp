/*
 * Title: Main
 * Author: Alperen Can 
 * ID: 21601740
 * Section: 1
 * Assignment: 4
 * Description: Main.cpp input file is read and according to the file methods are called on the Graph object.
*/
#include "Graph.h"
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {   
    if(argc < 2){
        cout << "Usage: ./hw4 fileName.txt" << endl;
        exit(0);
    }
    int vertices, commands;
    string line;
    ifstream commandFile(argv[1]); //file name is coming from argv
    // read first two lines seperately for vertices and no of commands
    getline(commandFile, line);
    vertices = stoi(line);

    getline(commandFile, line);
    commands = stoi(line);
    Graph airportHub = Graph(vertices);

    for (int i = 0; i < commands; i++){
        getline(commandFile, line);
        if(line[0] == 'I'){
           int src = stoi(line.substr(2,1));
           int dst = stoi(line.substr(4,1));
           int duration = stoi(line.substr(6,1));
           airportHub.addEdge(src, dst, duration); 
        }
        else if(line[0] == 'S'){
           int src = stoi(line.substr(2,1));
           int dst = stoi(line.substr(4,1));
           airportHub.shortestPath(src, dst); 
        }
        else if(line[0] == 'L'){
            int u = stoi(line.substr(2,1));
            airportHub.listFlights(u);
        }
        else if(line[0] == 'M'){
            airportHub = airportHub.minimizeCost(); // return and assign the MST to airportHub
        }
    }
}
