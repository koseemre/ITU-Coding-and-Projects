/*
*
* @Author
* Student Name: Emre KÖSE
* Student ID: 150130037
* Date: 25.12.2016
*
*  Compile: g++ main.cpp calc_operations.cpp data_operations.cpp interpreter_operations.cpp -o hw3
*  Run with prompt: ./hw3
*  Run with file:  ./hw3 <file name>
*/

#include <iostream>
#include "interpreter.h"
using namespace std;

int main(int argc, const char * argv[]) {
    Interpreter* I = new Interpreter;
    if(argc == 1){      // prompt mode
        I->prompt();
    }
    else if (argc == 2){        // batch mode
        string file_name = argv[1];
        I->readFile(file_name);
    }
    else{       // too many command line arguments
        cout<<"See main.cpp file for run commands."<<endl;
        delete I;
        return 0;
    }
    I->close();
    delete I;
    return 0;
}
