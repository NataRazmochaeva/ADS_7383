#include <string>
#include <stdexcept>
#include "CodeTree.hpp"

CodeTree::CodeTree(std::set<std::pair<int, char>> freq) {
    int weight = 0, sum = 0;
    for(auto it : freq) {
        weight += std::get<0>(it);
        symbols.push_back(std::get<1>(it));
    }
    if(symbols.length() == 1) {
        left = nullptr;
        right = nullptr;
        return;
    }
    std::set<std::pair<int, char>> left_freq, right_freq;
    for(auto it = freq.rbegin(); it != freq.rend(); ++it) {
        if(std::get<0>(*it) + sum <= (weight+1)/2) {
            sum += std::get<0>(*it);
            left_freq.insert(*it);
        }
        else
            right_freq.insert(*it);
    }
    if(sum < weight - sum)
        left_freq.swap(right_freq);
    left = new CodeTree(left_freq);
    right = new CodeTree(right_freq);
}

std::string CodeTree::decode(std::string& encoded) {
    CodeTree* cur = this;
    std::string res;
    for(auto it : encoded) {
        if(it == '1')
            cur = cur->left;
        else 
	    if(it == '0') 
	        cur = cur->right;
	    else
		throw std::invalid_argument("Invalid encoded string");
        if(cur->left == nullptr) {
            res += cur->symbols;
            cur = this;
        }
    }
    return res;
}
