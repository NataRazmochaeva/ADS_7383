#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <exception>
#include <windows.h>

using namespace std ;

typedef char base;
    class node {
    public:
        base info;
        node *lt;
        node *rt;
            // constructor
            node () {
                lt = nullptr;
                rt = nullptr;
            }
    };
    typedef node *binTree; // "представитель" бинарного дерева
    binTree Create(void);
    bool isnullptr(binTree);
    base RootBT (binTree); // для непустого бин.дерева
    binTree Left (binTree);// для непустого бин.дерева
    binTree Right (binTree);// для непустого бин.дерева
    binTree ConsBT(const base &x, const binTree &lst,  const binTree &rst);
    void destroy (binTree&);

    typedef binTree Form;
    Form readForm(std::istream &in);
    void writeForm(std::ostream &out, const Form f);
    Form deriviate(const Form f, char var);


    binTree Create()
    {
        return nullptr;
    }

    bool isnullptr(binTree b)
    {
        return (b == nullptr);
    }

    base RootBT (binTree b)                     // для непустого бин.дерева
    {   if (b == nullptr) { cerr << "Error: RootBT(nullptr) \n"; exit(1); }
        else return b->info;
    }

    binTree Left (binTree b)            // для непустого бин.дерева
    {   if (b == nullptr) { cerr << "Error: Left(nullptr) \n"; exit(1); }
        else return b ->lt;
    }

    binTree Right (binTree b)           // для непустого бин.дерева
    {   if (b == nullptr) { cerr << "Error: Right(nullptr) \n"; exit(1); }
        else return b->rt;
    }

    binTree ConsBT(const base &x, const binTree &lst, const binTree &rst)
    {   binTree p;
        p = new node;
        if ( p != nullptr) {
            p ->info = x;
            p ->lt = lst;
            p ->rt = rst;
            return p;
        }
        else {cerr << "Memory not enough\n"; exit(1);}
    }
//-------------------------------------
    node* Delete(node* p){
        if (left)
            delete p->lt;
        if (right)
            delete p->rt;
        delete p;
        return p = NULL;
    }

    bool isSign(char c){
        return c=='+'||c=='-'||c=='*';
    }
    bool isTerminal(char c){
        return isdigit(c)||(c>='a'&&c<='z');
    }
    Form readForm(istream &in){
        if(isTerminal(in.peek())){
            return ConsBT(in.get(),nullptr,nullptr);
        }
        if(in.peek()=='('){
            in.get();
            Form b=readForm(in);
            if(!isSign(in.peek()))throw "expected sigh\n";
            char s=in.get();
            b=ConsBT(s,b,readForm(in));
            if(in.peek()!=')')throw "expected ')'";
            in.get();
            return b;
        }
        throw "expected term or '('\n";
    }
    void writeForm(ostream &out, const Form f){
        if(isnullptr(f))throw "Error, empty formula\n";
        if(isnullptr(Right(f))&&isnullptr(Left(f))){
            out<<RootBT(f);
            return;
        }
        if(isnullptr(Right(f))||isnullptr(Left(f)))
            throw "Knot should have Left and Right\n";
        out<<'(';
        writeForm(out,Left(f));
        out<<RootBT(f);
        writeForm(out,Right(f));
        out<<')';
    }

    Form deriviate(const Form f, char var){
        if(var==RootBT(f)||isdigit(RootBT(f))||isalpha(RootBT(f))){
            if(!isnullptr(Right(f))||!isnullptr(Left(f)))
                throw "variable or const shouldn't be in root\n";
            if(var==RootBT(f))             // x'=1
                return ConsBT('1',nullptr,nullptr);
            return ConsBT('0',nullptr,nullptr);  // const'=0
        }
        if(RootBT(f)=='+'||RootBT(f)=='-') // (f(x) +/- g(x))' = f'(x) +/- g'(x)
            return ConsBT(
                          RootBT(f),
                          deriviate(Left(f),var),
                          deriviate(Right(f),var)
                   );
        if(RootBT(f)=='*')                 // (f(x)*g(x))'=f'(x)*g(x)+f(x)*g'(x)
            return ConsBT(
                          '+',
                          ConsBT(
                              '*',
                              deriviate(Left(f),var),
                              Right(f)
                          ),
                          ConsBT(
                              '*',
                              Left(f),
                              deriviate(Right(f),var)
                          )
                   );
        throw "unknown char\n";
    }
    int calc(Form f){
        if(isalpha(f->info) || isalpha(f->info))
            throw "Empty\n";
        int x, y, z;
        if((f->info=='+')||(f->info=='-')||(f->info=='*')){
            x=calc(f->lt);
            y=calc(f->rt);

            if (f->info=='+'){
                cout<<"you are here: "<<x<<'+'<<y<<endl;
                z=x+y;
            }
            else if (f->info=='-'){
                z=x-y;
                cout<<"you are here: "<<x<<'-'<<y<<endl;
            }
            else if (f->info=='*'){
                cout<<"you are here: "<<x<<'*'<<y<<endl;
                z=x*y;
            }
            return z;
        }
        else return f->info - '0';
    }
    void print(Form f, int l){
        if(f==nullptr){
            for(int i = 0;i<l;i++)
                cout<<"\t";
            cout<<'#'<<endl;
            return;
        }
        print(f->rt, l+1);
                for(int i = 0;i<l;i++)
                    cout<<"\t";
                cout<<f->info<<endl;
                print(f->lt, l+1);
    }

    int main(){
        Form f = nullptr;
        Form fPrime = nullptr;
        char c;
        int key = 0;
        string str;
        filebuf file;
        string file_name;
        stringbuf exp;
        string temp_str;
        char forSwitch;
        while(1){
           cout<<"Press 1 to read from console, press 2 to read from 1.txt file, press 0 to exit."<<endl;
           cin >> forSwitch;
           getchar();
           switch (forSwitch) {
               case '2':{
                   ifstream infile("1.txt");
                   if(!infile){
                         cout<<"There is no file"<<endl;
                         continue;
                         }
                   getline(infile, temp_str);
                   istream is(&exp);
                   exp.str(temp_str);

                   break;
               }
               case '1':{
                       cout<<"Enter the variable for derivative"<<endl;
                       cin>>c;
                       try{
                       cin.ignore();
                       cout<<"Enter the expression"<<endl;
                       getline(cin, temp_str);
                       istream is(&exp);
                       exp.str(temp_str);
                       writeForm(cout, f=readForm(is));
                       cout<<endl;
                       try{
                       cout<<"expression value: ";
                       cout<<calc(f)<<endl;
                       }
                       catch(const char* e){
                           cout<<e;
                       }

                       print(f, 0);
                       writeForm(cout, (fPrime=deriviate(f, c)));
                       cout<<endl;
                       break;
                       }
                       catch(const char* t){
                           cout<<t;
                       }
               }
               case '0':{
                       return 0;
               }
               default:{
                       cout<<"Incorrect input"<<endl;
                       break;
               }

           }

           f=Delete(f);
           fPrime=Delete(fPrime);
       str.clear();
       }

    }

