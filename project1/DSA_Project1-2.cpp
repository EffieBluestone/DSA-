/*Effie, The code below take in input from an input file that has a class tyep and person name. 
The code uses polyphorphism to create a hierarchical structure of classes so that the two sub classes inherit from the master class. 
A vector of pointers to Foobar objects were creatd as the data input was read. 
Each line of input is read into the code and is interpreted for its type and name and given a position. The first input taken is the last spot in line. 
The resulting output craetes an output file that displays the name of the object and its strentgh based on it type and position in proper the noatation. 
*/
#include <iostream>
#include <string>
#include<fstream>
#include<vector>
using namespace std;

class FooBar // master class
{
private:
	string name;
 	int position;
protected: 
	int GetPosition(){
		return position;
	}
public:
    //constructer 
	FooBar(string n, int p){
		name = n;
		position = p;
	}
	void SetName(string name){
		this->name = name;
	}
	void SetPosition(int p){
		position = p;
	}
	string GetName() 
	{
		return name;
	}
	virtual int GetStrength(){
		return position;
	}
};

class Foo : public FooBar 
{
public:
    //constructer 
	Foo(string name, int position): FooBar(name, position){
	}
	virtual int GetStrength(){
		return (GetPosition()*3);
	}
};		

class Bar : public FooBar 
{
public:
    //constructer 
	Bar(string name, int position): FooBar(name, position){
	}
	virtual int GetStrength(){
		return (GetPosition()+15);
	}
};

class Handeler { 
    public: 
        vector <FooBar*> myvector;
        string line,name,theClass; //declarations
        string fileIn; // inputfile name
        string fileOut; //output shud be a file
    
        void GetFiles(){ // code to get the file names 
            cout << "Enter the name of the input file: ";
            cin >> fileIn; 
            cout << "Enter the name of the output file: ";
            cin >> fileOut;  

        }
        // will read through the file and create the respective classes  
        void readFiles(){ 
            ifstream infile; 
	        infile.open(fileIn); 
            while(getline(infile,line)){
                theClass = line.substr(0,line.find(' '));
                name = line.substr(line.find(' ')+1,line.find('\n'));
                    if ((theClass)=="foobar"){
                        FooBar *p = new FooBar(name, 0); 
                        myvector.push_back(p);
                    }
                     if ((theClass)=="foo"){
                        FooBar *p = new Foo(name, 0); 
                        myvector.push_back(p);
                    }
                    if ((theClass)=="bar"){
                        FooBar *p = new Bar(name, 0); 
                        myvector.push_back(p);
                    }
            }
            infile.close();
        }
        //keep track of all the positions 
        void posTracker(){
            //POSITION TRACKER
            int pos = 1; 
            for(int i = myvector.size() - 1; i >= 0; i--){
                myvector[i]->SetPosition(pos);
                pos++;
            }
        }
        // creates the output file
        void outPutFiles(){
            ofstream outfile(fileOut);
            for(int i = 0; i < myvector.size(); i++){ 
                outfile << myvector[i]->GetName() << " " << myvector[i]->GetStrength() << "\n";
            }
        }
};

int main()
{
    Handeler handle = Handeler(); // create instance of handler class
    handle.GetFiles(); //get the files 
    handle.readFiles(); //reads the files 
    handle.posTracker(); // tracks the position 
    handle.outPutFiles(); // outputs the data into a file
}