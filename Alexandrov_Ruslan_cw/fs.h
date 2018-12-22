#ifndef COURSEWORK_FS_H
#define COURSEWORK_FS_H

#include "codetree.h"
#include "helper.h"

#include <string>

CodeTree *fanoShanon(const std::string &message);

CodeTree *fanoShanon(const Symbol *symbols, int len);



#endif //COURSEWORK_FS_H
