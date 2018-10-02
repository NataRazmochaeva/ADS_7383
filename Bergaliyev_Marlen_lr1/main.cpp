#include <iostream>
#include <unordered_map>
#include <fstream>
#include "relatives.hpp"


auto input_parser(std::istream& inpstream){
    std::string input;
    std::string parent;
    std::string child;
    std::set<std::string> children;
    std::unordered_map<std::string, std::set<std::string>> result;
    int n = 0;
    getline(inpstream, input);
    n = std::stoi(input);
    for(int i = 0; i < n; ++i){
	children.clear();
	parent.clear();
	child.clear();
        getline(inpstream, input);
	std::string::iterator s;
        for(s = input.begin(); s != input.end() && *s != ':';  ++s)
	    if(*s != ' ')
		parent.push_back(*s);
	if(*s == ':')
	    ++s;
	for(; s != input.end(); ++s){
	    if(*s == ' '){
		if(child != "")
		    children.insert(child);
		child.clear();
	    }else
		child.push_back(*s);
	}
	if(child != std::string())
	    children.insert(child);
	result.insert(std::make_pair(parent, children));
    }
    return result;
}


int main(){
    std::string command;
    std::filebuf file;
    std::string filename;
    std::unordered_map<std::string, std::set<std::string>> input;
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
		try{
		    input = input_parser(std::cin);
		}
		catch(std::exception& e){
		    std::cout << "Invalid input" << std::endl;
		    continue;
		}
		break;
	    }
	    case 1:{
		std::cout << "Enter file name: ";
		getline(std::cin, filename);
		if(file.open(filename, std::ios::in)){
		    std::istream fin(&file);
		    try{
		    	input = input_parser(fin);
		    }
		    catch(std::exception& e){
			std::cout << "Invalid file input" << std::endl;
			continue;
		    }
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
	auto result = couple_relatives(input);
    for(auto i : result)
	    std::cout << std::get<0>(i) << " " << std::get<1>(i) << std::endl;
    std::cout << result.size() << std::endl;
    }
    return 0;
}
