/*
*
* @Author
* Student Name: Emre KÖSE
* Student ID: 150130037
* Date: 25.12.2016
*
*/
#include <iostream>
#include <limits.h>
#include "data_structures.h"
using namespace std;


// STACK STRUCTURE OPERATIONS

void Stack::push(long int _value, char _bracket){
    operand* toadd = new operand;
    toadd->value = _value;
    toadd->bracket = _bracket;
    toadd->next = top;
    top = toadd;
}
operand Stack::pop(){
    operand *topnode = top;
    operand temp;
    top = top->next;
    temp = *topnode;
    delete topnode;
    return temp;
}
bool Stack::isempty(){
    return top == NULL;
}
void Stack::create(){
    top = NULL;
}
void Stack::close(){
    operand *traverse;
    while (top){
        traverse = top;
        top = top->next;
        delete traverse;
    }
}
int Stack::count(){
    int counter = 0;
    operand* traverse = top;
    while(traverse){
        traverse = traverse->next;
        counter++;
    }
    return counter;
}
// QUEUE STRUCTURE OPERATIONS

void Queue::enqueue(long int new_result){
    result *toadd = new result;
    toadd->value = new_result;
    toadd->next = NULL;
    if(isempty()){
        back = toadd;
        front = back;
    }
    else{
        back->next = toadd;
        back = toadd;
    }
}
long int Queue::dequeue(){
    long int temp;
    result *topnode = front;
    front = front->next;
    temp = topnode->value;
    delete topnode;
    return temp;
}
bool Queue::isempty(){
    return front == NULL;
}
void Queue::create(){
    front = NULL;
    back = NULL;
}
void Queue::close(){
    result *traverse;
    while (front){
        traverse = front;
        front = front->next;
        delete traverse;
    }
}
void Queue::printAll(){
    result* traverse = front;
    if (traverse){
        cout<<endl<<"Answer Queue: ";
    }
    else{
        cout<<endl<<"No Expression Calculated."<<endl<<endl;
        return;
    }
    while (traverse->next){

        if(traverse->value == LONG_MAX){    // print as inf
            cout<<"inf -> ";
        }
        else if(traverse->value == LONG_MIN){   // print as -inf
            cout<<"-inf -> ";
        }
        else{
            cout<<traverse->value<<" -> ";
        }

        traverse = traverse->next;

    }
    //print last element
    if(traverse->value == LONG_MAX){
        cout<<"inf";
    }
    else if(traverse->value == LONG_MIN){
        cout<<"-inf";
    }
    else{
        cout<<traverse->value;
    }
    cout<<endl<<endl;
}


