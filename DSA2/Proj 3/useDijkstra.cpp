#include "graph.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
using namespace std;
int main(){
    //ask the user to enter the name of file to specify the graph
    cout << "Please enter the name of the file specifying the graph: ";
    string inFileName;
    cin >> inFileName;

    //open fileName
    ifstream inFile(inFileName);
    if(!inFile){
        cout << "Error: file not found" << endl;
        return 1;
    }

    graph theGraph = graph(500);
    
    //loop through the file and add edges to the graph
    string line;
    while(getline(inFile, line)){
        stringstream ss(line);
        string from;
        string to;
        string weight;
        getline(ss, from, ' ');
        getline(ss, to, ' ');
        getline(ss, weight);
        theGraph.insertVertex(from, to, std::stoi(weight));
    }
    string start;

    while(1){
        //prompt user for starting index
        cout << "Enter the starting index: ";
        cin >> start;

        //quick check if index chosen is in the graph
        if(!theGraph.inGraph(start)){
            cout << "\n Error: starting index not found" << endl;
        }else{
            break;
        }
    }

    //get the time
    auto start_t = chrono::high_resolution_clock::now();
    theGraph.Dijkstra(start);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start_t;
    cout << "Total time (in seconds) for Dijkstra's Algorithm : " << elapsed.count() << " s" << endl;

    //ask the user for output file name
    cout << "Enter the name of the output file: ";
    string outFileName;
    cin >> outFileName;

    //open output file
    theGraph.printGraph(outFileName);
    return 0;
}