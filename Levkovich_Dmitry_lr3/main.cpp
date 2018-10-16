#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <cmath>
#include <exception>

using namespace std;
using base = int;

template <class T>
class Stack
{
private:
        T * arr;
        int size;
        int len;
public:
        Stack();
        ~Stack();
        int Size();
        void Push(T x);
        T Pop();
        T Top();
        void Clear();
        bool IsEmpty();
	void new_size(T s);
};
        template <class T>
        Stack<T>::Stack()
        {
                len = 0;
                arr = new T[size = 5];
        }

        template <class T>
        Stack<T>::~Stack()
        {
                delete[] arr;
        }

        template <class T>
        int Stack<T>::Size()
        {
                return len;
        }

        template <class T>
        void Stack<T>:: Push(T x)
        {
                if (len == size) 
                	new_size(size<<1);
                arr[len++] = x;
                cout<<"Push -> "<<x<<endl;
        }
        template <class T>
        T Stack<T>::Pop()
        {
            if (len == 0) 
	    	return arr[len];
            return arr[--len];
        }
        template <class T>
        T Stack<T>::Top()
        {
            return arr[len];
        }
        template <class T>
        void Stack<T>::Clear()
        {
            delete arr;
        }

            template <class T>
            bool Stack<T>::IsEmpty()
        {
            return len == 0;
        }
	template <class T>
        void Stack<T>::new_size(T s)
        {
                if (s<=0) 
			return;
                T * new_arr = new T[s];
                for (int i = 0; i<s; i++) 
			new_arr[i] = arr[i];
                delete[] arr;
                size = s;
                arr = new_arr;
		cout<<"NEW SIZE "<<size<<endl;

        }
        void computation(string a){
            int x = 0;
            Stack<int> s;
            int n=a.length();
            for (int i = 0; i < n; i++){
		if(!isspace(a[i])){
                	cout << "шаг_: " << i+1 << " символ = " << a[i] << endl;
		}
                if (a[i] == '+')
                    s.Push(s.Pop() + s.Pop());
                if (a[i] == '-'){
                    x=s.Pop();
                    s.Push(s.Pop()-x);
                }
                if (a[i] == '*')
                    s.Push(s.Pop() * s.Pop());
                if (a[i] == '/'){
                    x= s.Pop();
                    s.Push(s.Pop()/x);
                }
                if (a[i] == '^')
                    s.Push(pow(s.Pop(), s.Pop()));
                if ((a[i] >= '0') && (a[i] <= '9'))
                    s.Push(0);
                while ((a[i] >= '0') && (a[i] <= '9')){
                    s.Push(10*s.Pop() + (a[i++]-'0'));
		if(!isspace(a[i]))
                    cout << "шаг_: " << i+1 << " символ = " << a[i] << endl;
                }
            }
            int res = 0;
            res = s.Pop();
            if(!s.IsEmpty()){
                throw invalid_argument("Error\n");
            }
            else
                cout << "Результат = " << res << endl;
            s.Clear();
        }
        string Space(string str0){
            int i = 0, k = 0;
            char str[100];
            string str1;
            while(str0[i]!='\0'){
                if((str0[i]=='^'||str0[i]=='/'||str0[i]=='*'||str0[i]=='-'|| str0[i+1]=='+')){
                    str[k]=' ';
                    str[k+1]=str0[i];
                    str[k+2]=' ';
                    k+=3;
                }
                else{
                    
                    str[k]=str0[i];
                    k++;
                }
                i++;
            }
            str[k]='\0';
            str1=str;
            return str1;
        }
    int main ()
    {
        string a;
        int run = 1;
        string k;
        int m;
        while(run){
            cout<<"Введите 1, если хотите ввести выражение из консоли, введите 2, если хотите ввести выражение из файла, 3 - выход из программы."<<endl;
            getline(cin, k);
            try{
            m=stoi(k);
            }
            catch(exception& e){
            cout<<"неверный символ"<<endl;
            }
        try{
            switch(m){
                case 1:{
                    cout << "введите выражение:" << endl;
                    getline(cin, a);
                    a=Space(a);
                    computation(a);
                break;
                }
                case 2:{
                        ifstream infile("postfix.txt");
                        if(!infile){
                            cout<<"File not open for reading"<<endl;
                            break;
                        }
                        getline(infile, a);
                        a=Space(a);
                        computation(a);
                    break;
            }
                case 3:
                    cout<<"End!"<<endl;
                    return 0;
                default:
                    break;
            }
        }
        catch(exception& e){
            cout << e.what() << endl;
        }
        }
        return 0;
    }

