#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;
bool dp[1001][1001];

bool inter(string word1, string word2, string merge, ofstream& outFile ){
    if(word1.length() + word2.length() != merge.length()){
       // cout << "*** NOT A MERGE ***" << endl; 
        outFile << "*** NOT A MERGE ***" << endl; 
        return false; 
    }
    ; 
    for(int i = 0; i < word1.length()+2; i++){
        for(int j = 0; j < word2.length()+2; j++){
        dp[i][j] = false;
        }
    }
    dp[word1.length()][word2.length()] = true; 
//dynamic programing 
    for(int i = word1.length(); i > -1 ; i--){
        for(int j = word2.length(); j > -1 ; j--){
            if (i < word1.length() && (word1.at(i) == merge.at(i + j)) && dp[i+1][j]){
                //cout << word1.set(4)
                if(!dp[i][j]){
                //cout << "letter at "<< i << "is " << (char) toupper(word1.at(i)) << endl;
                }
                dp[i][j] = true;
            }
            if (j < word2.length() && (word2.at(j) == merge.at(i + j)) && dp[i][j+1]){
                dp[i][j] = true;
            }
        }
    }
      //if merge get word with proper capitalization
    if (dp[0][0]) {
        int tempX = 0;
        int tempY = 0;
        string str = "";
        while (tempX != word2.length() || tempY != word1.length()) {
            //cout << tempX + ", " + tempY << endl;
            if (dp[tempY+1][tempX] == 1) { //s/t below
                //cout << "here";
                str += char(toupper(word1.at(tempY)));
                tempY += 1;
            } else { //nothing below or bottom row
                //cout << "here1";
                str += char(word2.at(tempX));
                tempX += 1;
            }  
        }
        outFile << str << endl;
       // cout << str << endl;
    }
    else{
        outFile << "*** NOT A MERGE ***" << endl; 
       // cout << "*** NOT A MERGE ***" << endl; 
    }
    
    
     //test data
    // cout << "##################################################" <<endl;
    // for(int i = 0; i < word1.length()+1; i++){
    //     for(int j = 0; j < word2.length()+1; j++){
    //         cout << dp[i][j] << "|";
    //     }
    //     cout << "|" <<endl;
    // }
    // cout << "##################################################" <<endl;

    return dp[0][0];
}
int main(){

    //ask the user to enter the name of file to specify the graph
    cout << "Please enter the name of the input file: ";
    string inFileName;
    cin >> inFileName; 
    cout << "Enter the name of the output file: ";
    string outFileName;
    cin >> outFileName;
    //open fileName
    ifstream inFile(inFileName);
    if(!inFile){
        cout << "Error: file not found" << endl;
        return 1;
    }

    //loop through the file and add edges to the graph
    // look at three lines at a time 
    string word1;
    string word2;
    string merge; 
    ofstream outFile(outFileName);
    while(1){
        getline(inFile, word1);
        bool word1True = inFile.eof();
        if(word1True) break;
        //cout << word1 << endl; 
        getline(inFile, word2);
        bool word2True = inFile.eof();
        if(word2True) break;
        //cout << word2  << endl; 
        getline(inFile, merge);
        bool word3True = inFile.eof();
        if(word3True) break;
        //cout << word1 + ',' + word2 + ',' + merge << endl; 
        //cout << "first three done" << endl; 
        if((!word1True||!word2True||!word3True)){
            if(inter(word1, word2, merge, outFile)){
                //cout << "IT IS  MERGE" << endl;
                //outFile << "\n";
            }else{
                // outFile << "*** NOT A MERGE ***" << endl; 
                //outFile << "\n";
            }
            word1 = word2 = merge = "";
        }
        else {
            break;
        }
    }
    return 0;
}