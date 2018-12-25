#pragma once
#include <set>
#include <utility>

/*class ShannonFano {
public:
    ShannonFano();
    ShannonFano(std::set<std::pair<int, char>>);
    ShannonFano(std::set<std::pair<std::string, char>>);
    std::string decode(std::string&);
    std::string encode(std::string&);
private:
    ShannonFano* left;
    ShannonFano* right;
    std::string symbols;
};

class Huffman {
public:
    Huffman();
    Huffman(std::string);
    Huffman(std::set<std::pair<int, char>>);
    std::string decode(std::string&);
    std::string encode(std::string&);
private:
    Huffman* left;
    Huffman* right;
    std::string symbols;
};*/

class CodeTree{
public:
    static CodeTree* ShannonFano(std::set<std::pair<int, char>>);
    static CodeTree* Huffman(std::set<std::pair<int, char>>);
    std::string encode(std::string&);
    std::string decode(std::string&);
    ~CodeTree();
private:
    CodeTree(std::string);
    CodeTree* left;
    CodeTree* right;
    std::string symbols;
};
