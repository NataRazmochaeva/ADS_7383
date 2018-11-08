

#include <cstdio>
#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;

void read(Stack &s,std::ifstream &in, std::ofstream &out){
    char c;
    while ((c = in.get()) != '\n' && c!=EOF)
        s.push(c);
}

void write(Stack &s, std::ofstream &out){
    while (!s.isNull())
        out << s.pop2();
    out<<endl;
}

int main(){
	string file_name;
  string out_file_name;
  ifstream fin;
  ofstream fout;
  int ch;
  bool ex = true;
  Stack  s;
	while(ex){
    cout << "0-exit from the program" << '\n';
    cout << "1-input a line from a file" << '\n';
    cin>>ch;
    cin.ignore();
		switch (ch)
		{
	     case 1:{ cout << "Enter the name of the input file:" << '\n';
	      cin >> file_name;
        cin.ignore();
        cout << "Enter the name of the output file:" << '\n';
        cin >> out_file_name;
        cin.ignore();
        fin.open(file_name, ifstream::in);
        fout.open(out_file_name, ofstream::out);
        if (!fin.is_open() || !fout.is_open()) {
          cout << "Error opening file.\n";
        }
        else {
          while (!fin.eof()){
            read(s,fin,fout);
            write(s, fout);
          }
        }
        break;
      }
      case 0: {
        ex = false;
        break;
      }
      default:{
        ex = false;
        cout << "Error of input!";
        break;
      }
    }
  }
    fin.close();
    fout.close();
    return 0;
}
