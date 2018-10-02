#include <iostream>
#include <fstream>
#include "bin_rocker.hpp"


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
            Bin_rocker rocker(it);
	    std::cout << "Short form:" << std::endl;
            std::cout << rocker.to_str() << std::endl;
            std::cout << "Number of weights: " << rocker.numbers() << std::endl;
	}
	catch(std::exception &e){
	    std::cout << e.what() << ":" << std::endl;
	    std::cout << input << std::endl;
	    std::cout << std::string(distance(input.begin(), it), ' ') << '^' << std::endl;
	}
    }
    return 0;
}
