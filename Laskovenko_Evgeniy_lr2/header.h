#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <sstream>

//Namespace:
using namespace std;

//Types definition:
typedef char base;

//Signatures of functions:
class Pair* set_right_list(istream& is_str, Pair* c_pair, base prev_ch='\0');
bool syn_analyzer(string str, unsigned int i=0, unsigned int opened_br=0, bool flag=false);
class Pair* set_list(istream& is_str, bool st_flag=true);
void cout_list(class Pair* head);
class Atoms* diff_atoms(class Pair* head, class Atoms* h_res, class Atoms* c_res);
void cout_diff_list(class Atoms* head);

#endif
