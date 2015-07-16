#include <builtin_funcs.h>

#define EXTRACT_VALUE(id)				\
s_##id==TOK_DOUBLE || s_##id==TOK_INT? val_##id=lexical_cast<double>(id):	\
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

//Print to console
void sys_out(){
	//msg := param_0
	std::string v=formal_stack.top()[0];
	tok_type t=get_token_type(v);
	//Read value
	if(t==TOK_IDENTIFIER){
		v=var_map[v].val;
		t=get_token_type(v);
	}
	//Trim the double quotes
	if(t==TOK_STRING){
		std::cout<<v.substr(1, v.size()-2);
	}
	else
		std::cout<<v;
	formal_stack.pop();
}

//Read line from console
void sys_in(){
	std::string s;
	std::getline(std::cin, s);
	std::string r=ret_stack.top();
	ret_stack.pop();
	assign(r, '"'+s+'"');
	formal_stack.pop();
}

//[string / double / bool] -> [int]
void sys_to_int(){
	std::string r=ret_stack.top();
	ret_stack.pop();
	std::string val=formal_stack.top()[0];
	tok_type t=get_token_type(val);
	if(t==TOK_IDENTIFIER){
		val=var_map[val].val;
		t=get_token_type(val);
	}
	if(t==TOK_STRING)
		val=val.substr(1, val.length()-2);
	else if(t==TOK_DOUBLE)
		val=to_string<int>((int)lexical_cast<double>(val));
	else if(t==TOK_BOOL)
		val=val=="true"?"1":"0";
	assign(r, val);
	var_map[r].type=INT;
	formal_stack.pop();
}

//[string / bool] -> [double]
//You can assign int values to doubles directly
void sys_to_double(){
	std::string r=ret_stack.top();
	ret_stack.pop();
	std::string val=formal_stack.top()[0];
	tok_type t=get_token_type(val);
	if(t==TOK_IDENTIFIER){
		val=var_map[val].val;
		t=get_token_type(val);
	}
	if(t==TOK_STRING)
		val=val.substr(1, val.length()-2);
	else if(t==TOK_BOOL)
		val=val=="true"?"1":"0";
	assign(r, val);
	var_map[r].type=DOUBLE;
	formal_stack.pop();
}

//[int / double / bool] -> [string]
void sys_to_string(){
	std::string r=ret_stack.top();
	ret_stack.pop();
	std::string val=formal_stack.top()[0];
	tok_type t=get_token_type(val);
	if(t==TOK_IDENTIFIER){
		val=var_map[val].val;
		t=get_token_type(val);
	}
	if(t!=TOK_STRING)
		val='"'+val+'"';
	assign(r, val);
	var_map[r].type=STRING;
	formal_stack.pop();
}

//a^b
void sys_pow(){
	//a := param_0
	std::string a=formal_stack.top()[0];
	//b := param_1
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

//Square root
void sys_sqrt(){
	//a := param_0
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

//Exit from the program
void sys_exit(){
	exit(0);
}