/*
*
* @Author
* Student Name: Emre KÖSE
* Student ID: 150130037
* Date: 25.12.2016
*
*/

#ifndef data_structures_h
#define data_structures_h

// STACK STRUCTURE
struct operand{
    long int value;
    char bracket;      // '(' , ')' , ''=operand , 'a'=ans
    operand* next;
};
struct Stack{
    operand* top;
    void create();
    void close();
    bool isempty();
    void push(long int, char);
    operand pop();
    int count();
};

// QUEUE STRUCTURE
struct result{
    long int value;
    result* next;
};
struct Queue{
    result* front;
    result* back;
    void create();
    void close();
    bool isempty();
    void enqueue(long int new_result);
    long int dequeue();
    void printAll();    // print final answer queue
};
#endif /* data_structures_h */
