#pragma once
#include <set>
#include <utility>

class CodeTree {
public:
    CodeTree(std::set<std::pair<int, char>>);
    std::string decode(std::string&);
private:
    CodeTree* left;
    CodeTree* right;
    std::string symbols;
};
