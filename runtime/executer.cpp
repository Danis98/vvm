#include <executer.h>

int instr_ptr=0;

void execute(){
	for(std::map<label, addr>::const_iterator it=labels.begin(); it!=labels.end(); it++){
		std::cout<<"Label: "<<it->first<<" ["<<it->second<<"]\n";
	}
}

void exec_instr(int index){
	cmd_t cmd=cmds[index];
	
	sym_type sym_type_a1, sym_type_a2;
	var_type res_type;
	if(cmd.type==ADD || cmd.type==SUB
		|| cmd.type==MULT || cmd.type==DIV 
		|| cmd.type==MOD
		|| cmd.type==CEQ || cmd.type==CNE
		|| cmd.type==CLT || cmd.type==CLE
		|| cmd.type==CGT || cmd.type==CGE){
		execute_math_op(cmd);
	}
	else if(cmd.type==ASSIGN){
		sym_type expr_type=get_symbol_type(cmd.a1);
		variable *temp;
		if(expr_type==SYM_INT){
			temp=new int_var(lexical_cast<int>(cmd.a1));
			((int_var*)&var_map[cmd.a1])->val=((int_var*)temp)->val;
		}
		else if(expr_type==SYM_DOUBLE){
			temp=new double_var(lexical_cast<double>(cmd.a1));
		}
		else if(expr_type==SYM_BOOL){
			temp=new bool_var(cmd.a1=="true");
		}
		else if(expr_type==SYM_STRING){
			temp=new str_var(cmd.a1);
		}
		
	}
	else if(cmd.type==PARAM)
		par_stack.push(cmd.a1);
	else if(cmd.type==CALL){}
	else if(cmd.type==JUMP)
		instr_ptr=labels[cmd.a1];
	else if(cmd.type==JUMPIF){}
	else if(cmd.type==JUMPNIF){}
	instr_ptr++;
}

void assign(variable a, variable b){
	if(a.type!=b.type){
		std::cout<<"Incompatible assignment!\n";
		exit(0);
	}
	if(a.type==STRING){}
}

void execute_math_op(cmd_t cmd){
	
}

sym_type get_symbol_type(std::string sym){
	if(std::regex_match(sym.c_str(), std::regex("sym_.+"))
		|| std::regex_match(sym.c_str(), std::regex("t[0-9]+")))
		return SYM_IDENTIFIER;
	else if(std::regex_match(sym.c_str(), std::regex("-?[0-9]+")))
		return SYM_INT;
	else if(std::regex_match(sym.c_str(), std::regex("-?[0-9]+\\.[0-9]+")))
		return SYM_DOUBLE;
	else if(sym=="true" || sym=="false")
		return SYM_BOOL;
	else if(std::regex_match(sym.c_str(), std::regex("\".+\"")))
		return SYM_STRING;
	std::cout<<"Invalid token "<<sym<<"\n";
	exit(0);
}