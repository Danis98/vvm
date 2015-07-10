#ifndef _MAIN_H
#define _MAIN_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>

#include <variable_map.h>
#include <parser.h>

extern std::ifstream inFile;

//Command line arguments parsing
#define MIN_ARGC 2
#define MAX_ARGC 2

void wrong_usage_msg(int arg_num);
void invalid_arg_msg(const char* arg);

inline bool file_exists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

#endif