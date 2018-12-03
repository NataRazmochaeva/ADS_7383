#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstring>

using namespace std;

enum key{
    op_found =   -2,
    smth_wrong = -1,
};

typedef char base;
struct s_expr;
struct two_ptr{
    s_expr *hd;
    s_expr* tl;
};
struct s_expr{
    bool tag;
    union{
        base atom;
        two_ptr pair;
    }node;
};
typedef s_expr* lisp;

struct pairs {//пара переменная-константа
    char var;
    char con;
};
typedef pairs Pairs;

void errors(int err) {
    switch(err) {
        case 1:
            cerr<<"Неверный ввод."<<endl;
            break;
        case 2:
            cerr<<"Деление на нуль."<<endl;
            break;
        case 3:
            cerr<<"Не хвататет значений, констант или знаков. Проверьте введенные данные и повторите попытку."<<endl;
            break;
        case 4:
            cerr << "Неверный ввод."<<endl;
            break;
        default:
            break;
    }
}

lisp cons (const lisp h, const lisp t){
    lisp p;
    p = new s_expr;
    if ( p == NULL) {
        errors(4);
        return NULL;
    }else {
        p->tag = false;
        p->node.pair.hd = h;
        p->node.pair.tl = t;
        return p;
    }
}

lisp make_char_atom (const base x) {
    if(x=='+' || x=='-' || x=='*' || x=='/' || isalpha(x) || isdigit(x)){
        lisp s;
        s = new s_expr;
        s -> tag = true;
        s->node.atom = x;
        return s;
    }else{
        errors(3);
        return NULL;
    }
}

int read_s_expr(string array,int* ptr){
    int num=0;
    while(!isspace(array[(*ptr)]) && (*ptr)< array.length()){
        (*ptr)++;
    }
    (*ptr)++;
    if((*ptr) > 2 && isspace(array[(*ptr)-3])){
        if(isdigit(array[(*ptr)-2]) || isalpha(array[(*ptr)-2]))
            return array[(*ptr)-2];
        else if(array[(*ptr)-2] == '+' || array[(*ptr)-2]=='-' ||
                array[(*ptr)-2]=='*' || array[(*ptr)-2]=='/')
            return op_found;
        else
            return smth_wrong;
    }else if((*ptr) <= 2){
        if(isdigit(array[(*ptr)-2]) || isalpha(array[(*ptr)-2]))
            return array[(*ptr)-2];
        else if(array[(*ptr)-2] == '+' || array[(*ptr)-2]=='-' ||
                array[(*ptr)-2]=='*' || array[(*ptr)-2]=='/')
            return op_found;
        else
            return smth_wrong;
    }else
        return smth_wrong;
}

void read_lisp(string array,lisp* head,int* ptr){
    int num=0;
    num=read_s_expr(array,ptr);
    if(num!=smth_wrong && num!=op_found){
        lisp p11;
        p11=make_char_atom(array[(*ptr)-2]);
        int num2,num3;
        num2=read_s_expr(array,ptr);
        num3=read_s_expr(array,ptr);
        lisp p12;
        if(num3==smth_wrong || num2==smth_wrong){
            errors(1);
            return;
        }
        if(num3!=smth_wrong && num3!=op_found){
            lisp p1,p2;
            (*ptr)=(*ptr)-4;
            read_lisp(array,&p1,ptr);
            read_lisp(array,&p2,ptr);
            p12=cons(p1,p2);
        }
        if(num3==op_found){
            if(num2!=op_found && num2!=smth_wrong){
                lisp p1,p2;
                p1=make_char_atom(array[(*ptr)-4]);
                p2=make_char_atom(array[(*ptr)-2]);
                p12=cons(p1,p2);
            }
        }
        (*head)=cons(p11,p12);
    }else if(num==op_found && (*ptr)!= 0){
        (*head)=make_char_atom(array[(*ptr)-2]);
    }else{
        errors(1);
        return ;
    }
}

bool write_lisp(lisp head, int i,int j,bool* flag);

bool write(lisp head,int i,int j,bool* flag){
    if(head==NULL){
        cerr<< "Неверный ввод."<<endl;
        return false;
    }else if(head->tag==true){
        cerr<<"Не хвататет значений, констант или знаков. Проверьте введенные данные и повторите попытку."<<endl;
        return false;
    }else{
        i++;
        write_lisp(head->node.pair.hd,i,j,flag);
        j++;
        write_lisp(head->node.pair.tl,i,j,flag);
        return true;
    }
}

bool write_lisp(lisp head, int i,int j,bool* flag){
    if(head==NULL){
        cerr<<"Не хвататет значений, констант или знаков. Проверьте введенные данные и повторите попытку."<<endl;
        return false;
    }
    if(head->tag==true){
        for(int j=0;j< i;j++)
            cout<<'\t';
        if(head->node.atom=='+' || head->node.atom=='-' || head->node.atom=='*'
           || head->node.atom=='/' || (isalpha(head->node.atom))){
            if(head->node.atom=='/' && (*flag)==true){
                errors(2);
                return false;
            }
            cout<<head->node.atom<<endl;
        }else{
            cout<<head->node.atom<<endl;
            if(head->node.atom == '0')
                (*flag)=true;
            else
                (*flag)=false;
        }
        return true;
    }else{
        write(head,i,j,flag);
    }
}

int count(string array) {//считает количество символов, которе нужно заменить

  unsigned int i, k=0;
  for (i=0; i<array.length(); i++)
    if (isalpha(array[i])) k++;
  return k;
}

void destroy (lisp s) {
    if ( s != NULL) {
        if (s->tag == false){
            destroy ( s->node.pair.hd);
            destroy ( s->node.pair.tl);
        }
        delete s;
    };
}

float eval(string str,int &i)
{
    float x = 0.0;
    while (str[i]==' ') i--;

    if (str[i] == '+')
    {
        i--;
        return eval(str,i)+eval(str,i);
    }

    if (str[i] == '*')
    {
        i--;
        return eval(str,i)*eval(str,i);
    }

    if (str[i] == '/')
    {
        i--;
        return 1.0/(eval(str,i)/eval(str,i));
    }

    if (str[i] == '-')
    {
        i--;
        return -1*(eval(str,i)-eval(str,i));
    }
    int w=1;//"вес" очередной цифры
    while((str[i] >= '0') && (str[i] <= '9')){
        x = x + (str[i--] - '0')*w;
        w*=10;
    }
    return x;
}

Pairs pairs(int n, string str, Pairs pp[],int &Err) {//создает пару переменная-константа
  int ptr=2, i=0;
  while (str[ptr] != '\0') {
      if (!isspace(str[ptr]) && str[ptr] != '(' && str[ptr] != ')'){
          pp[i].var=str[ptr];
          pp[i].con=str[ptr+2];
          ptr+=3;
          i+=1;
      }
    ptr+=1;
  }
  if (n>i){
      cerr<<"Malo par"<<endl; //придумать выход из программы при ошибке
      Err = 1;
  }
  return *pp;
}

string comp_pair(int n, string array, Pairs pp[]){//заменяет переменную на число в строке

  int i, j=0;
  for (i=0; i<n; i++) {
    while (array[2*i]!=pp[j].var)
      j++;
    array[2*i]=pp[j].con;
    j = 0;
  }
  return array;
}

int main(){
    int num=0;
    while(num != 3){
        cout << "Выберите дальнейшие действия и введите цифру:"<<endl;
        cout << "1. Ввести выражение вручную."<<endl;
        cout << "2. Считать выражение из файла test1.txt."<<endl;
        cout << "3. Завершить работу."<<endl;
        cin >> num;
        switch(num){
            case 1:{
                getchar();
                string array, str;
                getline(cin,array);
                getline(cin,str);
                lisp head=NULL;
                bool flag;
                flag=false;
                int ptr=0,i=0,j=0,Err=0;
                Pairs pp[26];
                read_lisp(array,&head,&ptr);
                if(head!=NULL && ptr==array.length()+1)
                    if(write(head,i,j,&flag) && flag==false)
                        cout<< "Корректный ввод."<<endl;
                if(head!=NULL && ptr< array.length()+1)
                    cerr<<"Неверный ввод."<<endl;
                int len = array.size()-1;
                int n = count(array);
                *pp = pairs(n, str, pp,Err);
                for(int i =0; i < n; i++){
                  cout<<"[" << pp[i].var << " " << pp[i].con << "]" << endl;
                }
                array = comp_pair(n, array, pp);
                float x = eval(array,len);
                cout << x << endl;
                destroy(head);
                break;
            }
            case 2:{
                getchar();
                string array, str;
                ifstream infile("test.txt");
                getline(infile,array);
                getline(infile,str);
                infile.close();
                lisp head=NULL;
                bool flag;
                flag = false;
                int ptr=0,i=0,j=0,Err=0;
                Pairs pp[26];
                read_lisp(array,&head,&ptr);
                if(head!=NULL && ptr==array.length()+1)
                    if(write(head,i,j,&flag) && flag==false)
                        cout<< "Корректный ввод."<<endl;
                if(head!=NULL && ptr< array.length()+1)
                    cerr<<"Неверный ввод."<<endl;
                int len = array.size()-1;
                int n = count(array);
                *pp = pairs(n, str, pp,Err);
                for(int i =0; i < n; i++){
                  cout<<"[" << pp[i].var << " " << pp[i].con << "]" << endl;
                }
                array = comp_pair(n, array, pp);
                float x = eval(array,len);
                cout << x << endl;
                destroy(head);
                break;
            }
            case 3:
                return 0;
            default:
                cerr << "Проверьте введенные данные и повторите попытку." << endl;
                break;
        }
    }
    return 0;
}
