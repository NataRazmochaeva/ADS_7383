#include <iostream>
#include <set>
#include <utility>
#include <fstream>
#include "CodeTree.hpp"

auto table_parser(std::istream& input) {
    std::string s;
    int n = 0;
    getline(input, s);
    n = std::stoi(s);
    char c;
    int num;
    std::set<std::pair<int, char>> freq;
    for(int i=0; i<n; ++i) {
        input >> c;
        getline(input, s);
        num = std::stoi(s);
        freq.insert(std::make_pair(num, c));
    }
    return freq;
}

int main() {
    std::string command;
    std::filebuf file;
    std::string filename;
    while(true) {
        std::cout << "Enter 0 to read input from consol or 1 to read from file or 2 to exit: ";
        getline(std::cin, command);
        try {
            if(std::stoi(command) == 2)
                break;
        }
        catch(std::exception &e) {
            std::cout << "Invalid command, try again" << std::endl;
            continue;
        }
        std::set<std::pair<int, char>> freq;
        std::string encoded;
        try {
            switch(std::stoi(command)) {
            case 0: {
                std::cout << "Enter number of symbols: ";
    		std::string s;
    		int n = 0;
    		getline(std::cin, s);
    		n = std::stoi(s);
                std::cout << "Enter symbols and their frequency:" << std::endl;
                char c;
                int num;
                for(int i=0; i<n; ++i) {
                    std::cin >> c;
                    getline(std::cin, s);
                    num = std::stoi(s);
                    freq.insert(std::make_pair(num, c));
                }
                std::cout << "Enter encoded message:" << std::endl;
                std::getline(std::cin, encoded);
                break;
            }
            case 1: {
                std::cout << "Enter file name: ";
                getline(std::cin, filename);
                if(file.open(filename, std::ios::in)) {
                    std::istream fin(&file);
                    freq = table_parser(fin);
                    getline(fin, encoded);
                    file.close();
                }
                else {
                    std::cout << "Incorrect filename" << std::endl;
                    file.close();
                    continue;
                }
                break;
            }
            default: {
                std::cout << "Incorrect command, try again" << std::endl;
                continue;
            }
            }
        }
        catch(std::exception &e) {
            std::cout << "Invalid table" << std::endl;
            continue;
        }
	try{
            CodeTree code(freq);
            std::cout << "Decoded message:" << std::endl << code.decode(encoded) << std::endl;
	}
	catch(std::exception &e){
	    std::cout << e.what() << std::endl;
	}
    }
    return 0;
}

