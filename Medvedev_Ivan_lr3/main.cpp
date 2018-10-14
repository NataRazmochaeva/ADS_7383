#include <iostream>
#include <cstring>
#include <fstream>
#include <cctype>
#include "prefix.hpp"

using namespace std;


int prioritet(char ch){
    switch(ch){
        case '+': case'-':{
            return 1;
        }
        case '*': case '/':{
            return 2;
        }
        case '^':{
             return 3;
        }
    default:{
        return 0;
    }

    }
}

bool isOperation(char x){
    if (x == '^' || x == '*' || x == '/' || x == '+' || x == '-')
        return true;
    return false;
}


int main(){ 
        int i = 0;
        const char space = ' ';
        string ans;
        string infix;
        Stack <char> operations;
        ifstream infile("infix.txt");
        getline(infile, infix);
        if(!isalpha(infix[i]) && !isdigit(infix[i]) && infix[i] != '('){
            cout<<"Неверное инфиксное выражение - первый символ не переменная и не число"<<endl;
            return 0;
        }
       // infile.close();
        i = infix.length() - 1;
        if(!isalpha(infix[i]) && !isdigit(infix[i]) && infix[i] != ')'){
            cout<<"Неверное инфиксное выражение - операция в конце строки"<<endl;
            return 0;
        }
        while (i >= 0){

            if(isalpha(infix[i]) || isdigit(infix[i])){
                ans.insert(0, 1, infix[i]);
                if(!isalpha(infix[i-1]) && !(isdigit(infix[i-1])))
                     ans.insert(0, 1, space);

            }
            else if (isOperation(infix[i])){
                if (isOperation(infix[i-1])){
                    cout<<"Неверное инфиксное выражение - два знака подряд"<<endl;
                    return 0;
                }
                if(!operations.Size())
                    operations.push(infix[i]);
                else{
                    while(prioritet(infix[i]) <= prioritet(operations.Top()) && operations.Size()){
                        ans.insert(0, 1, operations.pop());
                        ans.insert(0, 1, space);
                    }
                    operations.push(infix[i]);
                }

            }
          else if(infix[i] ==')'){
                operations.push(infix[i]);
            }
          else if(infix[i] =='('){
               while (prioritet(operations.Top())){

                  ans.insert(0, 1, operations.pop());
                  ans.insert(0, 1, space);

               }
               if (operations.Top() != ')'){
                   cout<<"Нет закрывающей скобки!";
                   return 0;
               }
               operations.pop();
            }


            else{
                cout<<"Лишние символы"<<endl;
                return 0;
            }
            i--;
        }
        while(operations.Size()){
            ans.insert(0, 1, operations.pop());
            ans.insert(0, 1, space);
        }
        ofstream out("prefix.txt");
        out<<ans;
        cout<<"Выражение записано в префиксном форме"<<endl;
        out.close();
        ans.clear();
        infix.clear();
        return 0;


}
