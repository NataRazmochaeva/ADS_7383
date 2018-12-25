#ifndef TASK_H
#define TASK_H

#include <tuple>
#include "coding.h"

void create_task(std::vector<std::pair<int, char>> &freq, std::string &message, std::string &encoded, CodeTree*(*coding)(std::set<std::pair<int, char>>));

#endif
