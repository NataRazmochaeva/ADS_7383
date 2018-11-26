#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>
#include <fstream>
#include <cctype>
class Tree{
public:
    char data;
};

using namespace std;

void buildTree(vector<Tree>&arr,int index,int max,char buffer[],int j){
    if (index >= max)
        return;
    int stet = 0;
    int k = j;
    if (buffer[j] == '\0')
        return;
    if (buffer[j] == '('){
        j++;
        while (buffer[j] != '*' && buffer[j] != '+' && buffer[j] != '-'){
            while (buffer[j] == '('){
              stet++;
              j++;
            }
            if (stet == 0)
              j++;
            while (stet>0){
              if (buffer[j] == ')')
                stet--;
              j++;
            }
        }
      }
      else {
          arr[index].data = buffer[j];
          return;
      }
    if (buffer[j] == '*' || buffer[j] == '+' || buffer[j] == '-'){
        arr[index].data = buffer[j];
      }
    buildTree(arr, 2*index+1, max, buffer,k+1);
    buildTree(arr, 2*(index+1), max, buffer,j+1);
}

void print(vector<Tree>&arr,int index,string &str,int max,int count){
  if (index >= max)
    return;
  print(arr,2*index+1,str,max,count+1);
  for (int i = 0;i < count;i++)
  str = str + "   ";
  if (arr[index].data != '#')
    str = str + "[" + arr[index].data + "]\n";
  else str = str + "   \n";
  print(arr,2*(index+1),str,max,count+1);
}

void prefix(vector<Tree>arr,unsigned int index){
  if (index>=arr.size())
    return;
  if (arr[index].data != '#')
    cout << arr[index].data;
  prefix(arr,2*index+1);
  prefix(arr,2*(index+1));
}

string change(vector<Tree>arr,int index,string Lskob,string Rskob,string answer){
    if (index >= arr.size())
        return answer;
    if (arr[index].data == '#')
        return answer;
    if (arr[index].data == '*' || arr[index].data == '+' || arr[index].data == '-')
        return Lskob+change(arr,2*index+1,Lskob,Rskob,answer)+arr[index].data+change(arr,2*(index+1),Lskob,Rskob,answer)+Rskob;
    else return change(arr,2*index+1,Lskob,Rskob,answer)+arr[index].data+change(arr,2*(index+1),Lskob,Rskob,answer);
}

void right(vector<Tree>&arr,int index){
  char symb = arr[2*index+1].data;
  arr[2*(2*index+1)+1].data = symb;
  arr[2*index+1].data = arr[2*(index+1)].data;
  char copy = arr[4*(index+1)+1].data;
  arr[4*(index+1)+1].data = symb;
  arr[2*(2*index+2)].data = copy;
}

void left(vector<Tree>&arr,int index){
  char symb = arr[2*(index+1)].data;
  arr[2*(2*(index+1)+1)].data = symb;
  arr[2*(index+1)].data = arr[2*index+1].data;
  char copy = arr[2*(2*index+2)].data;
  arr[2*(2*index+2)].data = symb;
  arr[4*(index+1)+1].data = copy;
}

bool test(char buff[]){
    int count=0;
    if (buff[0]!='(' || buff[strlen(buff)-1]!=')')
        return false;
    for (int i=0;buff[i]!='\0';i++){
        if (buff[i]=='(')
            count++;
        if (buff[i]==')')
            count--;
        if (buff[i]=='/')
            return false;
        if (buff[i]=='+'||buff[i]=='*'||buff[i]=='-'){
            if (i<2||i>strlen(buff)-3)
                return false;
            if (!isalnum(buff[i-1])||!isalnum(buff[i+1]))
                return false;
        }
        if ((!isalnum(buff[i])||isupper(buff[i]))&&buff[i]!='+'&&buff[i]!='-'&&buff[i]!='*'&&buff[i]!='('&&buff[i]!=')')
            return false;
    }
    if (count == 0)
        return true;
    else return false;
}



int main()
{
    cout << "Task #21" << endl;
    cout << "Press 1 to write str" << endl;
    cout << "Press 2 to get str from file" << endl;
    cout << "Press 3 to exit" << endl;
    int choose;
    char buffer[100];
    cin >> choose;
    cin.ignore();
    switch (choose){
    case 1:{
        cout << "Input formula: ";
        cin.getline(buffer,100);
        break;
    }
    case 2:{
        ifstream inp("file.txt");
        inp.getline(buffer,100);
        inp.close();
        cout << "Input formula: " << buffer << endl;
        break;
    }
    case 3:{
        return 0;
    }
    default:{
        cout << "Wrong input, try again";
        return 0;
        }
    }

    if (!test(buffer)){
        cout << "Wrong str" << endl;
        return 0;
    }
    if (!strlen(buffer)){
        cout << "Empty str" << endl;
        return 0;
    }
    int ct = 1,max_skob = 0;
    int N;
    int j = 0;
    int minus_flag = 0;
    for(int i=0;buffer[i]!='\0';i++){
      if (buffer[i] == '(')
        ct++;
      if (buffer[i] == ')'){
          if (ct > max_skob)
              max_skob = ct;
          ct = 1;
      }
      if (buffer[i]  == '-')
          minus_flag = 1;
    }
    if (max_skob < 2)
        max_skob = 2;
    N = pow(2,max_skob)-1;
    vector <Tree> arr(N);
    for (int i=0;i<N;i++){
      arr[i].data = '#';
    }
    cout<<endl;
    buildTree(arr,0,N,buffer,j);
    cout<<"tree-formula: ";
    for( int i= 0;i<N; i++){
      cout<<arr[i].data;
    }
    cout << endl;
    string str;
    int count = 0;
    print(arr,0,str,N,count);
    cout << str;



    string Lskob = "(",Rskob = ")",answer = "";
    answer += change(arr,0,Lskob,Rskob,answer);
    cout << "2 task answer: " << answer << endl;



    cout << "3 task answer: ";
    prefix(arr,0);
    cout << endl;


    cout << "4 task answer: ";
    if (minus_flag == 0){
      int left_index = 0,right_index = 0;
      for (int i=0;2*(i+1) < arr.size() && 2*i+1 < arr.size();i++){
        if (arr[i].data == '*' && arr[2*i+1].data != '*' && arr[2*i+1].data != '+' && arr[2*(i+1)].data == '+'){
            right_index = i;
            right(arr,right_index);
          }
        if(arr[i].data == '*' && arr[2*(i+1)].data != '*' && arr[2*(i+1)].data != '+' && arr[2*i+1].data == '+'){
            left_index = i;
            left(arr,left_index);
        }
      }
      string ans = "";
      ans += change(arr,0,Lskob,Rskob,ans);
      cout << ans << endl;
    }
    else cout << "Input with minus! " << buffer << endl;
    return 0;
}
