#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;

enum key {
  operation=-2,
  smth_wrong=-1,
};

typedef char base;
struct s_expr;
struct two_ptr {
  s_expr *hd;
  s_expr* tl;
};
struct s_expr {
  bool tag;
  union {
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

  switch (err) {
    case 1: {
      cerr<<"Неверный ввод."<<endl;
      break;}
    case 2: {
      cerr << "Деление на 0" << endl;
      break;}
    case 3: {
      cerr<<"Не хвататет значений, констант или знаков. Проверьте введенные данные и повторите попытку."<<endl;
      break;}
    default:
      break;
  }
}

lisp cons (const lisp h, const lisp t) { //создает список

    lisp p;
    p=new s_expr;
    if (p==NULL) {
        errors(1);
        return NULL;
    }
    else {
        p->tag=false;
        p->node.pair.hd=h;
        p->node.pair.tl=t;
        return p;
    }
}

lisp make_atom(const base x) { //создает атом

  if (x=='+' || x=='-' || x=='*' || x=='/'|| isdigit(x)) {
    lisp s;
    s=new s_expr;
    s->tag=true;
    s->node.atom=x;
    return s;
  }
  else {
    errors(3);
    return NULL;
  }
}

int read_s_expr(string array, int* ptr) { //создает список

  int num=0;
  while (!isspace(array[(*ptr)]) && (*ptr)< array.length())
      (*ptr)++;
  (*ptr)++;
  if ((*ptr) > 2 && isspace(array[(*ptr)-3])) {
    if (isdigit(array[(*ptr)-2]))
      return array[(*ptr)-2];
    else if (array[(*ptr)-2] == '+' || array[(*ptr)-2]=='-' || array[(*ptr)-2]=='*' || array[(*ptr)-2]=='/')
      return operation;
    else return smth_wrong;
  }
  else if ((*ptr) <= 2) {
    if (isdigit(array[(*ptr)-2]))
      return array[(*ptr)-2];
    else if (array[(*ptr)-2] == '+' || array[(*ptr)-2]=='-' || array[(*ptr)-2]=='*' || array[(*ptr)-2]=='/')
      return operation;
    else return smth_wrong;
  }
  else return smth_wrong;
}

void read_lisp(string array, lisp* head, int* ptr) { //создает список

  int num=0;
  num = read_s_expr(array,ptr);
  if (num!=smth_wrong && num!=operation) {
    lisp p11;
    p11 = make_atom(array[(*ptr)-2]);
    int num2, num3;
    num2 = read_s_expr(array, ptr);
    num3 = read_s_expr(array, ptr);
    lisp p12;
    if(num3==smth_wrong || num2==smth_wrong) {
      errors(1);
      return;
    }
    if (num3!=smth_wrong && num3!=operation) {
      lisp p1, p2;
      (*ptr)=(*ptr)-4;
      read_lisp(array, &p1, ptr);
      read_lisp(array, &p2, ptr);
      p12 = cons(p1,p2);
    }
    if (num3==operation) {
      if (num2!=operation && num2!=smth_wrong) {
        lisp p1, p2;
        p1 = make_atom(array[(*ptr)-4]);
        p2 = make_atom(array[(*ptr)-2]);
        p12 = cons(p1,p2);
      }
    }
    (*head) = cons(p11,p12);
  }
  else if(num==operation && (*ptr)!= 0) {
    (*head) = make_atom(array[(*ptr)-2]);
  }
  else {
    errors(1);
    return ;
  }
}

bool write_lisp(lisp head, int i, int j, bool* flag);//выводит список

bool write(lisp head, int i, int j, bool* flag) {//выводит список
  if (head==NULL) {
    cerr<< "Неверный ввод."<<endl;
      return false;
  }
  else if (head->tag==true) {
    cerr<<"Не хвататет значений, констант или знаков. Проверьте введенные данные и повторите попытку."<<endl;
    return false;
  }
  else {
    i++;
    write_lisp(head->node.pair.hd, i, j, flag);
    j++;
    write_lisp(head->node.pair.tl, i, j, flag);
    return true;
  }
}

bool write_lisp (lisp head, int i, int j, bool* flag) {//выводит список

  if (head==NULL) {
    cerr<<"Не хвататет значений, констант или знаков. Проверьте введенные данные и повторите попытку."<<endl;
    return false;
  }
  if (head->tag==true) {
    for (int j=0; j < i; j++) cout<<"   ";
    if (head->node.atom=='+' || head->node.atom=='-' || head->node.atom=='*' || head->node.atom=='/' || (isalpha(head->node.atom))) {
      if (head->node.atom=='/' && (*flag)==true) {
        errors(2);
        return false;
      }
      cout<<head->node.atom<<endl;
    }
    else {
      cout<<head->node.atom<<endl;
      if (head->node.atom == '0')
        (*flag)=true;
      else (*flag)=false;
    }
    return true;
  }
  else write(head,i,j,flag);
}

void destroy(lisp s) {

  if (s!=NULL) {
    if (s->tag==false) {
      destroy (s->node.pair.hd);
      destroy (s->node.pair.tl);
    }
    delete s;
  }
}

Pairs pairs(int n, string str, Pairs pp[]) {//создает пару переменная-константа

  char tmp[2];
  int ptr=0, n1=0, i=0;
  cout<<str<<endl;
  while (str[ptr+1]!=')') {
    pp[i].var=str[ptr+2];
    pp[i].con=str[ptr+4];
    ptr+=5;
    n1++;
    i++;
  }
  if (n>n1) cerr<<"Введено недостаточное количество пар переменная-константа"<<endl; //придумать выход из программы при ошибке
  return *pp;
}

string comp_pair(int n, string array, Pairs pp[]){//заменяет переменную на число в строке

  int i, j=0;
  for (i=0; i<n; i++) {
    while (array[2*i]!=pp[j].var)
      j++;
    array[2*i]=pp[j].con;
  }
  return array;
}

int get_atom(lisp hd) {//получает значение атома и преобразует его в int для вычислений

  char ret[2];
  if (hd->tag) {
    cout<<"Yes!"<<endl;
    if (isdigit(hd->node.atom)) {
      cout<<"digit"<<endl;
      ret[0]=hd->node.atom;
      cout<<"digit1"<<endl;
      ret[1]='\0';
      cout<<"ret: "<<atoi(ret)<<endl;
    }
    if (ispunct(hd->node.atom)){
      cout<<"sign"<<endl;
      return 0;
    }
  }
  else return 0;
  cout<<"get_atom: "<<ret<<endl;
  return atoi(ret);
  /*if(hd!=NULL){
  int a;
  a=(int)(hd->node.atom)-'0';
  std::cout <<"a: "<< a << '\n';
  return a;}
  else
  return 0;*/
}

int calc(lisp head, string sign, int c, int n) {//вычисляет введение значение

  std::cout <<"hd: "<< (head->node.pair.hd)->node.atom << '\n';
  std::cout << "c" <<c<< '\n';
  int ret;
  if (c==n) {
    cout<<"end"<<endl;
    return ret;
  }
  char s=sign[c];
  cout<<s<<endl;
  switch (s) {
    case '+': {
      ret = get_atom(head->node.pair.hd) + calc(head->node.pair.tl, sign, ++c, n);
      return ret;
    }
    case '-': {
      ret = get_atom(head->node.pair.hd) - calc(head->node.pair.tl, sign, ++c, n);
      return ret;
    }
    case '*': {
      ret = get_atom(head->node.pair.hd) * calc(head->node.pair.tl, sign, ++c, n);
      return ret;
    }
    case '/': {
      ret = get_atom(head->node.pair.hd) / calc(head->node.pair.tl, sign, ++c, n);
      if (calc(head->node.pair.tl, sign, ++c, n)==0)
        cerr<<"Деление на 0"<<endl;
        return smth_wrong;
    }
    default: {
      return get_atom(head->node.pair.hd);
    }
  }
}

int count(string array) {//считает количество символов, которе нужно заменить

  int i, k=0;
  for (i=0; i<array.length(); i++)
    if (isalpha(array[i])) k++;
  return k;
}

void process(string array, string str){//обработка данных


  lisp head=NULL;
  bool flag;
  int ptr=0, i=0, j=0, c=0, k=0, ans, n;
  Pairs pp[30];
  string sign;
  n = count(array);
  *pp = pairs(n, str, pp);
  array = comp_pair(n, array, pp);
  for (k=0; k<array.length(); k++)
    if (ispunct(array[k]))
      sign.push_back(array[k]);
  read_lisp(array, &head, &ptr);
  if (head==NULL)
    cerr<<"Файл пуст."<<endl;
  if (write(head,i,j,&flag) && flag==false)
    cout<< "Корректный ввод."<<endl;
  cout<<"Ответ: "<<calc(head, sign, c, n)<<endl;
  destroy(head);
}

int main() {

  int num=0;
  while (num != 3) {
    cout<<"Выберите дальнейшие действия:"<<endl;
    cout<<"1 - Ввести выражение вручную."<<endl;
    cout<<"2 - Считать выражение из файла test.txt."<<endl;
    cout<<"3 - Завершить работу."<<endl;
    cin>>num;

    switch (num) {
      case 1: {
        getchar();
        string array, str;
        getline(cin,array);
        getline(cin, str);
        process(array, str);
        break;
      }
      case 2: {
        string array, str;
        ifstream infile("test1.txt");
        getline(infile, array);
        array=array+'\n';
        getline(infile, str);
        process(array, str);
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
