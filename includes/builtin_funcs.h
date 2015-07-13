#ifndef _BUILTIN_FUNCS_H
#define _BUILTIN_FUNCS_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>

#include <lex_cast.h>
#include <token_type.h>
#include <variable_map.h>
#include <func_stacks.h>

void assign(std::string a, std::string b);

extern int sys_funcs_num;
extern std::vector<std::string> sys_funcs;

void sys_out();
void sys_in();
void sys_to_int();
void sys_to_double();
void sys_to_string();
void sys_pow();
void sys_sqrt();
void sys_exit();

#endif