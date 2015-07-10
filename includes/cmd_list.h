#ifndef _CMD_LIST_H
#define _CMD_LIST_H

#include <vector>

typedef std::string operand;

//Possible commands
enum cmd_type{
	ADD,
	SUB,
	MULT,
	DIV,
	MOD,
	ASSIGN,
	PARAM,
	CALL,
	JUMP,
	JUMPIF,
	JUMPNIF,
	LABEL,
	CEQ,
	CNE,
	CLT,
	CLE,
	CGT,
	CGE,
	RET
};

extern int cmd_num;
extern std::string cmd_str[];

cmd_type get_cmd(std::string cmd);

//Command
struct cmd_t{
	cmd_type type;
	operand a1, a2, r;
	
	bool isResult(operand op){
		return r==op;
	}
};

typedef std::vector<cmd_t> cmd_list;

extern cmd_list cmds;

#endif