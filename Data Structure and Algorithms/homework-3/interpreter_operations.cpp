/*
*
* @Author
* Student Name: Emre KÖSE
* Student ID: 150130037
* Date: 25.12.2016
*
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <string>
#include <cstdlib>

#include "data_structures.h"
#include "calculator.h"
#include "interpreter.h"

using namespace std;

void Interpreter::initialize(){
    S = new Stack;
    Q = new Queue;
    C = new Calculator;
    S->create();
    Q->create();
    C->flag = true;
}
void Interpreter::close(){
    S->close();
    Q->close();
    delete S;
    delete Q;
    delete C;
}
void Interpreter::readFile(string &file_name){
    initialize();
    bool flag = true;   // used to notify syntax errors
    string prefix,postfix;
    long int answer;
    ifstream read(file_name.c_str());
    if(!read){      // wrong file path
        cout<<"File does not exist."<<endl;
        exit(0);
    }
    while(std::getline(read,prefix)){   // read line by line
        flag = true;
        cin.clear();    // clean buffer
        postfix = prefixToPostfix(prefix,flag);
        if(!flag){      // check for error
            S->close();
            cout<<endl<<"Syntax error."<<endl;
            continue;
        }
        answer = evaluate(postfix,flag);
        if(!flag){      // check for error
            S->close();
            cout<<endl<<"Calculation error."<<endl;
            continue;
        }
    }
    Q->printAll();  // print all answers
    return;
}
void Interpreter::prompt(){
    cout<< "Initializing the interpreter..."<<endl;
    initialize();
    string prefix, postfix;
    bool flag = true;
    long int answer;
    cout<<endl<<">> ";
    getline(cin,prefix);    // get prefix expression from user input
    while(prefix != "exit"){
        flag = true;
        postfix = prefixToPostfix(prefix,flag);
        if(!flag){      // check for error
            S->close();
            cout<<endl<<"Syntax error."<<endl;
            cout<<endl<<">> ";
            getline(cin,prefix);
            continue;
        }
        answer = evaluate(postfix,flag);
        if(!flag){      // check for error
            S->close();
            cout<<endl<<"Calculation error."<<endl;
            cout<<endl<<">> ";
            getline(cin,prefix);
            continue;
        }
        cout<<endl<<"Postfix string: "<<postfix<<endl;      // print postfix expression
        cout<<"Answer: ";                                   // print answer
        if(answer == LONG_MAX){     // print as inf
            cout<<"inf"<<endl;
        }
        else if(answer == LONG_MIN){    // print as -inf
            cout<<"-inf"<<endl;
        }
        else{
            cout<<answer<<endl;
        }
        cout<<endl<<">> ";
        getline(cin,prefix);            // get a new prefix expression from user input
    }
    cout<<endl<<endl<<"Terminating interpreter..."<<endl;
    Q->printAll();      // print all answers
}

long int Interpreter::evaluate(string &postfix, bool& flag){ // flag is for syntax errors
    string word;
    bool isOperand;         // true if operand
    long int answer = -1;
    long int *operandList = NULL,*tempList = NULL;
    istringstream iss(postfix);
    while(iss >> word){     // read postfix from left to right
        isOperand = true;
        if(word == "("){        // push opening parenthesis
            S->push(0, '(');
            continue;
        }
        if(word == "inf" || word == "-inf" ||  (!Q->isempty() && word == "ans")){   // special operands
            isOperand = true;
        }
        else{
            for(int i = 0; i < word.length(); i++){         // check if it is a number
                if(((word[i] > 57 || word[i] < 48)) && word[i] != 45){  // check according to ASCII
                    isOperand = false;
                }
            }
        }
        if(isOperand){      // is operand
            long int operand;
            if(word == "inf"){
                operand = LONG_MAX;
            }
            else if(word == "-inf"){
                operand = LONG_MIN;
            }
            else if(!Q->isempty() && word == "ans"){    // if not first evaulation
                operand = Q->back->value;               // ans is taken from Queue (not dequeued)
            }
            else{
                operand = atol(word.c_str());           // string to long int
            }
            S->push(operand, ' ');                      // push operand into stack
            continue;
        }
        else{               // is not operand
            int operandCount = C->getOperandCount(word);
            int count = 0;
            if(operandCount != -1){    // check if it is a defined operator
                while(!S->isempty()){   // till stack is empty
                    operand temp = S->pop();
                    if(operandCount == 1 && count > 1){          // if no bracket take max 1 argument (abs and sqrt)
                        if(temp.bracket != '('){    // if not bracket push back to stack
                            S->push(temp.value, temp.bracket);
                        }
                        break;
                    }
                    else if(operandCount == 2 && count > 2){    // if no bracket take max 2 arguments (div and sub)
                        if(temp.bracket != '('){    // if not bracket push back to stack
                            S->push(temp.value, temp.bracket);
                        }
                        break;
                    }
                    else if(operandCount == 3 && count > 2){    // if no bracket take max 2 argument (mod exp and log)
                        if(temp.bracket != '('){    // if not bracket push back to stack
                            S->push(temp.value, temp.bracket);
                        }
                        break;
                    }
                    if(temp.bracket == '('){    // if opening parenthesis, break
                        break;
                    }
                    count++;        // increment number of operands
                    if(count == 1){ // first operand
                        operandList = new long int[count];
                    }
                    else{           // update size of array for new operands
                        tempList = new long int[count - 1];
                        for(int i = 0; i < count - 1; i++){
                            tempList[i] = operandList[i];
                        }
                        delete [] operandList;
                        operandList = new long int[count];
                        for(int i = 0; i < count - 1; i++){
                            operandList[i] = tempList[i];
                        }
                        delete [] tempList;
                    }
                    operandList[count - 1] = temp.value;
                }
                answer = C->makeCalculation(word, operandList, count, flag);
                if(!flag){      // check for errors
                    delete [] operandList;
                    return -1;
                }
                S->push(answer,' ');       // push result of the expression into stack
            }
        }
    }
    delete [] operandList;
    S->close();
    Q->enqueue(answer); // add answer to queue
    return answer;
}
string Interpreter::prefixToPostfix(string& prefix, bool& flag){

    string postfix = "";
    istringstream iss1(prefix);
    string temp = "";
    string word;
    bool isOperand = true;  // if true, it is operand
    while(iss1 >> word){    // take the reverse (to read from right to left) of input expression
        temp = word + " " + temp;
    }
    istringstream iss2(temp);
    while(iss2 >> word) {
        isOperand = true;
        if(word == "("){        // put '(' for each ')'
            postfix += ") ";
            continue;
        }
        else if(word == ")"){   // put ')' for each '(' and push
            postfix += "( ";
            S->push(0,')');
            continue;
        }
        if(word == "inf" || word == "-inf" || (!Q->isempty() && word == "ans")){    // special operands
            isOperand = true;
        }
        else{
            if(word == "-"){    // to distinguish "-" and negative numbers such as "-2"
                isOperand = false;
            }
            for(int i = 0; i < word.length(); i++){         // check if it is a number
                if(((word[i] > 57 || word[i] < 48)) && word[i] != 45){
                    isOperand = false;
                }
            }
        }
        if(isOperand){      // if it is operand, push into stack
            long int operand;
            if(word == "inf"){
                operand = LONG_MAX;
                S->push(operand, ' ');
            }
            else if(word == "-inf"){
                operand = LONG_MIN;
                S->push(operand, ' ');
            }
            else if(!Q->isempty() && word == "ans"){
                operand = Q->back->value;
                S->push(operand, 'a');
            }
            else{
                operand = atol(word.c_str());
                S->push(operand, ' ');
            }
        }
        else{       // if not operand
            int operandCount = C->getOperandCount(word);
            int count = 0;
            if(operandCount != -1){    // check if it is a defined operator
                while(!S->isempty()){
                    operand temp = S->pop();
                    if(temp.bracket == ')'){    // if closing parenthesis, break
                        break;
                    }
                    count++;
                    // add operand to string(postfix)
                    if(temp.value == LONG_MAX){
                        postfix += "inf ";
                    }
                    else if (temp.value == LONG_MIN){
                        postfix += "-inf ";
                    }
                    else if(!Q->isempty() && temp.bracket == 'a'){
                       postfix += "ans ";
                    }
                    else{
                        // long int to string
                        stringstream ss;
                        string value_str;
                        ss << temp.value;
                        value_str = ss.str();
                        postfix = postfix + value_str + " ";
                    }
                }
                if(operandCount == 1 && count > 1){     // unary operator but more than 1 operand
                    flag = false;
                }
                else if(operandCount == 2 && count > 2){// binary operator but more than 2 operands
                    flag = false;
                }
                else if(operandCount == 3 && count > 2){// binary or unary opertor but more than 2 operands
                    flag = false;
                }
                if(!flag){      // if convertion could not be done, return "" with false flag
                    return "";
                }
                postfix = postfix + word + " ";         // add operator name to string(postfix)
            }
            else{       // undefined operator name
                flag = false;
                return "";
            }
        }
    }
    if(!S->isempty()){  // if any operand is left in stack, it means syntax error.
        flag = false;
        return "";
    }
    return postfix;
}
