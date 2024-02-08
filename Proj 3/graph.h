#include <iostream>
#include <vector>
#include <list>
#include "heap.h" 

class graph{

    public: 
         //constuctor
         graph(int numVer);

         void insertVertex(const std::string &id1, const std::string &id2, int w);

        //shortest path from start to all other vertices use Dijkstra algorithm 
        // starting vertex not found return -1
         int Dijkstra(const std::string &start);

        //write the shortest path from start to end to the output stream
        //if the path known returns(vertex name,path distance and full path)
        //else return vertex name and "no path"
         void printGraph(std::string outFileName);

        //true if in, else return false 
         bool inGraph(const std::string &id);

        //table states 
         void printTable();

    private:

    class node;

        class edge{
            public:
            node* destination;
            int weight;
        };

        //Private Node Class
    class node{
        public:
        std::list<edge> edges;
        std::string name; 
        std::string path; 
        int dist = 5000000;
        bool known = false;
        
    };
        std::list<node> nodes;
        int vertices = 0;
        hashTable hTable; 

};

//table is hTable