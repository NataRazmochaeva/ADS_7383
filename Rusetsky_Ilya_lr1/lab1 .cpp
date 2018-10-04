#include<iostream>
#include<cstring>
#include<fstream>
#define MAX_LENGTH 1000

using namespace std;

void strtok_(char *str);
void keyboard_input();
void file_input();
void Interface();

int main(){
Interface();
int number=0;
cin>>number;
 while(number){
  switch(number){
  case 1:
   keyboard_input();
   cout<<endl;
   Interface();
   cin>>number;
   break;
  case 2:
   file_input();
   cout<<endl;
   Interface();
   cin>>number;
   break;
  default:
  int a=3;
  if(number==a)return 0;
   cout<<"Неверно введены данные!"<<endl;
   Interface();
   cin>>number;
  }
 }
return 0;
}

void strtok_(char *str){
char *istr=str;
if((str=strtok(istr,"/"))!=NULL){
 strtok_(NULL);
 cout<<str;
 }
}

void keyboard_input(){
char str[MAX_LENGTH];
cout<<"Введите строку:"<<endl;
cin>>str;
strtok_(str);
}

void file_input(){
string filename;
char str[MAX_LENGTH];
cout<<"Имя файла:"<<endl;
cin>>filename;
ifstream file;
file.open(filename.c_str());
 if(!file){
 cout<<"Нет такого файла!"<<endl;
 return;
 }
 else{
 cout<<"Есть такой файл!"<<endl;
 file.getline(str,MAX_LENGTH);
 }
cout<<str<<endl;
strtok_(str);
file.close();
}

void Interface(){
 cout<<"Выберите действие: "<<endl;
 cout<<"1:Ввод с клавиатуры"<<endl;
 cout<<"2:Вывод из файла"<<endl;
 cout<<"3:Выход"<<endl;
}


