#include <iostream>
#include <string>
#include<fstream>
#include<vector>
using namespace std;

template <typename Data>
class SimpleList{
    
    class Node{
        private: 
            Data data; //
            Node* nextNode; 

        public: 
        Node(Data myInfo, Node* nextAddress){
            data = myInfo; 
            nextNode = nextAddress; 
        }
        Node(Data myInfo){
            data = myInfo; 
            nextNode= NULL;
        }
        void setnextNode(Node* newNode){
            nextNode = newNode; 
        }
        Data getData(){
            return data;
        }
        Node* getnextNode(){
            return nextNode; 
        }
    };

    private:
	    string name;
        Node* start;
        Node* end; 
    protected: 
        
    public:
    SimpleList(string n){
        end = NULL;
        start = NULL;
        name = n; 
    }
    void addNodeToStart(Data dataValue){
        Node *newNode = new Node(dataValue);
        if( end == NULL){
            end = newNode;
        }
        Node *temp = start; 
        start = newNode; 
        newNode->setnextNode(temp);
    }
    Data removeFromStart(){
        Node* temp = start->getnextNode();
        Data val = start->getData(); 
        //add delete start here
        start = temp; 
        return val;
    }
    void addNodeToEnd(Data dataValue){
        Node *newNode = new Node(dataValue);
        if(end == NULL){
            addNodeToStart(dataValue);
        } else {
            end->setnextNode(newNode);
            end = newNode; 
        }
    }

    void printStartEnd() {
        cout << start->getData()<< endl;
        cout << end->getData()<< endl;
    }
    string getName() {
		return name;
	}
};

template <typename Data>
class Stack : public SimpleList <Data>
{
    public: 
        void push(Data dataValue){
            return this-> addNodeToStart( dataValue);
        }
        Data pop(){
            return this-> removeFromStart();
        }

};

template <typename Data>
class Queue: public SimpleList <Data>{
    public: 
        void push(Data dataValue){
            return this-> addNodeToEnd(dataValue);
        }
        Data pop() {
            return this->removeFromStart();
        }
    };


void getFiles(){ // code to get the file names 
            string fileIn, fileOut;
            cout << "Enter the name of the input file: ";
            cin >> fileIn; 
            cout << "Enter the name of the output file: ";
            cin >> fileOut;  
            ifstream infile; 
	        
        }
    /*
void outPutFiles(){
        ofstream outfile(fileOut);
            
        }
    }*/
int main(){
    list<SimpleList<int> *> ListSLi;
    list<SimpleList<int> *> ListSLd;
    list<SimpleList<int> *> ListSLs; 

    //read files 

    // parse the file 
    void parse(){
    string line;
    while(getline(fileIn,line)){
        outputF << "PROCESSING COMMAND: " << line << '\n';
        auto words = this->split(line, ' ');
        if(words[0] == "create"){
            this->create(words[1],words[2]);
        }else if (words[0] == "push"){
            this->push(words[1],words[2]);
        }else if (words[0] == "pop"){
            this->pop(words[1]);
        }
    }
}
bool exist(string name) {
    if (name[0] == 'i'){
        //ints here
        if (  ){ //If find returns the end then it is not in the list
            return false;
        } else{
            return true;
        }
    //doubles here
    }else if (name[0] == 'd'){
        if ( ){
            return false;
        } else{
            return true;
        }

    }else if (name[0] == 's'){
    //strings here
        if (){
            return false;
        } else{
            return true;
        }
    }
}
    void create(string name, string type ){
        if(this->exist(name)){
            cout << "ERROR: This name already exists!" << "\n";
        return;
        }
    }
    void push(string name, string add){
       if(this->exist(name)){
           if( )
            
        }
        else(){
            cout << "ERROR: This name does not exist!" << "\n";
        }
    }

    void pop(string name){
        if(this->exist(name)){
            
        }
        else(){
            cout << "ERROR: This name does not exist!" << "\n";
        }
       
    }
};