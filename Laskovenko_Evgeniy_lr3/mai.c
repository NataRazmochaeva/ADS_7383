#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <exception>

#define ARR_SIZE 10
using namespace std;


template<class BASE>
class Stack
{
public:
    Stack(long);
    BASE top();
    BASE pop();
    void resize(long);
    void push(BASE);
    void clear();
    bool is_empty();
    ~Stack();
private:
    BASE* arr;
    int arr_size;
    int end_index;
};
template<class BASE>
Stack<BASE>::Stack(long size)
{
    arr = new BASE[size];
    arr_size = size;
    end_index = 0;
}
template<class BASE>
BASE
Stack<BASE>::top()
{
    return arr[end_index-1];
}
template<class BASE>
BASE
Stack<BASE>::pop()
{
    end_index--;
    return arr[end_index];
}
template<class BASE>
void
Stack<BASE>::resize(long new_size)
{
    auto new_arr = new BASE[new_size];
    for(int i=0; i<arr_size; i++)
        new_arr[i] = arr[i];
    arr_size = new_size;
    delete arr;
    arr = new_arr;
}
template<class BASE>
void
Stack<BASE>::push(BASE el)
{
    if(end_index == arr_size-1)
        resize(arr_size*2);
    arr[end_index] = el;
    end_index++;
}
template<class BASE>
void
Stack<BASE>::clear()
{
    for(int i=0; i<end_index; i++)
        arr[end_index] = 0;
    end_index = 0;
}
template<class BASE>
bool
Stack<BASE>::is_empty()
{
    return end_index == 0;
}
template<class BASE>
Stack<BASE>::~Stack<BASE>()
{
    clear();
    delete[] arr;
}


class analyzer_err : public exception
{
public:
    analyzer_err(int index, const char* exp="") noexcept
    {
	sprintf(msg, "Index: %d, Error msg: ", index+1);
        msg = strcat(msg, exp);
    }
    virtual const char* what() const noexcept
    {
        return msg;
    }
    virtual ~analyzer_err(){}
private:
    char* msg;
};

class client_err : public exception
{
public:
    client_err(const char* exp) noexcept
    {
        msg = exp;
    }
    virtual const char* what() const noexcept
    {
        return msg;
    }
    virtual ~client_err(){}
private:
    const char* msg;
};


bool
syn_analyzer(istream& is_str, long size)
{
    char ch;
    bool flag = false;
    Stack<char> st(ARR_SIZE);
    for(int i=0; i<size; i++)
    {
        is_str >> ch;
        if(ch=='A' || ch=='B')
            st.push(ch);
        else if(ch=='C')
        {
            if(st.is_empty())
                throw new analyzer_err(i, "Where is x1? (Stack is empty)");
            while(!st.is_empty())
            {
                if(is_str >> ch)
                {
                    if(st.pop()==ch)
                        flag = true;
                    else
                        throw new analyzer_err(i, "x2 is not reversed x1!");
                    i++;
                }
                else
                    throw new analyzer_err(i, "x2 is wrong! (x1 is greater)");
            }
        }
        else if(ch=='D')
        {
            if(!flag)
                throw new analyzer_err(i, "D is before a,b,c,d-elements?");
            flag = false;
        }
        else
            throw new analyzer_err(i, "Wrong character in string! (Not A, B, C or D)");
    }
    if(!st.is_empty())
        throw new analyzer_err(size, "There is no C in a,b,c,d-element!");
    return flag;
}


int
main()
{
    string filename;
    string temp_str;
    filebuf file;
    stringbuf str_buf;
    istream is_str(&str_buf);
    while(true)
    {
        try
        {
            cout << "Enter a name of the data-file or press ENTER to exit:" << endl;
            getline(cin, filename);
            if(filename.empty())
                break;
            if(!file.open(filename, ios::in))
            {
               file.close();
               throw new client_err("Incorrect filename.");
            }
            auto size = file.in_avail();
            char temp_ch;
            cout << "File contains: ";
            for(auto c_size = 0; c_size<size; c_size++)
            {
                temp_ch=file.sbumpc();
                cout << temp_ch;
                if(temp_ch != ' ' && temp_ch != '\n')
                    temp_str.append(1, temp_ch);
            }
            cout << endl;
            file.close();
            if(!temp_str.size())
                throw new client_err("Input file is empty.");
            str_buf.str(temp_str);
            temp_str.clear();
            if(syn_analyzer(is_str, str_buf.in_avail()))
                cout << "It is an expression" << endl;
            else
                throw new client_err("It isn't an expression!");
        }
        catch (exception* ex)
        {
            cout << ex->what() << endl;
        }
    }
    return 0;
}

