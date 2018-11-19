#include "codetree.h"

#pragma once

#include <string>

CodeTree *fanno_shannon(const std::string &message);

CodeTree *fanno_shannon(const Symbol *symbols, int len);
