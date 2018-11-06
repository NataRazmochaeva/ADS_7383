#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <exception>

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
	~node(){
		cout << "<3 " << info << endl;
		delete lt;
		delete rt;
	}
    };
    typedef node *binTree; // "представитель" бинарного дерева
    binTree Create(void);
    bool isNull(binTree);
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
     bool isNull(binTree b)
    {
        return (b == nullptr);
    }
     base RootBT (binTree b)                     // для непустого бин.дерева
    {   if (b == nullptr) { cerr << "Error: RootBT(null) \n"; exit(1); }
        else return b->info;
    }
     binTree Left (binTree b)            // для непустого бин.дерева
    {   if (b == nullptr) { cerr << "Error: Left(null) \n"; exit(1); }
        else return b ->lt;
    }
     binTree Right (binTree b)           // для непустого бин.дерева
    {   if (b == nullptr) { cerr << "Error: Right(null) \n"; exit(1); }
        else return b->rt;
    }
     binTree ConsBT(const base &x, const binTree &lst, const binTree &rst)
    {   binTree p;
        p = new node;

            p ->info = x;
            p ->lt = lst;
            p ->rt = rst;
            return p;
        
    }
//-------------------------------------
     bool isSign(char c){
        return c=='+'||c=='-'||c=='*';
    }
    bool isTerminal(char c){
        return isdigit(c)||(c>='a'&&c<='z');
    }
    Form readForm(istream &in){
        if(isTerminal(in.peek())){
            return ConsBT(in.get(), nullptr, nullptr);
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
        if(isNull(f))throw "Error, empty formula\n";
        if(isNull(Right(f))&&isNull(Left(f))){
            out<<RootBT(f);
            return;
        }
        if(isNull(Right(f))||isNull(Left(f)))
            throw "Knot should have Left and Right\n";
        out<<'(';
        writeForm(out,Left(f));
        out<<RootBT(f);
        writeForm(out,Right(f));
        out<<')';
    }
     Form deriviate(const Form f, char var){
        if(var==RootBT(f)||isdigit(RootBT(f))||isalpha(RootBT(f))){
            if(!isNull(Right(f))||!isNull(Left(f)))
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
            return ConsBT('+',ConsBT('*',deriviate(Left(f),var),Right(f)),ConsBT('*',Left(f),deriviate(Right(f),var)));
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
 int main (){

    Form f;
    Form fPrime;
    int run = 1;
    string k;
    int m;
    while(run){
    cout<<"enter the variable for derivative"<<endl;
    char c;
    cin>>c;
    cin.ignore();
    try{
        cout<<"Source formula:";
        writeForm(cout, (f=readForm(cin)));
        cout<<endl;
        try{
        cout<<"expression value: ";
        cout<<calc(f)<<endl;
        }
        catch(const char* e){
            cout<<e;
        }
        cout<<"graphical representation:"<<endl;
        cout<<endl;
        print(f, 0);
        cout<<"derivative for "<<c<<endl;
        writeForm(cout, (fPrime=deriviate(f,c)));
        cout<<endl;
    }
    catch(const char* t){
        cout<<t;
    }
	delete f;
	delete fPrime;
    cout<<"Continue? Press 1. Else press 0"<<endl;
        cin>>m;
        cin.ignore();
        if(m==0)
            return 0;
    }
    return 0;
}
