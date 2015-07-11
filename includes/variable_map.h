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
};

class str_var : public variable{
public:
	std::string val;
	str_var(std::string val) : val(val){
		type=STRING;
	}
};

class int_var : public variable{
public:
	int val;
	int_var(int val) : val(val){
		type=INT;
	}
};

class double_var : public variable{
public:
	double val;
	double_var(double val) : val(val){
		type=DOUBLE;
	}
};

class bool_var : public variable{
public:
	bool val;
	bool_var(bool val) : val(val){
		type=BOOL;
	}
};

typedef std::string var_id;
typedef std::map<var_id, variable> variable_map;

extern variable_map var_map;

#endif