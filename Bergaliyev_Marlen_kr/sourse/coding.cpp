#include <string>
#include <stdexcept>
#include "coding.h"
#include <iostream>
#include <tuple>

CodeTree::CodeTree(std::string syms){
    left = nullptr;
    right = nullptr;
    symbols = syms;
}

CodeTree* CodeTree::ShannonFano(std::set<std::pair<int, char>> freq) {
    int weight = 0, sum = 0;
    std::string syms;
    for(auto it : freq) {
        weight += std::get<0>(it);
        syms.push_back(std::get<1>(it));
    }
    CodeTree* res = new CodeTree(syms);
    if(syms.length() == 1) {
        return res;
    }
    std::set<std::pair<int, char>> left_freq, right_freq;
    auto it = freq.rbegin();
    for(; it != freq.rend(); ++it) {
        if(2*(std::get<0>(*it) + sum)-weight <= 2*sum-weight) {
            sum += std::get<0>(*it);
            left_freq.insert(*it);
        }
        else
            break;
    }
    for(; it != freq.rend(); ++it){
        right_freq.insert(*it);
    }
    /*for(auto it = freq.rbegin(); it != freq.rend(); ++it) {
        if(std::get<0>(*it) + sum <= (weight+1)/2) {
            sum += std::get<0>(*it);
            left_freq.insert(*it);
        }
        else
            right_freq.insert(*it);
    }*/
    if(sum < weight - sum)
        left_freq.swap(right_freq);
    res->left = ShannonFano(left_freq);
    res->right = ShannonFano(right_freq);
    return res;
}

CodeTree* CodeTree::Huffman(std::set<std::pair<int, char>> freq) {
    int weight = 0, sum = 0;
    std::set<std::tuple<int, std::string, CodeTree*>> nodes;
    std::string syms;
    for(auto it : freq) {
        std::tuple<int, std::string, CodeTree*> l(std::get<0>(it), std::string(1, std::get<1>(it)), new CodeTree(std::string(1, std::get<1>(it))));
        nodes.insert(l);
        syms.push_back(std::get<1>(it));
    }
    CodeTree* res = new CodeTree(syms);
    while(nodes.size() > 2){
        auto it = nodes.begin();
        auto r = *it;
        ++it;
        auto l = *it;
        CodeTree* new_node = new CodeTree(std::get<1>(l)+std::get<1>(r));
        new_node->left = std::get<2>(l);
        new_node->right = std::get<2>(r);
        std::tuple<int, std::string, CodeTree*> elem(std::get<0>(l)+std::get<0>(r), new_node->symbols, new_node);
        nodes.erase(it);
        nodes.erase(nodes.begin());
        nodes.insert(elem);
    }
    res->right = std::get<2>(*nodes.begin());
    res->left = std::get<2>(*++nodes.begin());
    return res;
}

/*ShannonFano::ShannonFano(std::set<std::pair<std::string, char>> freq) {
    ShannonFano* cur = this;
    cur->left = nullptr;
    cur->right = nullptr;
    for(auto it : freq){
	cur->symbols += std::string(1, std::get<1>(it));
	for(auto i : std::get<0>(it)){
	    if(i == '1'){
		if(cur->left == nullptr)
		    cur->left = new ShannonFano();
		cur = cur->left;
	    }
	    else 
		if(i == '0'){
		    if(cur->right == nullptr)
		        cur->right = new ShannonFano();
	 	    cur = cur->right;
		}
	        else throw std::invalid_argument("Invalid table");
	    cur->symbols += std::string(1, std::get<1>(it));
	}
	cur = this;
    }
}*/

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

std::string CodeTree::encode(std::string& message){
    CodeTree* cur = this;
    std::string encoded;
    for(auto it : message){
	while(cur->left != nullptr){
	    if(cur->left->symbols.find(it) != std::string::npos){
		encoded.append("1");
		cur = cur->left;
	    }
	    else{
		encoded.append("0"); 
		cur = cur->right;
	    }
	}
	cur = this;
    }
    return encoded;
}

CodeTree::~CodeTree(){
    delete left;
    delete right;
}
