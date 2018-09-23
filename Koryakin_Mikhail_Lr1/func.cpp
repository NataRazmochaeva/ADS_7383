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

bool write(istream &files, bool cur){     //Функция для определения вводимого значение 
		
		char str[10];
		if(files>>str){
			if (strcmp(str,"true")==0){
				cur = true;					
			}
			if (strcmp(str,"false")==0)
				cur = false;
			if (strcmp(str,"not")==0){
				files>>str;
				if (strcmp(str,"true")==0)
					cur = false;
				if (strcmp(str,"false")==0)
					cur = true;
			}
		}
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
