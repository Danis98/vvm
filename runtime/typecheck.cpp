#include <typecheck.h>

var_type determine_res_type(var_type a, var_type b){
	if(a==b)
		return a;
	else if(a==INT && b==DOUBLE
		|| a==DOUBLE && b==INT)
		return DOUBLE;
	else if(a==STRING || b==STRING)
		return STRING;
	else{
		std::cout<<"Invalid operand types: "<<var_types_str[(int)a]<<", "<<var_types_str[(int)b]<<"\n";
		exit(0);
	}
}