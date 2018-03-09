/*
*
* @Author
* Student Name: Emre KÖSE
* Student ID: 150130037
* Date: 25.12.2016
*
*/
#ifndef interpreter_h
#define interpreter_h

#include "data_structures.h"
#include "calculator.h"
using namespace std;

struct Interpreter{
    Stack *S;   // used for prefix-postfix conversion and postfix evaluation
    Queue *Q;   // used for storing answers
    Calculator *C;  // used for mathematical operations

    void initialize();
    void prompt();  // user input is enabled
    void readFile(string& file_name);   // read from file
    string prefixToPostfix(string& prefix, bool& flag);     // prefix-postfix conversion
    long int evaluate(string& postfix, bool& flag);         // postfix evaulation
    void close();
};
#endif /* interpreter_h */
