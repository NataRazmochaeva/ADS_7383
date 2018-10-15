#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;

typedef char* base;      // базовый тип элементов (атомов)

struct s_expr {

    bool tag; // true: atom, false: pair
    union {
        base atom;
        struct two_ptr {

            s_expr *hd;
            s_expr *tl;
        } pair;
    } node;
};

typedef s_expr *lisp;

lisp head(const lisp s);
lisp tail(const lisp s);
lisp cons(const lisp h, const lisp t);
lisp make_atom(const base x);
bool isAtom(const lisp s);
bool isNull(const lisp s);
void destroy(lisp s);
string lisp_to_string(const lisp x);
string seq_to_string(const lisp x);
void read_lisp(lisp &y, istringstream &ss);
void read_s_expr(char prev, lisp &y, istringstream &ss);
void read_seq(lisp& y, istringstream &ss);
bool isEqual_lisp(const lisp f, const lisp s);
bool isEqual_seg(const lisp f, const lisp s);

lisp make_atom(const base x) {

    lisp s;
    s = new s_expr;
    s->tag = true;
    s->node.atom = x;
    return s;
}

bool isAtom(const lisp s) {

    if (s == NULL) {
        return false;
    } else {
        return (s->tag);
    }
}

bool isNull(const lisp s) {

    return s == NULL;
}


lisp head(const lisp s) { // PreCondition: not null (s)

    if (s != NULL) {

        if (!isAtom(s)) {

            return s->node.pair.hd;
        }
        else {

            cerr << "Error: Head(atom) \n";
            exit(1);
        }
    } else {
        cerr << "Error: Head(nil) \n";
        exit(1);
    }
}

lisp tail(const lisp s) {// PreCondition: not null (s)

    if (s != NULL) {

        if (!isAtom(s)) {

            return s->node.pair.tl;
        } else {

            exit(1);
        }
    } else {

        exit(1);
    }
}

lisp cons(const lisp h, const lisp t) { // PreCondition: not isAtom (t)

    lisp p;

    if (isAtom(t)) {

        exit(1);
    } else {

        p = new s_expr;

        if (p == NULL) {

            exit(1);
        } else {

            p->tag = false;
            p->node.pair.hd = h;
            p->node.pair.tl = t;
            return p;
        }
    }
}

void destroy(lisp s) {

    if (s != NULL) {

        if (!isAtom(s)) {

            destroy(head(s));
            destroy(tail(s));
        }
        delete s;
    }
}

void read_lisp(lisp& y, istringstream &ss) {

    char x;
    do {

        ss >> x;
    } while (x == ' ');

    read_s_expr(x, y, ss);
}

void read_s_expr(char prev, lisp& y, istringstream &ss) {

    int i = 0;
    char ch = prev;
    streampos oldpos;
    base str = (base)calloc(30, sizeof(char));
    if (prev == ')') {
        exit(1);
    } else if (prev != '(') {
        while (ch != ' ' && ch != ')') {
            str[i] = ch;
            i++;
            oldpos = ss.tellg();
            ch = ss.get();
        }
        if (ch == ')') {
           ss.seekg(oldpos);
        }
        y = make_atom(str);
    } else {
        read_seq(y, ss);
    }
}


void read_seq(lisp& y, istringstream &ss) {

    char x;
    lisp p1, p2;
    if (!(ss >> x)) {
        exit(1);
    } else {
        while (x == ' ') {
            ss >> x;
        }
        if (x == ')') {
            y = NULL;
        } else {
                read_s_expr(x, p1, ss);
                read_seq(p2, ss);
                y = cons(p1, p2);
        }
    }
}



string lisp_to_string(const lisp x) {//пустой список выводится как ()

    string str;
    if (isNull(x)) {
        str += "()";
    }
    else if (isAtom(x)) {
        str += x->node.atom;
        str += " ";
    } else { //непустой список}
        str +=  "( ";
        str += seq_to_string(x);
        str += ") ";
    }
    return str;
}


string seq_to_string(const lisp x) {//выводит последовательность элементов списка без обрамляющих его скобок
    if (!isNull(x)) {
        return lisp_to_string(head(x)) + seq_to_string(tail(x));
    }
    return "";
}

base getAtom(const lisp s) {

    if (!isAtom(s)) {
        exit(1);
    } else {
        return (s->node.atom);
    }
}

bool isEqual_lisp(const lisp f, const lisp s) {

    if (isNull(f) && isNull(s)) {
        return true;
    } else if (isAtom(f) && isAtom(s)) {
            return true;
    } else {
        return isEqual_seg(f, s);
    }
    return false;
}

bool isEqual_seg(const lisp f, const lisp s) {

    if (!isNull(f) && !isNull(s)) {
        return isEqual_lisp(head(f), head (s)) && isEqual_seg(tail(f), tail(s));
    }
    return isNull(f) && isNull(s);
}

int print(bool result, int sw_var){
  if(result)
      cout << "True. These are structurally identical lists.\n";
  else
      cout << "False. These are not structurally identical lists.\n";
  return sw_var = 4;
}

 int main() {

    lisp* s = new lisp;
    lisp* f = new lisp;
    string str1, str2;
    int sw_var;
    string file_name;
    fstream file;
    cout << "Menu"<< '\n';
    cout << "0-exit from the program"<< '\n';
    cout << "1-input a string from the keyboard"<< '\n';
    cout << "2-input a line from a file" << '\n';
    cin >> sw_var;
    cin.ignore();
    while(sw_var)
    {
        switch(sw_var)
        {
        case 1: {
            cout << "Enter the first line :"<< '\n';
            cin >> str1;
            istringstream ss1(str1);
            read_lisp(*f, ss1);
            cout << "Enter the second line :"<< '\n';
            cin >> str2;
            istringstream ss2(str2);
            read_lisp(*s, ss2);
            sw_var=print(isEqual_lisp(*f, *s), sw_var); }
            break;
        case 2:{
            cout << "Enter the name of the file:"<< '\n';
            cin >> file_name;
            cin.ignore();
            file.open(file_name, fstream::in);
            if(!file.is_open()){
                cout << "Error opening file.\n";
                sw_var = 4;
              }
            else{
                getline(file, str1);
                istringstream ss1(str1);
                read_lisp(*f, ss1);
                getline(file, str2);
                istringstream ss2(str2);
                read_lisp(*s, ss2);
                sw_var=print( isEqual_lisp(*f, *s), sw_var);
                file.close();
              }}
            break;
        case 0:
            break;
        default: {
            cout << "Enter again.\n";
            cin >> sw_var;
            cin.ignore();}
            break;
        }
    }
    return 0;
  }
