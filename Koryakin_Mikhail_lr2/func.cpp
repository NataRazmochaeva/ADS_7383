#include "func.hpp"

void starter(istream &is){
    lisp s1;
    read_lisp (s1, is);
    cout << "Считан Иерархический список: " << endl;
    write_lisp (s1);
    cout<<endl;
    s1 = linelist (s1);
    cout << "Сформирован линейный список: " << endl;
    write_lisp (s1);
    cout << endl;
    cout << "Элементов в списке: " <<evade(s1)<<endl;
    cout << "destroy list: " << endl;
    del(s1);
}



int evade(lisp& sp){
    if (sp->node.pair.hd != nullptr){
        if (isAtom(sp->node.pair.hd)){
            if (sp->node.pair.tl != nullptr)
                return 1+evade(sp->node.pair.tl);
            else
                return 1;
        }
        else{
            if (sp->node.pair.tl != nullptr)
                return evade(sp->node.pair.tl)+evade(sp->node.pair.hd);
            else
                return 0;
        }
     }
}


lisp head (const lisp s){// PreCondition: not null (s)
    if (s != nullptr)
        if (!isAtom(s))
            return s->node.pair.hd;
        else {
            throw invalid_argument("Error: Head(atom) \n");
        }
    else {
        throw invalid_argument("Error: Head(nil) \n");
    }
}
//.......................................
bool isAtom (const lisp s){
    if(s == nullptr)
        return false;
    else
        return (s -> tag);
}
//.......................................
bool isNull (const lisp s){
    return s==nullptr;
}
//.......................................
lisp tail (const lisp s){// PreCondition: not null (s)
    if (s != nullptr)
        if (!isAtom(s))
            return s->node.pair.tl;
        else {
            throw invalid_argument("Error: Tail(atom) \n");
        }
    else {
        throw invalid_argument("Error: Tail(nil) \n");
    }
}
//.......................................
lisp cons (const lisp h, const lisp t){
// PreCondition: not isAtom (t)
    lisp p;
    if (isAtom(t)) {
        throw invalid_argument("Error: Cons(*, atom)\n");
    }
    else {
        p = new s_expr;
        if ( p == nullptr) {
            throw invalid_argument("Memory not enough\n");
        }
        else {
            p->tag = false;
            p->node.pair.hd = h;
            p->node.pair.tl = t;
            return p;
        }
    }
}
//...........................

lisp make_atom (const base x){
    lisp s;
    s = new s_expr;
    s -> tag = true;
    s->node.atom = x;
    return s;
}
//...........................
void del (lisp s){
    if ( s != nullptr) {
        if (!isAtom(s)){
            del ( head (s));
            del ( tail(s));
        }
    delete s;
    //s = NULL;
    }
}
//...........................
base getAtom (const lisp s){
    if (!isAtom(s)) {
        throw invalid_argument("Error: getAtom(s) for !isAtom(s) \n");
    }
    else
        return (s->node.atom);
}
//...........................
// ввод списка с консоли
void read_lisp ( lisp& y, istream &is_str){
    base x;

    do{
        is_str >> x;
    }while (x==' ');
    //cout<<x<<endl;
    int counter=0;
    read_s_expr ( x, y, is_str);
} //end read_lisp
//...........................
void read_s_expr (base prev, lisp& y, istream &is_str){ //prev － ранее прочитанный символ}
    if ( prev == ')' ) {
        throw invalid_argument(" ! List.Error 1 - нет открывающей скобки");
    }
    else if ( prev != '(' ){
        y = make_atom (prev);
    }
    else
        read_seq (y, is_str);
} //end read_s_expr
//...........................
void read_seq ( lisp& y, istream &is_str){
    base x;
    lisp p1, p2;
    if (!(is_str >> x)) {
        throw invalid_argument(" ! List.Error 2 - нет закрывающей скобки " );
    }
    else {
        while ( x==' ' ){
            is_str >> x;
        }

        if ( x == ')' )
            y = nullptr;
        else {
            read_s_expr ( x, p1, is_str);
            read_seq ( p2, is_str);
            y = cons (p1, p2);
        }
    }
} //end read_seq
//...........................
// Процедура вывода списка с обрамляющими его скобками － write_lisp,
// а без обрамляющих скобок － write_seq
void write_lisp (const lisp x){//пустой список выводится как ()
    if (isNull(x))
        cout << " ( )";
    else if (isAtom(x)){
        cout << ' ' << x->node.atom;
    }
    else { //непустой список}
        cout << " (" ;
        write_seq(x);
        cout << " )";
    }
} // end write_lisp
//...........................
void write_seq (const lisp x){//выводит последовательность элементов списка без обрамляющих его скобок
    if (!isNull(x)) {
        write_lisp(head (x));
        write_seq(tail (x));
    }
}

//...........................
lisp copy_lisp (const lisp x){
    if (isNull(x))
        return nullptr;
    else if (isAtom(x))
        return make_atom (x->node.atom);
    else
        return cons (copy_lisp (head (x)), copy_lisp (tail(x)));
}

lisp linelist(const lisp s){
    if (isNull(s))
        return nullptr;
    else if(isAtom(s))
        return cons(make_atom(getAtom(s)),nullptr);
    else if (isAtom(head(s)))
        return cons( make_atom(getAtom(head(s))),linelist(tail(s)));
    else //Not Atom(Head(s))
        return concat(linelist(head(s)),linelist(tail(s)));
}

lisp concat (const lisp y, const lisp z){
    if (isNull(y))
        return copy_lisp(z);
    else
        return cons (copy_lisp(head (y)), concat (tail (y), z));
}

