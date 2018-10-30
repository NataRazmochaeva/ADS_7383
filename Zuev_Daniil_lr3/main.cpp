 
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
//#include <exception>
using namespace std;

class Stack
{
private:
    char *stackPtr;                      // указатель на стек
    int size;                   // максимальное количество элементов в стеке
    int top;                          // номер текущего элемента стека
public:
    Stack(int = 10);                  // по умолчанию размер стека равен 10 элементам
    ~Stack();                         // деструктор

    void newStack(int );
    int getTop();
    inline void push(const char & );     // поместить элемент в вершину стека
    inline char pop();                   // удалить элемент из вершины стека и вернуть его
    inline char tops();
    inline void printStack();         // вывод стека на экран
};

Stack::Stack(int maxSize) // инициализация константы
{
    stackPtr = new char[maxSize]; // выделить память под стек
    top = 0; // инициализируем текущий элемент нулем;
}

Stack::~Stack()
{
    delete [] stackPtr; // удаляем стек
}

void Stack::newStack(int newSize)
{
    char* newPtr = new char[newSize];
    for(int i = 0; i<=size;i++)
        newPtr[i] = stackPtr[i];
    delete [] stackPtr;
    stackPtr = newPtr;
    size = newSize;
}

int Stack::getTop()
{
    return top;
}

inline void Stack::push(const char &value)
{
    // проверяем размер стека
    if(top < size)
    {// номер текущего элемента должен быть меньше размера стека
        top++;
        stackPtr[top] = value; // помещаем элемент в стек
    }
    else
        newStack(size<<1);
}

inline char Stack::pop()
{
    // проверяем размер стека
    if(top != 0)// номер текущего элемента должен быть больше 0
        return stackPtr[--top]; // удаляем элемент из стека
    else throw 1;
}

inline char Stack::tops()
{
    // проверяем размер стека
    if(top != 0) // номер текущего элемента должен быть больше 0
        return stackPtr[top]; // удаляем элемент из стека
    else throw 2;
}

inline void Stack::printStack()
{
    for (int ix = 1; ix <= top; ix++)
        cout << stackPtr[ix] << " ";
    cout<<endl;
}

bool isName(char x)
{
    if(x=='x'||x=='y'||x=='z')
        return true;
    else return false;
}

char* readFormula(stringstream& xstream)
{
    char x;
    int i = 0;
    char a[100];
    a[i++]='(';
    do
        xstream >> x;
    while (x==' ');
    if(x =='('||x=='['||x =='{'||x=='x'||x=='y'||x=='z')
    {
        a[i++] = x;
    }
    else throw 3;
    while(xstream>>x)
    {
        while(x == ' ')
            xstream>>x;
        if(x == '('||x == '['||x =='{'||x=='x'||x=='y'||x=='z'||x == ')'||x == ']'||x == '}'||x=='+'||x=='-')
        {
            a[i++] = x;
        }
        else throw 4;
    }
    a[i++]=')';
    a[i++]='\0';
    cout<<"The input string:\n";
    for(int j = 1;j<i-2;j++)
    cout<<a[j]<<' ';
    cout<<endl;
    return a;
}

void checkFormula(char* a)
{
    Stack s;
    int len = strlen(a);
    for(int i = 0; i < len; i++)
    {
        if(a[i] == ')')
        {
            while(true)
            {
                if(!isName(s.tops()))
                    throw 5;
                s.pop();
                if(s.tops() == '{'||s.tops() == '[')
                    throw 7;
                if(s.tops() == '(')
                {
                    s.pop();
                    s.push('x');
                    break;
                }
                if(!(s.tops()=='-'||s.tops()=='+'))
                    throw 6;
                s.pop();
                if(!isName(s.tops()))
                    throw 5;
                s.pop();
                if(s.tops() == '{'||s.tops() == '[')
                    throw 7;
                if(s.tops() == '(')
                {
                    s.pop();
                    s.push('x');
                    break;
                }
                s.push('x');
            }
            s.pop();
            s.push('x');
            continue;
        }
        if(a[i] == '}')
        {
            while(true)
            {
                if(!isName(s.tops()))
                    throw 5;
                s.pop();
                if(s.tops() == '('||s.tops() == '[')
                    throw 7;
                if(s.tops() == '{')
                {
                    s.pop();
                    s.push('z');
                    break;
                }
                if(!(s.tops()=='-'||s.tops()=='+'))
                    throw 6;
                s.pop();
                if(!isName(s.tops()))
                    throw 5;
                s.pop();
                if(s.tops() == '('||s.tops() == '[')
                    throw 7;
                if(s.tops() == '{')
                {
                    s.pop();
                    s.push('z');
                    break;
                }
                s.push('z');
            }
            s.pop();
            s.push('z');
            continue;
        }
        if(a[i] == ']')
        {
            while(true)
            {
                if(!isName(s.tops()))
                    throw 5;
                s.pop();
                if(s.tops() == '('||s.tops() == '{')
                    throw 7;
                if(s.tops() == '[')
                {
                    s.pop();
                    s.push('y');
                    break;
                }
                if(!(s.tops()=='-'||s.tops()=='+'))
                    throw 6;
                s.pop();
                if(!isName(s.tops()))
                    throw 5;
                s.pop();
                if(s.tops() == '('||s.tops() == '{')
                    throw 7;
                if(s.tops() == '[')
                {
                    s.pop();
                    s.push('y');
                    break;
                }
                s.push('y');
            }
            s.pop();
            s.push('y');
            continue;
        }
        s.push(a[i]);
    }
    if(s.getTop()!=1)
        throw 8;
}

int main()
{
    stringstream xstream;
    bool b;
    char str0[100];
    short int tmp = 0;
    while(tmp != 3)
    {
        xstream.str("");
        xstream.clear();
        cout<<"Введите 1, если желаете вводить выражение с клавиатуры.\n"
              "Введите 2, если желаете брать выражение из файла test.txt.\n"
              "Введите, 3 если хотите закончить работу."<<endl;
        cin>>tmp;
        switch(tmp){
            case 1:
            {
                b = 1;
                cout << "Введите формулу: \n";
                cin.get();
                cin.getline(str0, 1000);
                xstream << str0;
                break;
            }
            case 2:
            {
                b = 1;
                ifstream outfile;
                outfile.open("test.txt");
                if (!outfile)
                {
                    cout << "Входной файл не открыт!\n";
                    b = 0;
                    break;
                }
                outfile.read(str0, 1000);
                outfile.close();
                xstream << str0;
                break;
            }
            case 3:
            {
                b = 0;
                break;
            }
            default:
            {
                cout<<"Введите верное число\n";
                break;
            }
        }
        try
        {
            checkFormula(readFormula(xstream));
        }
        catch(int a)
        {
            switch(a){
            case 2:
                cout<< "The stack is emptied during the execution of the function.\n";
                break;
            case 1:
                cout<< "Trying to take a character from an empty stack.\n";
                break;
            case 3:
                cout<< "The first character is incorrect.\n";
                break;
            case 4:
                cout<< "The following character is incorrect.\n";
                break;
            case 5:
                cout<< "The following character must be a name.\n";
                break;
            case 6:
                cout<< "The following character must be an operation.\n";
                break;
            case 7:
                cout<< "The opening bracket is not confirm to the closing bracket.\n";
                break;
            case 8:
                cout<< "Missing closing brackets.\n";
            }
            continue;
        }
        catch(exception& e)
        {
            cout<<e.what()<<endl;
            continue;
        }
        cout<<"Formula is right.\n";
    }
    return 0;
}
