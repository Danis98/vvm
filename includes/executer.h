#ifndef _EXECUTER_H
#define _EXECUTER_H

#include <iostream>
#include <cmd_list.h>
#include <variable_map.h>
#include <label_list.h>
#include <func_stacks.h>
#include <typecheck.h>
#include <regex>
#include <sstream>

enum sym_type{
	SYM_IDENTIFIER,
	SYM_INT,
	SYM_DOUBLE,
	SYM_BOOL,
	SYM_STRING
};

extern int sys_funcs_num;
extern std::string sys_funcs[];

void execute();
void exec_instr(int index);
void execute_math_op(cmd_t cmd);

sym_type get_symbol_type(std::string sym);

template <typename T>
inline T lexical_cast(const std::string& str)
{
    T var;
    std::istringstream iss;
    iss.str(str);
    iss >> var;
    return var;
}

#endif