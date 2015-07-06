#ifndef _CMD_LIST_H
#define _CMD_LIST_H

#include <vector>

typedef std::string operand;

struct cmd{
	cmd_type type;
	operand a1, a2, r;
	
	bool isResult(operand op){
		return r==op;
	}
};

typedef std::vector<cmd> cmd_list;

extern cmd_list cmds;

#endif