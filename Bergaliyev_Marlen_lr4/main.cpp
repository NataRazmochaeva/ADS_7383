#include <iostream>
#include <fstream>
#include "BinTree.hpp"


BinTree<int> from_string(std::string::iterator &it){
    while(isspace(*it))
	++it;
    if(*it != '(')
        throw std::invalid_argument("Missing opening bracket");
    ++it;
    while(isspace(*it))
	++it;
    char* num = &(*it);
    int count = 0;
    while(isdigit(*it)) {
        ++count;
        ++it;
    }
    if(count == 0)
        throw std::invalid_argument("Missing number");
    BinTree<int> res(atoi(num));
    while(isspace(*it))
        ++it;
    if(*it == '('){
	if(*(it+1) != ')')
	    res.push_left(from_string(it));
	else it += 2;
    }
    else{
	num = &(*it);
	count = 0;
        while(isdigit(*it)) {
            ++count;
            ++it;
        }
        if(count == 0)
            throw std::invalid_argument("Missing number");
	res.push_left(BinTree<int>(atoi(num)));
    }
    while(isspace(*it))
	++it;
    if(*it == '('){
	if(*(it+1) != ')')
	    res.push_right(from_string(it));
	else it += 2;
    }
    else{
	num = &(*it);
	count = 0;
        while(isdigit(*it)) {
            ++count;
            ++it;
        }
        if(count == 0)
            throw std::invalid_argument("Missing number");
	res.push_right(BinTree<int>(atoi(num)));
    }
    if(*it != ')')
        throw std::invalid_argument("Missing closing bracket");
    ++it;
    return res;
}

int main(){
    std::string command;
    std::filebuf file;
    std::string filename;
    std::string input;
    while(true){
	std::cout << "Enter 0 to read input from consol or 1 to read from file or 2 to exit: "; 
	getline(std::cin, command);
	try{
	    if(std::stoi(command) == 2)
	    	break;
	}
	catch(std::exception &e){
	    std::cout << "Invalid command, try again" << std::endl;
	    continue;
	}
	switch(std::stoi(command)){
	    case 0:{
		std::cout << "Enter binary tree of numbers:" << std::endl;
		getline(std::cin, input);
		break;
	    }
	    case 1:{
		std::cout << "Enter file name: ";
		getline(std::cin, filename);
		if(file.open(filename, std::ios::in)){
		    std::istream fin(&file);
		    getline(fin, input);
		    file.close();
		}
		else{
		    std::cout << "Incorrect filename" << std::endl;
		    file.close();
		    continue;
		}
		break;
	    }
	    default:{
		std::cout << "Incorrect command, try again" << std::endl;
		continue;
	    }
	}
        std::string::iterator it = input.begin();
	try{
            BinTree<int> tree = from_string(it);
            std::cout << "Depth: " << tree.depth() << std::endl;
	    std::cout << "Internal way lenght: " << tree.internal_lenght() << std::endl;
	    std::cout << "Leafs:" << std::endl;
	    tree.print_leafs(std::cout);
	    std::cout << std::endl;
	    std::string level;
	    std::cout << "Enter level of tree: ";
	    getline(std::cin, level);
	    try{
	    	std::cout << level << "-level's number of nodes: " << tree.nlvl_node_number(std::stoi(level)) << std::endl;
	    }
	    catch(std::exception &e){
		std::cout << "It isn't number" << std::endl;
	    }
	    if(tree.equal_elem())
		std::cout << "There is equal elements" << std::endl;
	    else
		std::cout << "There is no equal elements" << std::endl;
	}
	catch(std::exception &e){
	    std::cout << e.what() << ":" << std::endl;
	    std::cout << input << std::endl;
	    std::cout << std::string(distance(input.begin(), it), ' ') << '^' << std::endl;
	}
    }
    return 0;
}
