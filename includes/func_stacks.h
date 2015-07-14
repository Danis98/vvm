#ifndef _PARAM_STACK_H
#define _PARAM_STACK_H

#include <stack>
#include <vector>
#include <string>

typedef std::string param;

typedef std::vector<param> param_stack;

extern param_stack par_stack;

//Formal arguments 
typedef std::vector<param> formal_params;

//Allow calls inside of functions
typedef std::stack<formal_params> formal_params_stack;

extern formal_params_stack formal_stack;

//Store the place to put the return value
typedef std::stack<param> return_stack;

extern return_stack ret_stack;

//Call stack
typedef std::stack<int> call_addr_stack;

extern call_addr_stack call_stack;

#endif