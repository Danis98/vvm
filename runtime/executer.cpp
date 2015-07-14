#include <executer.h>

#define TOK_TYPE_TO_VAR_TYPE(tok, var, var_name)				\
(tok==TOK_PARAM? var=var_map[formal_stack.top()[get_par_num(var_name)]].type:	\
	(tok==TOK_IDENTIFIER? var=var_map[var_name].type:			\
		(tok==TOK_BOOL?	var=BOOL:					\
			(tok==TOK_STRING? var=STRING:				\
				(tok==TOK_DOUBLE? var=DOUBLE:			\
					(tok==TOK_INT? var=INT:			\
						var=UNINITIALIZED		\
					)					\
				)						\
			)							\
		)								\
	)									\
)

int instr_ptr=0;

void execute(){
	while(instr_ptr<instr_num){
		exec_instr(instr_ptr);
		//print_status();
	}
	
	std::cout<<"Final variable values:\n";
	for(variable_map::const_iterator it=var_map.begin();it!=var_map.end();it++)
		std::cout<<it->first<<" ["<<var_types_str[(int)(it->second.type)]<<"] ->\t\t"<<it->second.val<<"\n";
}

void exec_instr(int index){
	cmd_t cmd=cmds[index];
	
	//Mathematical and logical operations
	if(cmd.type==ADD || cmd.type==SUB
		|| cmd.type==MULT || cmd.type==DIV 
		|| cmd.type==MOD
		|| cmd.type==CEQ || cmd.type==CNE
		|| cmd.type==CLT || cmd.type==CLE
		|| cmd.type==CGT || cmd.type==CGE){
		execute_math_op(cmd);
	}
	//Assignments
	else if(cmd.type==ASSIGN)
		assign(cmd.r, cmd.a1);
	//Function calling and returning
	else if(cmd.type==PARAM)
		par_stack.push_back(cmd.a1);
	else if(cmd.type==CALL){
		if(cmd.r!="") ret_stack.push(cmd.r);
		formal_params formal;
		for(int i=0;i<lexical_cast<int>(cmd.a2);i++){
			formal.push_back(par_stack[par_stack.size()-1]);
			par_stack.pop_back();
		}
		formal_stack.push(formal);
		if(std::find(sys_funcs.begin(), sys_funcs.end(), cmd.a1)==sys_funcs.end()){
			call_stack.push(instr_ptr);
			instr_ptr=labels[cmd.a1];
		}
		else{
			if(cmd.a1=="out")
				sys_out();
			else if(cmd.a1=="in")
				sys_in();
			else if(cmd.a1=="to_int")
				sys_to_int();
			else if(cmd.a1=="to_double")
				sys_to_double();
			else if(cmd.a1=="to_string")
				sys_to_string();
			else if(cmd.a1=="pow")
				sys_pow();
			else if(cmd.a1=="sqrt")
				sys_sqrt();
			else if(cmd.a1=="exit")
				sys_exit();
		}
	}
	else if(cmd.type==RET){
		//Pop formal parameters
		formal_stack.pop();
		//Return to the point of execution previous to the function call
		instr_ptr=call_stack.top();
		call_stack.pop();
		//Return a value
		if(cmd.a1!="null"){
			std::string ret_id=ret_stack.top();
			ret_stack.pop();
			assign(ret_id, cmd.a1);
		}
	}
	
	//Jump stmts
	else if(cmd.type==JUMP)
		instr_ptr=labels[cmd.a1];
	else if(cmd.type==JUMPIF){
		if(var_map[cmd.a1].checkTrue())
			instr_ptr=labels[cmd.a2];}
	else if(cmd.type==JUMPNIF){
		if(!var_map[cmd.a1].checkTrue())
			instr_ptr=labels[cmd.a2];
	}
	instr_ptr++;
}

//a := b
void assign(std::string a, std::string b){
	if(get_token_type(a)!=TOK_IDENTIFIER){
		std::cout<<a<<" is read-only!\n";
		exit(0);
	}
	tok_type expr_type=get_token_type(b);
	//Interpret an eventual param_n and recalculate
	if(expr_type==TOK_PARAM){
		b=formal_stack.top()[get_par_num(b)];
		expr_type=get_token_type(b);
	}
	if(var_map[a].type==UNINITIALIZED){
		var_type res_type;
		TOK_TYPE_TO_VAR_TYPE(expr_type, res_type, b);
		if(expr_type==TOK_IDENTIFIER)
			var_map[a]={res_type, var_map[b].val};
		else
			var_map[a]={res_type, b};
	}
	else{
		if(var_map[a].type!=var_map[b].type){
			if(var_map[a].type==DOUBLE && var_map[b].type==INT
				|| var_map[a].type==INT && var_map[b].type==DOUBLE)
				var_map[a].type==DOUBLE;
			else{
				std::cout<<"Incompatible assignment: "<<var_types_str[var_map[a].type]
					<<" := "<<var_types_str[var_map[b].type]<<"\n";
				exit(0);
			}
		}
		if(expr_type==TOK_IDENTIFIER)
			var_map[a].val=var_map[b].val;
		else
			var_map[a].val=b;
	}
}

void execute_math_op(cmd_t cmd){
	var_type a_type, b_type, r_type;
	std::string a_val, b_val, r_val;
	tok_type tok_a=get_token_type(cmd.a1);
	TOK_TYPE_TO_VAR_TYPE(tok_a, a_type, cmd.a1);
	tok_type tok_b=get_token_type(cmd.a2);
	TOK_TYPE_TO_VAR_TYPE(tok_b, b_type, cmd.a2);
	r_type=determine_res_type(a_type, b_type);
	
	a_val=tok_a==TOK_IDENTIFIER?var_map[cmd.a1].val:cmd.a1;
	b_val=tok_b==TOK_IDENTIFIER?var_map[cmd.a2].val:cmd.a2;
	
	//Handle logical operators
	switch(cmd.type){
		case CEQ:
			r_val=a_val==b_val?"true":"false";
			var_map[cmd.r]={BOOL, r_val};
			return;
		case CNE:
			r_val=a_val!=b_val?"true":"false";
			var_map[cmd.r]={BOOL, r_val};
			return;
		case CLT:
			if(a_type!=INT && a_type!=DOUBLE
				|| b_type!=INT && b_type!=DOUBLE)
				fatal("Operator "+cmd_str[(int)cmd.type]+" undefined for operands "
					+var_types_str[(int)a_type]+", "+var_types_str[(int)b_type]+"\n");
			r_val=lexical_cast<double>(a_val) < lexical_cast<double>(b_val)?"true":"false";
			var_map[cmd.r]={BOOL, r_val};
			return;
		case CLE:
			if(a_type!=INT && a_type!=DOUBLE
				|| b_type!=INT && b_type!=DOUBLE)
				fatal("Operator "+cmd_str[(int)cmd.type]+" undefined for operands "
					+var_types_str[(int)a_type]+", "+var_types_str[(int)b_type]+"\n");
			r_val=lexical_cast<double>(a_val) <= lexical_cast<double>(b_val)?"true":"false";
			var_map[cmd.r]={BOOL, r_val};
			return;
		case CGT:
			if(a_type!=INT && a_type!=DOUBLE
				|| b_type!=INT && b_type!=DOUBLE)
				fatal("Operator "+cmd_str[(int)cmd.type]+" undefined for operands "
					+var_types_str[(int)a_type]+", "+var_types_str[(int)b_type]+"\n");
			r_val=lexical_cast<double>(a_val) > lexical_cast<double>(b_val)?"true":"false";
			var_map[cmd.r]={BOOL, r_val};
			return;
		case CGE:
			if(a_type!=INT && a_type!=DOUBLE
				|| b_type!=INT && b_type!=DOUBLE)
				fatal("Operator "+cmd_str[(int)cmd.type]+" undefined for operands "
					+var_types_str[(int)a_type]+", "+var_types_str[(int)b_type]+"\n");
			r_val=lexical_cast<double>(a_val) >= lexical_cast<double>(b_val)?"true":"false";
			var_map[cmd.r]={BOOL, r_val};
			return;
	}
	
	//Handle mathematical operators
	//String concatenation
	if(r_type==STRING && cmd.type==ADD)
		var_map[cmd.r]={STRING, (a_type==STRING?cmd.a1.substr(0, cmd.a1.size()-1):cmd.a1)+
				(b_type==STRING?cmd.a2.substr(1, cmd.a2.size()-1):cmd.a2)};
	else if(r_type==STRING)
		fatal("Unsupported string operation: "+cmd_str[(int)cmd.type]+"\n");
	//Numerical
	//Bools don't have other compatible operands yet
	if(a_type==BOOL || b_type==BOOL)
		fatal("Mathematical operator "+cmd_str[(int)cmd.type]+" on bool values\n");
	
	switch(cmd.type){
	case ADD:
		if(r_type==INT)
			var_map[cmd.r]={r_type, to_string<int>(lexical_cast<int>(a_val)+lexical_cast<int>(b_val))};
		else if(r_type==DOUBLE)
			var_map[cmd.r]={r_type, to_string<double>(lexical_cast<double>(a_val)+lexical_cast<double>(b_val))};
		return;
	case SUB:
		if(r_type==INT)
			var_map[cmd.r]={r_type, to_string<int>(lexical_cast<int>(a_val)-lexical_cast<int>(b_val))};
		else if(r_type==DOUBLE)
			var_map[cmd.r]={r_type, to_string<double>(lexical_cast<double>(a_val)-lexical_cast<double>(b_val))};
		return;
	case MULT:
		if(r_type==INT)
			var_map[cmd.r]={r_type, to_string<int>(lexical_cast<int>(a_val)*lexical_cast<int>(b_val))};
		else if(r_type==DOUBLE)
			var_map[cmd.r]={r_type, to_string<double>(lexical_cast<double>(a_val)*lexical_cast<double>(b_val))};
		return;
	case DIV:
		if(r_type==INT)
			var_map[cmd.r]={r_type, to_string<int>(lexical_cast<int>(a_val)/lexical_cast<int>(b_val))};
		else if(r_type==DOUBLE)
			var_map[cmd.r]={r_type, to_string<double>(lexical_cast<double>(a_val)/lexical_cast<double>(b_val))};
		return;
	case MOD:
		if(r_type==INT)
			var_map[cmd.r]={r_type, to_string<int>(lexical_cast<int>(a_val)%lexical_cast<int>(b_val))};
		else if(r_type==DOUBLE)
			fatal("Operator MOD undefined for operands "+var_types_str[(int)a_type]+", "+var_types_str[(int)b_type]+"\n");
		return;
	default:
		fatal("Undefined operator "+cmd_str[(int)cmd.type]+"\n");
	}
}

int get_par_num(std::string id){
	return lexical_cast<int>(id.substr(6));
}

tok_type get_token_type(std::string tok){
	tok_type t;
	if(is_int(tok))
		t=TOK_INT;
	else if(is_double(tok))
		t=TOK_DOUBLE;
	else if(tok=="true" || tok=="false")
		t=TOK_BOOL;
	else if(tok[0]=='"' && tok[tok.length()-1]=='"')
		t=TOK_STRING;
	else if(strncmp(tok.c_str(), "sym_", 4)==0
		|| strncmp(tok.c_str(), "t", 1)==0)
		t=TOK_IDENTIFIER;
	else if(strncmp(tok.c_str(), "param_", 6)==0)
		t=TOK_PARAM;
	else{
		std::cout<<"Invalid token "<<tok<<"\n";
		exit(0);
	}
	return t;
}

void print_status(){
	if(instr_ptr==instr_num) return;
	std::cout<<"---------------------------------------\n";
	std::cout<<"INSTR: "<<instr_ptr<<" / "<<instr_num<<"\n";
	std::cout<<cmd_str[(int)(cmds[instr_ptr].type)]<<"{"<<cmds[instr_ptr].a1<<", "<<cmds[instr_ptr].a2<<"} = "<<cmds[instr_ptr].r<<"\n";
	std::cout<<"VARIABLES\n";
	for(variable_map::const_iterator it=var_map.begin();it!=var_map.end();it++)
		std::cout<<(it->first)<<" ->\t"<<(it->second.val)<<"\n";
	std::cout<<"FORMAL PARAMS:\n";
	if(formal_stack.size()>0)
		for(formal_params::const_iterator it=formal_stack.top().begin();it!=formal_stack.top().end();it++)
			std::cout<<*it<<" ";
	std::cout<<"\n";
	std::cout<<"PARAM_STACK:\n";
	if(par_stack.size()>0)
		for(param_stack::const_iterator it=par_stack.begin();it!=par_stack.end();it++)
			std::cout<<*it<<" ";
	std::cout<<"---------------------------------------\n";
}