//spellcheck
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include "hash.h"

using namespace std;
// fucntion serves to divide up the string (line) into words that are allowed removing the nonvalids and return that string
vector<string> division(string str) {

    vector<string> division;
    string letters = "";
    bool includeNum = false;

    for (char c : str) {

        if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
		c == '-' || c == '\''))
            letters = letters + c; 

        else if (!isdigit(c)) {
                if (!includeNum && !letters.empty())
                    division.push_back(letters);
                letters.clear();
                includeNum = false;
            }
            if (isdigit(c))
                includeNum = true;
    }     
    return division;
}
// makes the word good, ensures that string getting returned is less than 20 char , contians no invalid char, and lowercase
string makeGood(string lnEd) {
    if (lnEd.length() > 20)
        return "";

    for (auto it = lnEd.begin(); it != lnEd.end(); ++it) {
        if(!isalnum(*it) && *it !='-' && *it != '\'')
            return "";
        else 
            *it = ::tolower(*it); 
    }

    return lnEd;
}
//gets the dcitionary words to add into the hashtable 
void readDic(ifstream& input, hashTable& dictionary) {
    if (input.is_open()) {
        string ln;
        while (getline(input, ln)) {
            string lineEdit = makeGood(ln);
            if (lineEdit.length() != 0)
                dictionary.insert(lineEdit);
        }
        input.close();
    }
}
//fucntion used to ensure that only valid char are in the string 
bool validChar(string lnEd) {
    int j = 0;
    while (lnEd[j]){
        if (lnEd[j] != '-' && lnEd[j] != '\'' && !isalpha(lnEd[j]) )
            return false;
        j++;
    }
    return true;
}
//checks the input list agaisnt the dictionary created and inform user of any errors that occur
void checker(string inputFile, string outputFile, hashTable & dictionary){
    ifstream input(inputFile);
    ofstream outFile;
    outFile.open(outputFile);
    int lineCnt = 1; 

    if (!input){
        cerr << "Error: could not open " << inputFile << "\n";
        exit(1);
    }

    if(input.is_open()){ 
        string ln; //represent the line
        unsigned int i = 0; 

        while(getline(input,ln)){  
            i++; 
            vector <string> lnEdit; 
            string holder = "";
            //applies the lowercase operation to every char in ln
            transform(ln.begin(), ln.end(), ln.begin(), [](char c){ return tolower(c); });
            lnEdit = division(ln + " ");
            //error messeges for words which should be invalid 
            for(auto & lnEd: lnEdit){ 
                if(validChar(lnEd)) {
                    if ( lnEd.length() > 20 )
                        outFile << "Long word at line " << i << ", starts: " << lnEd.substr(0,20) << '\n';
                    else { 
                        string good = makeGood(lnEd); 
                        bool has = dictionary.contains(good); 
                        if(!has && good.length() > 0)
                            outFile << "Unknown word at line " << i << ": " << good << '\n';
                    }
                    lineCnt++;
                }
            }
        }
    } 
    input.close();
}

int main () {
    auto dictionary = hashTable(1000);

    ifstream dictfile;
    string dictname;
    string inFile;
    string outFile;

    cout << "Enter name of dictionary: ";
    cin >> dictname;
    dictfile.open(dictname);
    clock_t t1 = clock();
    readDic(dictfile, dictionary) ;
    clock_t t2 = clock();
    unsigned long time = t2 - t1; 
    cout << "Total time (in seconds) to load dictionary: " << (time / CLOCKS_PER_SEC) << '\n';

    cout << "Enter name of input file: ";
    cin >> inFile;
    cout << "Enter name of output file: ";
    cin >> outFile;
    clock_t t3 = clock();
    checker(inFile, outFile, dictionary); 
    clock_t t4 = clock();
    unsigned long time1 = t4 - t3 ; 
    cout << "Total time (in seconds) to check document: " << (time1 / CLOCKS_PER_SEC) << '\n';
    return 0;
}
