#include <iostream>
#include <fstream>
#include "queue.hpp"

void rewrite(std::istream &fin, std::ostream &fout){
    Queue<unsigned char> numbers(4), other(10);
    std::string input;
    while(!fin.eof()){
	getline(fin, input);
	for(auto i : input)
	    if(i > '9' || i < '0')
		other.push(i);
	    else
		numbers.push(i);
	while(!other.isEmpty())
	    fout << other.pop();
	while(!numbers.isEmpty())
	    fout << numbers.pop();
	fout << std::endl;
    }
}


int main(){
    std::filebuf ifile, ofile;
    std::string ifilename, ofilename;
    while(true){
	std::cout << "Enter input file name or nothing to exit: "; 
	getline(std::cin, ifilename);
	if(ifilename == "")
	    break;
	if(!ifile.open(ifilename, std::ios::in)){
	    std::cout << "Incorrect file, try again" << std::endl;
	    ifile.close();
	    continue;
	}
	std::cout << "Enter output file name: ";
	getline(std::cin, ofilename);
	if(!ofile.open(ofilename, std::ios::out)){
	    std::cout << "Incorrect file, try again" << std::endl;
	    ifile.close();
	    ofile.close();
	    continue;
	}
	std::istream fin(&ifile);
	std::ostream fout(&ofile);
	rewrite(fin, fout);
	ifile.close();
	ofile.close();
    }
    return 0;
}
