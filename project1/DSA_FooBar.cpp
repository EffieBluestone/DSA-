#include <iostream>
#include <string>
#include<fstream>
#include<vector>
using namespace std;
int count = 1; 
//vector <*FooBar> myvector; //declare in main 	vector of pointers to foobar 
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
	FooBar(string n, int p){
		name = n;
		position = p;
	}
	void SetName(string name)
	{
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
	Foo(string name, int position): FooBar(name, position){

	}
	virtual int GetStrength() 
	{
		return (GetPosition()*3);
	}
};		
class Bar : public FooBar 
{
public:
	Bar(string name, int position): FooBar(name, position){
	}
	virtual int GetStrength() 
	{
		return (GetPosition()+15);
	}
};




int main()
{
    vector <FooBar*> myvector;
    string fileIn; 
    cout << "Enter the name of the input file: ";
    cin >> fileIn; 
    string fileOut; //output shud be a file
    cout << "Enter the name of the output file: ";
    cin >> fileOut;  

	ifstream infile; 
	infile.open(fileIn); 
    ofstream outfile(fileOut);
    
    string line;
    string name; 
    string theClass;
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
    //POSITION TRACKER
    int pos = 1; 
    for(int i = myvector.size() - 1; i >= 0; i--){
        myvector[i]->SetPosition(pos);
        pos++;
    
    }
    //output file creation      After run that file will just be there
    for(int i = 0; i < myvector.size(); i++){ 
        outfile << myvector[i]->GetName() << " " << myvector[i]->GetStrength() << "\n";
    }
}