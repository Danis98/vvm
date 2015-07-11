#ifndef _LABEL_LIST_H
#define _LABEL_LIST_H

#include <string>
#include <map>

typedef std::string label;
typedef int addr;

typedef std::map<label, addr> label_list;

extern label_list labels;

#endif