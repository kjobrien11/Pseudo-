//
//  Formatter.cpp
//  PC
//
//  Created by KJ O'Brien on 11/21/22.
//
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Formatter{
    const string HEADER = "#include <iostream>\n#include <string>\nusing namespace std;\n int main () {\n";
    const string FOOTER = "return 0;\n}\n";
    const string INDENT = "    ";
    string output = HEADER;
    string currentIndent = INDENT;
    bool loopFlag = false;
    
    
    
    string getCurrentIndent(){
        return currentIndent;
    }
    void increaseIndent(){
        currentIndent = currentIndent + INDENT;
    }
    
    void decreaseIndent(){
        currentIndent = currentIndent.substr(0, currentIndent.length()-4);
    }
    string handleRand(string line){
        
        unsigned long space = line.find(" ");
        unsigned long firstComma = line.find(",");
        unsigned long secondComma = line.find(",", firstComma+1);


        string x = "int " + line.substr(space+1, firstComma-space-1) + " = " + "rand() % ";
        string z = line.substr(secondComma+1, secondComma);
        string y = line.substr(firstComma+1, secondComma-firstComma-1);
        return x + z + + " + "+ y +";\n";
    }
    string handleNewLine(){
        return "}\n\n";
    }
    string handleString(string line){
        return "string " + line +";\n";
    }
    string handleBool(string line){
        return "bool " + line +";\n";
    }
    string handleDouble(string line){
        return "double " + line +";\n";
    }
    string handleFor(string line){
        loopFlag = true;
        unsigned long space = line.find(" ");
        unsigned long firstComma = line.find(",");
        unsigned long secondComma = line.find(",", firstComma+1);
        unsigned long thirdComma = line.find(",", secondComma+1);
        string ret = "for(int "+ line.substr(space+1, firstComma-space-1) + " = "  +line.substr(firstComma+1, secondComma-firstComma-1) +"; "+ line.substr(space+1, firstComma-space-1)+ line.substr(secondComma+1, thirdComma-secondComma-1)+ line.substr(thirdComma+1, secondComma)+ "; " + line.substr(space+1, firstComma-space-1) + "++){\n";
        return ret;
    }
    string handleWhile(string line){
        loopFlag = true;
        unsigned long space = line.find(" ");
        unsigned long firstComma = line.find(",");
        unsigned long secondComma = line.find(",", firstComma+1);
        unsigned long thirdComma = line.find(",", secondComma+1);
        string ret = "int " + line.substr(space+1, firstComma-space-1) + " = " +line.substr(firstComma+1, secondComma-firstComma-1) + ";\n";
        ret += getCurrentIndent() + "while("+ line.substr(space+1, firstComma-space-1) + line.substr(secondComma+1, thirdComma-secondComma-1)+ line.substr(thirdComma+1) + "){\n";
        return ret;
    }
    bool isInt(string line, int secondSpace, int thirdSpace){
        try {
            int test = stoi(line.substr(secondSpace+1, thirdSpace));
            return true;
        }
        catch (const std::invalid_argument & e) {
                    std::cout << e.what() << "\n";
            return false;
        }
    }
    string handleInt(string line, int secondSpace, int thirdSpace){
        return "int " + line +";\n";

    }
    string handlePrint(string line){
        unsigned long printStart = line.find("(");
        unsigned long printEnd = line.find(")");
        return "cout << " + line.substr(printStart +1,printEnd-1-printStart);
    }
    string handlePrintNoNewLine(string line){
        return handlePrint(line) + ";\n";
        
    }
    string handlePrintNewLine(string line){
        return handlePrint(line) + " << endl;\n";
    }
    string handleInput(string line){
        int firstSpace = (int)line.find(" ");
        string h = "int" + line.substr(firstSpace) + ";\n";
        return h + getCurrentIndent() +  "cin >>" + line.substr(firstSpace) + ";\n";
    }
    string handleIf(string line){
        loopFlag = true;
        int firstSpace = (int)line.find(" ");
        return "if" + line.substr(firstSpace) + "{\n";
    }
    
    string parseLine(string line){
        
        int firstSpace = (int)line.find(" ");
        int secondSpace = (int)line.find(" ", firstSpace+1);
        int thirdSpace = (int)line.find(" ", secondSpace+1);
        
        if (line.substr(0, 6) == "printn"){
            return handlePrintNewLine(line);
        }else if (line.substr(0, 2) == "if"){
            return handleIf(line);
        }else if (line.substr(0, 5) == "input"){
            return handleInput(line);
        }else if(line.substr(secondSpace+1, thirdSpace) == "false" || line.substr(secondSpace+1, thirdSpace) == "true"){
            return handleBool(line);
        }else if(line.substr(secondSpace+1, thirdSpace).find(".") != std::string::npos){
            return handleDouble(line);
        }else if(line.substr(secondSpace+1, thirdSpace) == "for"){
            return handleFor(line);
        }else if(line.substr(0, 5) == "print"){
            return handlePrintNoNewLine(line);
        }else if (isInt(line, secondSpace, thirdSpace)){
            return handleInt(line, secondSpace, thirdSpace);
        }else if (line.substr(secondSpace+1, thirdSpace) == "while"){
            return handleWhile(line);
        }else if(line.substr(secondSpace+1, 1) == "\""){
            return handleString(line);
        }else if(line.substr(0,4) == "rand"){
            return handleRand(line);
        }else if(line.substr(secondSpace+1, 1) == ""){
            decreaseIndent();
            return handleNewLine();
        }else{
            return line+";\n";
        }
    }

public:
    
    void addLine(string line){

        //remove leading indentation
        int index = 0;
        for(int i = 0; i < line.size(); i++){
            if(line.substr(i, 1) == " " || line.substr(i, 1) == "\t"){
            }else{
                index = i;
                break;
            }
        }
        string curLine = parseLine(line.substr(index));
        if(loopFlag){
            output = output +"\n";
            loopFlag = false;
            output = output + getCurrentIndent() + curLine;
            increaseIndent();
        }else{
            output = output + getCurrentIndent() + curLine;
        }
        
    }
    //returns final output to .cpp file
    string returnOutput(){
        return output + currentIndent + FOOTER;
    }
};
