//
//  main.cpp
//  PC
//
//  Created by KJ O'Brien on 11/21/22.
//
// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include "Formatter.cpp"
using namespace std;

int main () {
    string line;
    ifstream input("/Users/kjobrien/Documents/repos/PC/input.txt");
    ofstream outputFile("/Users/kjobrien/Documents/repos/PC/output.cpp");
    
    Formatter formatter;

    if(input.is_open()){
        
        while(getline(input, line)){
            formatter.addLine(line);
        }
        outputFile << formatter.returnOutput();
        outputFile.close();
        input.close();
    }else {
        cout << "Unable to open file";
    }
  return 0;
}
