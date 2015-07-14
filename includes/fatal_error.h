#ifndef _FATAL_ERR_H
#define _FATAL_ERR_H

#include <iostream>
#include <string>
#include <cstdlib>

inline void fatal(std::string msg){
	std::cout<<msg;
	exit(0);
}

#endif