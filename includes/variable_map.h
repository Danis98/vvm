#ifndef _VARIABLE_MAP_H
#define _VARIABLE_MAP_H

#include <map>
#include <string>

union var_value{
	std::string str;
	int i;
	double d;
	bool b;
};

enum var_type{
	INT,
	DOUBLE,
	BOOL,
	STRING,
	UNINITIALIZED
};

extern std::string var_types_str[];

struct variable{
	var_type type;
	var_value val;
};

typedef std::string var_id;
typedef std::map<var_id, variable> variable_map;

extern variable_map var_map;

#endif