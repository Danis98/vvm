#ifndef _LEX_CAST_H
#define _LEX_CAST_H

#include <string>
#include <sstream>

template <typename T>
inline T lexical_cast(const std::string& str)
{
    T var;
    std::istringstream iss;
    iss.str(str);
    iss >> var;
    return var;
}

template <typename T>
inline std::string to_string(T val){
	std::stringstream ss;
	ss<<val;
	return ss.str();
}

#endif