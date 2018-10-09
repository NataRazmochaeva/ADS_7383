#include<iostream>
#include<cstring>
#include<fstream>
#define MAX_LENGTH 1000

using namespace std;

int func(char str,char *delim);
char *strtok_1(char *str,char *delim,char **mem);
void strtok_(char *str,char **mem);
void keyboard_input(char **mem);
void file_input(char **mem);
void Interface();


int main(){
Interface();
int number=0;
char *mem=0;
cin>>number;
 while(number){
  switch(number){
  case 1:
   keyboard_input(&mem);
   cout<<endl;
   Interface();
   cin>>number;
   break;
  case 2:
   file_input(&mem);
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

int func(char str,char *delim){
int i=0;
 for(;i<strlen(delim);i++)
 {
 if(str==delim[i])
  return 1;
 if(str=='\0')
  return 2;
 }
return 0;
}



char *strtok_1(char* str,char *delim,char **mem){
char *pch=*mem;
int i=0;
 if(str!=NULL){
 *mem=str;
 pch=*mem;
 }
 if(*mem==NULL)
 return NULL;
 while(func(*pch,delim)==0)
 pch++;
i=func(*pch,delim);
*pch='\0';
pch++;
swap(pch,*mem);
 if(i==2)
 *mem= NULL;
return pch;
}


void strtok_(char *str,char **mem){
char *pch=str;
 if((pch=strtok_1(str,(char*)"/",mem))!=NULL){
 strtok_(NULL,mem);
 cout<<pch;
 }
}

void keyboard_input(char **mem){
char str[MAX_LENGTH];
cout<<"Введите строку:"<<endl;
cin>>str;
strtok_(str,mem);
}

void file_input(char **mem){
string filename;
char str[MAX_LENGTH];
cout<<"Имя файла:"<<endl;
cin>>filename;
ifstream file;
file.open(filename.c_str());
 if(!file){
 cout<<"Нет такого файла!"<<endl;
 }
 else{
 cout<<"Есть такой файл!"<<endl;
 file.getline(str,MAX_LENGTH);
 }
cout<<str<<endl;
strtok_(str,mem);
file.close();
}

void Interface(){
 cout<<"Выберите действие: "<<endl;
 cout<<"1:Ввод с клавиатуры"<<endl;
 cout<<"2:Вывод из файла"<<endl;
 cout<<"3:Выход"<<endl;
}


