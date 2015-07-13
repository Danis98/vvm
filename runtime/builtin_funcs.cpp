#include <builtin_funcs.h>

#define EXTRACT_VALUE(id)				\
s_##id==TOK_DOUBLE? val_##id=lexical_cast<double>(id):	\
	(s_##id==TOK_IDENTIFIER? val_##id=lexical_cast<double>(var_map[id].val):\
	val_##id=0)

int sys_funcs_num=8;

std::vector<std::string> sys_funcs={
	"out",
	"in",
	"to_int",
	"to_double",
	"to_string",
	"pow",
	"sqrt",
	"exit"
};

void sys_out(){
	std::cout<<var_map[formal_stack.top()[0]].val;
	formal_stack.pop();
}

void sys_in(){
	std::string s;
	std::cin>>s;
	std::string r=ret_stack.top();
	ret_stack.pop();
	assign(r, '"'+s+'"');
	formal_stack.pop();
}

void sys_to_int(){
	std::string r=ret_stack.top();
	ret_stack.pop();
	assign(r, "param_0");
	var_map[r].type=INT;
	formal_stack.pop();
}

void sys_to_double(){
	std::string r=ret_stack.top();
	ret_stack.pop();
	assign(r, "param_0");
	var_map[r].type=DOUBLE;
	formal_stack.pop();
}

void sys_to_string(){
	std::string r=ret_stack.top();
	ret_stack.pop();
	assign(r, "param_0");
	var_map[r].type=STRING;
	formal_stack.pop();
}

void sys_pow(){
	std::string a=formal_stack.top()[0];
	std::string b=formal_stack.top()[1];
	tok_type s_a=get_token_type(a), s_b=get_token_type(b);
	double val_a, val_b;
	EXTRACT_VALUE(a);
	EXTRACT_VALUE(b);
	std::string r=ret_stack.top();
	ret_stack.pop();
	double val_r=pow(val_a, val_b);
	assign(r, to_string<double>(val_r));
	formal_stack.pop();
}

void sys_sqrt(){
	std::string a=formal_stack.top()[0];
	tok_type s_a=get_token_type(a);
	double val_a;
	EXTRACT_VALUE(a);
	std::string r=ret_stack.top();
	ret_stack.pop();
	double val_r=sqrt(val_a);
	assign(r, to_string<double>(val_r));
	formal_stack.pop();
}

void sys_exit(){
	exit(0);
}