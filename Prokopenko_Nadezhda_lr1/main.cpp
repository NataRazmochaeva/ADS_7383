#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool bracket_exp(string str, unsigned int cur_pos=0, bool flag=false, int opened_br=0)
{
    if(cur_pos < str.length())
    {
        if(str[cur_pos]=='A' && flag==false)
        {
            flag = true;
        }
        else if(str[cur_pos] == '(' && flag==true && str[cur_pos-1] != ')')
        {
            flag = false;
            opened_br++;
        }
        else if(str[cur_pos] == ';' && flag == true && opened_br > 0)
        {
            flag = false;
        }
        else if(str[cur_pos] == ')' && flag == true && opened_br > 0)
        {
            opened_br--;
        }
        else if(opened_br != 0)
        {
            return flag = false;
        }
        else
        {
            return flag = false;
        }
        flag = bracket_exp(str, cur_pos+1, flag, opened_br);
    }
    return flag;
}

string delet(string str){
  int i=0;
  while(str.length()>i){
    if(str[i] == ' ')
      str.erase(i,1);
    else  i++;
  }
  return str;
}
int print(bool result, int sw_var){
  if(result)
      cout << "True. This is the concept of brackets.\n";
  else
      cout << "False. This is not the concept of brackets.\n";
  return sw_var = 4;
}

int main()
{
    int sw_var;
    string str;
    bool result = false;
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
        case 1:
            cout << "Enter the string:"<< '\n';
            getline(cin, str);
            if(str != ""){
                result = bracket_exp(delet(str));
              }
            sw_var=print(result, sw_var);
            break;
        case 2:
            cout << "Enter the name of the file:"<< '\n';
            cin >> file_name;
            cin.ignore();
            file.open(file_name, fstream::in);
            if(!file.is_open()){
                cout << "Error opening file.\n";
                sw_var = 4;
              }
            else{
                getline(file, str);
                cout << delet(str) << endl;
                if(str != "")
                    result = bracket_exp(delet(str));
                sw_var=print(result, sw_var);
                file.close();
              }
            break;
        case 0:
            break;
        default:
            cout << "Enter again.\n";
            cin >> sw_var;
            cin.ignore();
            break;
        }
    }
    return 0;
}
