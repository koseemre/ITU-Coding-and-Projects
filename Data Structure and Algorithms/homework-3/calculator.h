/*
 *
 * @Author
 * Student Name: <student_name>
 * Student ID: <student_id>
 * Date: 25.12.2016
 *
 */
#ifndef calculator_h
#define calculator_h
using namespace std;

struct Calculator{
    bool flag;  // is used to notify calculation errors
    long int makeCalculation(string& op_name, long int* operands, int operand_count,  bool& return_flag);       // redirect to relevant function
    int getOperandCount(string& op_name);       // number of operands that operator can take
    long int f_abs(long int n);
    long int f_sqrt(long int n);
    long int f_sub(long int n1, long int n2);
    long int f_div(long int n1, long int n2);
    long int f_exp(long int n);
    long int f_exp(long int x, long int n);
    long int f_log(long int n);
    long int f_log(long int x, long int n);
    long int f_mod(long int n);
    long int f_mod(long int x, long int n);
    long int f_sum(long int* n, int count);
    long int f_product(long int* n, int count);
    long int f_min(long int* n, int count);
    long int f_max(long int* n, int count);
};
#endif /* calculator_h */
