#ifndef _EXECUTER_H
#define _EXECUTER_H

#include <cmd_list.h>
#include <variable_map.h>
#include <label_list.h>
#include <func_stacks.h>
#include <typecheck.h>
#include <lex_cast.h>
#include <token_type.h>
#include <builtin_funcs.h>
#include <fatal_error.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

void execute();
void exec_instr(int index);
void execute_math_op(cmd_t cmd);
void assign(std::string a, std::string b);
int get_par_num(std::string id);

void print_status();

extern int instr_num;

inline bool is_int(std::string s){
	for(int i=0;i<s.length();i++)
		if(s[i]<'0' || s[i]>'9')
			return false;
	return true;
}

inline bool is_double(std::string s){
	bool dot=false;
	for(int i=0;i<s.length();i++){
		if(s[i]=='.' && dot)
			return false;
		if(s[i]=='.' && !dot)
			dot=true;
		if((s[i]<'0' || s[i]>'9')
			&& s[i]!='.')
			return false;
	}
	return dot;
}

#endif