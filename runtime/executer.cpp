#include <executer.h>

void execute(){

}

void exec_instr(int index){
	cmd_t cmd=cmds[index];
	
	sym_type sym_type_a1, sym_type_a2;
	var_type res_type;
	switch(cmd.type){
		case ADD:
			sym_type_a1=get_symbol_type(cmd.a1);
			sym_type_a2=get_symbol_type(cmd.a2);
			
			return;
	}
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