#ifndef _VARIABLE_MAP_H
#define _VARIABLE_MAP_H

#include <map>
#include <string>

//Types of variables
enum var_type{
	INT,
	DOUBLE,
	BOOL,
	STRING,
	UNINITIALIZED
};

extern std::string var_types_str[];

//Variable contents
class variable{
public:
	var_type type=UNINITIALIZED;
	std::string val="";
	variable(){}
	variable(var_type type, std::string val) : type(type), val(val) {}
	bool checkTrue(){
		switch(type){
		case INT:
			return val!="0";
		case DOUBLE:
			return val!="0";
		case BOOL:
			return val=="true";
		case STRING:
			return val!="";
		}
	};
};

typedef std::string var_id;
typedef std::map<var_id, variable> variable_map;

extern variable_map var_map;

#endif