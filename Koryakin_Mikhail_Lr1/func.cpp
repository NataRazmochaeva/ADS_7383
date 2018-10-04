#include "func.hpp"
/* for function "oper" 
   1 = "or"
   0 = "and"
*/

int oper(istream &files, int op){  //Функция для определения вводимой операции
	char str[10];
	files>>str;
	if (strcmp(str,"and")==0)
		return 0;
	else 
		return 1;
}

bool write(istream &files, bool cur, int flag=0){     //Функция для определения вводимого значение 
		
		char str[10];
		if(files>>str){
			if (strcmp(str,"true")==0){
				cur = true;					
			}
			if (strcmp(str,"false")==0)
				cur = false;
			if (strcmp(str,"not")==0){
				if (!flag)
					flag=1;
				else
					flag=0;
				return write(files, cur, flag);
			}
		}
		if (flag)
			return !cur;
		else
			return cur;
}


bool rec(istream &files, bool cur, int flag){	//Рекурсивная функция для определения результата логического выражения
	if (flag==1){
		cur = write(files, cur);
		return cur;
	}
	if (flag==0){
		cur = write(files, cur);
		int op;
		op = oper(files, op);
		flag=1;
		if (op)
			return (cur || rec(files, cur, flag));
		else
			return (cur && rec(files, cur, flag));
        
	}
}

bool check(string str, bool flag=false, unsigned int k=0){
	while (str[k] == ' ')
		k++;
	if (k<str.length()){
		if(!flag && str.substr(k, str.find(' ', k)-k)=="not")
			flag=check(str, false, k+4);
		else if(!flag && str.substr(k, str.find(' ', k)-k)=="true")
			flag=check(str, true, k+5);
		else if(!flag && str.substr(k, str.find(' ', k)-k)=="false")
			flag=check(str, true, k+6);
		else if(flag && str.substr(k, str.find(' ', k)-k)=="and")
			flag=check(str, false, k+4);
		else if(flag && str.substr(k, str.find(' ', k)-k)=="or")
			flag=check(str, false, k+3);
		else 
			return false;
	}
	return flag;
}


