#ifndef _PARSER_H
#define _PARSER_H

#include <main.h>
#include <cmd_list.h>
#include <sstream>

//Operands required by each operator
extern int req_ops[];

extern int line_num;

void parse();
void parse_line(std::string line);
int required_operands(std::string cmd);

#endif