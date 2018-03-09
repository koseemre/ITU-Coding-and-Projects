/*
*
* @Author
* Student Name: Emre KÖSE
* Student ID: 150130037
* Date: 25.12.2016
*
*/
#include <iostream>
#include <math.h>
#include <limits.h>
#include "calculator.h"
using namespace std;

// defining inf
static long int inf = LONG_MAX;
// operator list
static string operators[11] = {"abs","sqrt","sub","div","exp","log","mod","sum","product","min","max"};
// number of operands for operators
static int operandCounts[11] = {1,1,2,2,3,3,3,4,4,4,4}; // 1: 1 operand, 2: 2 operand, 3: 1 or 2 operand, 4: >= 0 operand

// return_flag is true when calculation done, false when calculation is not allowed.
long int Calculator::makeCalculation(string& op_name, long int* operands, int operand_count, bool& return_flag){
    long int answer;
    flag = true;        // flag is used for not-allowed calculations
    if(op_name == "abs"){
        answer = f_abs(operands[0]);
    }
    else if(op_name == "sqrt"){
        answer = f_sqrt(operands[0]);
    }
    else if(op_name == "sub"){
        answer = f_sub(operands[1],operands[0]);    // operands are sent in reverse order because their order has changed when popped from stack
    }
    else if(op_name == "div"){
        answer = f_div(operands[1],operands[0]);
    }
    else if(op_name == "exp"){
        if(operand_count == 1){
            answer = f_exp(operands[0]);
        }
        else{
            answer = f_exp(operands[1],operands[0]);
        }
    }
    else if(op_name == "log"){
        if(operand_count == 1){
            answer = f_log(operands[0]);
        }
        else{
            answer = f_log(operands[1],operands[0]);
        }
    }
    else if(op_name == "mod"){
        if(operand_count == 1){
            answer = f_mod(operands[0]);
        }
        else{
            answer = f_mod(operands[1],operands[0]);
        }
    }
    else if(op_name == "sum"){
        answer = f_sum(operands,operand_count);
    }
    else if(op_name == "product"){
        answer = f_product(operands,operand_count);
    }
    else if(op_name == "min"){
        answer = f_min(operands,operand_count);
    }
    else{      // "max"
        answer = f_max(operands,operand_count);
    }
    return_flag = flag;
    return answer;
}
// get number of operands that operator needs
int Calculator::getOperandCount(string& op_name){
    for(int i = 0; i < 11; i++){
        if(op_name == operators[i]){
            return operandCounts[i];
        }
    }
    return -1;      // if operator is not defined.
}
  //*******************\\
 // OPERATOR FUNCTIONS  \\
//***********************\\

long int Calculator::f_abs(long int n){
    if(n < 0){
        return -n;
    }
    return n;
}
long int Calculator::f_sqrt(long int n){
    if(n == inf){       // sqrt of infinity is infinity
        return inf;
    }
    else if(n < 0){     // negative numbers are not allowed
        flag = false;
        return -1;
    }
    return sqrt(n);
}
long int Calculator::f_sub(long int n1, long int n2){
    if( (n1 == inf && n2 == inf) || (n1 == -inf && n2 == -inf)){  // inf - inf and -inf - -inf not allowed.
        flag = false;
        return -1;
    }
    else if(n1 == inf){
        return inf;
    }
    else if(n1 == -inf){
        return -inf;
    }
    return n1 - n2;
}
long int Calculator::f_div(long int n1, long int n2){
    if( (n1 == inf && n2 == inf) || (n1 == -inf && n2 == -inf) || (n1 == -inf && n2 == inf) || (n1 == inf && n2 == -inf) || (n2 == 0)){     // forbidden operands
        flag = false;
        return -1;
    }
    else if(n1 == inf && n2 > 0){
        return inf;
    }
    else if(n1 == inf && n2 < 0){
        return -inf;
    }
    else if(n1 == -inf && n2 > 0){
        return -inf;
    }
    else if(n1 == -inf && n2 < 0){
        return inf;
    }
    return n1 / n2;
}
long int Calculator::f_exp(long int n){
    if(n == inf){
        return inf;
    }
    else if(n == -inf){
        return 0;
    }
    return pow(2.71828182, n);
}
long int Calculator::f_exp(long int x, long int n){
    if((x == inf && n == 0) || (x == -inf && n == 0) || (x == 0 && n == 0) || (x == 1 && n == inf) || (x == 0 && n == -inf)){   // forbidden operands
        flag = false;
        return -1;
    }
    else if(n == -inf){
        return 0;
    }
    return pow(x,n);
}
long int Calculator::f_log(long int n){
    if(n <= 0){     // zero and negative numbers are not allowed
        flag = false;
        return -1;
    }
    else if(n == inf){
        return inf;
    }
    return log(n);
}
long int Calculator::f_log(long int x, long int n){
    if(x < 0 || n < 0 || x == 1 || x == inf){ // forbidden operands
        flag = false;
        return -1;
    }
    else if(n == inf){
        return inf;
    }
    return log(n) / log(x);
}
long int Calculator::f_mod(long int n){
    if(n <= 0 || n == inf){ // forbidden operands
        flag = false;
        return -1;
    }
    return n % 10;
}
long int Calculator::f_mod(long int x, long int n){
    if(n <= 0 || x <= 0 || n == inf || x == inf){ // forbidden operands
        flag = false;
        return -1;
    }
    return n % x;
}
long int Calculator::f_sum(long int* n, int count){
    bool isInf = false, is_Inf = false;     // check for if there is inf and -inf
    long int total = 0;
    for(int i = 0; i < count; i++){
        if(n[i] == inf){
            isInf = true;
        }
        else if(n[i] == -inf){
            is_Inf = true;
        }
        else{
            total += n[i];
        }
    }
    if(isInf && is_Inf){
        flag = false;
        return -1;
    }
    else if(isInf){
        return inf;
    }
    else if(is_Inf){
        return -inf;
    }
    return total;
}
long int Calculator::f_product(long int* n, int count){
    bool isInf = false, is_Inf = false;     // check for if there is inf and -inf
    long int total = 1;
    for(int i = 0; i < count; i++){
        if(n[i] == inf){
            isInf = true;
        }
        else if(n[i] == -inf){
            total *= -1;
            is_Inf = true;
        }
        else{
            total *= n[i];
        }
    }
    if(isInf || is_Inf){
        if(total > 0){
            return inf;
        }
        else{
            return -inf;
        }
    }
    return total;
}
long int Calculator::f_min(long int* n, int count){
    long int minimum = inf;
    for(int i = 0; i < count; i++){
        if(n[i] == -inf){
            return -inf;
        }
        else if(n[i] < minimum){
            minimum = n[i];
        }
    }
    return minimum;
}
long int Calculator::f_max(long int* n, int count){
    long int maximum = -inf;
    for(int i = 0; i < count; i++){
        if(n[i] == inf){
            return inf;
        }
        else if(n[i] > maximum){
            maximum = n[i];
        }
    }
    return maximum;
}
