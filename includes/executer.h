#ifndef _EXECUTER_H
#define _EXECUTER_H

#include <iostream>
#include <cmd_list.h>
#include <variable_map.h>
#include <typecheck.h>
#include <regex>

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

sym_type get_symbol_type(std::string sym);

#endif