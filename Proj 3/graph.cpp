#include "graph.h"
#include <iostream> 
#include <fstream>

// constructor 
graph::graph(int numVertices){
    hTable = hashTable(numVertices*2);
}

//Insert vertex into the graph 
void graph::insertVertex(const std::string &id1, const std::string &id2, int w){
    bool b1, b2;
    node *vertex1Location;
    //Check if Starting Vertex is in the graph
    if(!this->hTable.contains(id1)){
        //if not in create a new node
        node N; 
        N.name = id1;
        nodes.push_back(N);
        hTable.insert(id1, &(nodes.back()));
        vertex1Location = &(nodes.back());
        vertices++;
    }
    else{
        vertex1Location = static_cast<node*>(hTable.getPointer(id1,&b1));
    }
    node *vertex2Location;
    //Check if Ending Vertex is in the graph
    if(!this->hTable.contains(id2)){
    //Create a new node
        node N2; 
        N2.name = id2;
        nodes.push_back(N2);
        hTable.insert(id2, &(nodes.back()));
        vertex2Location = &(nodes.back());
        vertices++;
    }else{
        vertex2Location = static_cast<node*>(hTable.getPointer(id2,&b2));
    }

    //Create a new edge from start  v -> end v
    edge E;
    E.weight = w;
    E.destination = vertex2Location;
    vertex1Location->edges.push_back(E);
}
//true if in, else return false 
bool graph::inGraph(const std::string &id){
    return this->hTable.contains(id);
}
 //shortest path from start to all other vertices use Dijkstra algorithm 
 // starting vertex not found return -1
int graph::Dijkstra(const std::string &id){
 heap theHeap = heap(vertices);
    //Sets all vertices to known 
    // nodes - list<node>

	for (auto it = nodes.begin(); it != nodes.end(); it++)
	{
        if(it->name == id){
            it->dist = 0;
        }else{
            it->dist = 5000000;
        }

		theHeap.insert((*it).name, (*it).dist, &(*it));
	}


    //Get the start vertex
    bool b1;
    node *start = static_cast<node*>(hTable.getPointer(id,&b1));
    if(!b1){
        return -1;
    }
    theHeap.setKey(id,0);

    std::cout << "Intial Configuration" << std::endl;
    printTable();

    //the Min Heap
    while(1){
        std::string pID;
        int pkey;
        void* pNode;

        theHeap.deleteMin(&pID, &pkey, &pNode);
        node *smallDistanceNode = (graph::node*)pNode;
        if(smallDistanceNode->known){
            break;
        }
        smallDistanceNode->known = true;
        for(auto e = smallDistanceNode->edges.begin(); e !=  smallDistanceNode->edges.end(); e++){
            if(!(*e).destination->known){
                int newDist = smallDistanceNode->dist + e->weight;
                if(newDist < (*e).destination->dist){
                    (*e).destination->dist = newDist;
                    (*e).destination->path = smallDistanceNode->path + (smallDistanceNode->name + ", ");
                    theHeap.setKey((*e).destination->name, (*e).destination->dist);
                }
            }
        }
        
        std::cout << "After Evaluation of " << smallDistanceNode->name << std::endl;
        printTable();
        std::cout << std::endl;
    }
}
//write the shortest path from start to end to the output stream
//if the path known returns(vertex name,path distance and full path)
//else return vertex name and "no path"
void graph::printGraph(std::string outFileName){
std::ofstream outFile(outFileName);
    for(node n : nodes){
        if(n.dist < 1100000){
            outFile << n.name << ": " << std::to_string(n.dist) << " [" << n.path << n.name << "]" << std::endl;; 
        }else{
            outFile << n.name << ": NO PATH\n";
        }
    }
    outFile.close();
}

//list of table states 
void graph::printTable(){
    std::cout << "| V# | known | Distance | Path          |" << std::endl;
    for(auto item = nodes.begin(); item != nodes.end(); ++item){
        if(item->dist > 1100000){
            std::cout <<"| "<<  item->name << " | " << item->known << " | I | " << item->path << " |" << std::endl;
        }else{
            std::cout <<"| "<<  item->name << " | " << item->known << " | "<< item->dist << " | " << item->path << " |" << std::endl;
        }
    }
}