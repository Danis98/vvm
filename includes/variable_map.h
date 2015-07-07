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
struct variable{
	enum var_type type;
	//Possible values
	std::string str;
	int i;
	double d;
	bool b;
};

typedef std::string var_id;
typedef std::map<var_id, variable> variable_map;

extern variable_map var_map;

#endif