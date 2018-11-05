#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

typedef char base;
struct node{
    base info;
    node *lt;
    node *rt;
};
typedef node *binTree;

base RootBT(binTree b){
    if(b == NULL){
        cerr << "Error: RootBT(null) \n";
        exit(1);
    }else
        return b->info;
}

binTree ConsBT(const base &x, binTree &lst, binTree &rst){
    binTree p;
    p = new node;
    if ( p != NULL) {
        p ->info = x;
        p ->lt = lst;
        p ->rt = rst;
        return p;
    }else {
        cerr << "Memory not enough\n";
        exit(1);
    }
}

binTree EnterBT(char* arrayKLP,char* arrayLKP, int &i){
    binTree p,q;
    p=NULL;
    q=NULL;
    char c,c1;
    if(i<strlen(arrayKLP) && strlen(arrayLKP)!=0){
        c=arrayKLP[i];
        c1=arrayLKP[strlen(arrayLKP)-1-i];
        for(int j=0;j<strlen(arrayLKP);j++){
            if(arrayKLP[i]==arrayLKP[j]){
                char* gap_left_str=(char*)calloc(20,sizeof(char));
                strncpy(gap_left_str,arrayLKP,j);
                char* gap_right_str=(char*)calloc(20,sizeof(char));
                strncpy(gap_right_str,arrayLKP+j+1,strlen(arrayLKP)-j-1);
                i++;
                p=EnterBT(arrayKLP,gap_left_str,i);
                q=EnterBT(arrayKLP,gap_right_str,i);
                return ConsBT(c,p,q);
            }
        }
    }else
        return NULL;
}

binTree Left(binTree b){
    if (b == NULL){
        cerr << "Error: Left(null) \n";
        exit(1);
    }else
        return b->lt;
}

binTree Right(binTree b){
    if (b == NULL){
        cerr << "Error: Right(null) \n";
        exit(1);
    }else
        return b->rt;
}

void outBT(binTree b,int i,bool left, binTree ptr){
    if (b!=NULL){
        outBT(Left(b),i+4,true,b);
        if(ptr==NULL){
            for(int k=0;k<i;k++)
                cout<<" ";
            cout<<"---";
            cout << RootBT(b)<<endl;
        }else if(left){
            for(int k=0;k<i;k++)
                cout<<" ";
            cout<<".---";
            cout << RootBT(b)<<endl;
        }else{
            for(int k=0;k<i;k++)
                cout<<" ";
            cout<<"`---";
            cout << RootBT(b)<<endl;
        }
        outBT(Right(b),i+4,false,b);
    }else
        return;
}

void LPK(binTree b){
    if(b!=NULL){
        LPK(Left(b));
        LPK(Right(b));
        cout<<RootBT(b);
    }else
        return;
}

bool check(char* arrayKLP,char* arrayLKP){
    int k=0;
    for(int i=0;i<strlen(arrayKLP);i++){
        for(int j=0;j<strlen(arrayLKP);j++){
            if(arrayLKP[j]==arrayKLP[i])
                k++;
        }
    }
    if(k==strlen(arrayKLP))
        return true;
    else
        return false;
}

int main(){
    int num=0;
    while(num != 3){
        char* arrayKLP=(char*)calloc(20,sizeof(char));
        char* arrayLKP=(char*)calloc(20,sizeof(char));
        cout << "Выберите дальнейшие действия и введите цифру:"<<endl;
        cout << "1. Ввести перечисления узлов вручную."<<endl;
        cout << "2. Считать перечисления узлов из файла test1.txt."<<endl;
        cout << "3. Завершить работу."<<endl;
        cin >> num;
        switch(num){
            case 1:{
                getchar();
                char c;
                c=getchar();
                int j=0;
                while(!isspace(c)){
                    arrayKLP[j]=c;
                    j++;
                    c=getchar();
                }
                c=getchar();
                j=0;
                while(!isspace(c)){
                    arrayLKP[j]=c;
                    j++;
                    c=getchar();
                }
                int i=0;
                binTree b;
                if(strlen(arrayKLP)==strlen(arrayLKP)){
                    if(check(arrayKLP,arrayLKP)==true){
                        b=EnterBT(arrayKLP,arrayLKP,i);
                        i=0;
                        binTree ptr;
                        ptr=NULL;
                        outBT(b,i,false,ptr);
                        LPK(b);
                        cout<<endl;
                    }else{
                        cerr<<"Strings are not the same."<<endl;
                        exit(1);
                    }
                }else{
                    cerr<<"Strings are not the same."<<endl;
                    exit(1);
                }
                free(arrayLKP);
                free(arrayKLP);
                break;
            }
            case 2:{
                string array;
                ifstream infile("test1.txt");
                getline(infile,array);
                array=array+'\n';
                int k=0;
                while(!isspace(array[k])){
                    arrayKLP[k]=array[k];
                    k++;
                }
                arrayKLP[strlen(arrayKLP)]='\0';
                k++;
                int j=0;
                while(!isspace(array[k])){
                    arrayLKP[j]=array[k];
                    k++;
                    j++;
                }
                arrayLKP[strlen(arrayLKP)]='\0';
                int i=0;
                binTree b;
                if(strlen(arrayKLP)==strlen(arrayLKP)){
                    if(check(arrayKLP,arrayLKP)==true){
                        b=EnterBT(arrayKLP,arrayLKP,i);
                        i=0;
                        binTree ptr;
                        ptr=NULL;
                        outBT(b,i,false,ptr);
                        LPK(b);
                        cout<<endl;
                    }else{
                        cerr<<"Strings are not the same."<<endl;
                        exit(1);
                    }
                }else{
                    cerr<<"Strings are not the same."<<endl;
                    exit(1);
                }
                
                free(arrayLKP);
                free(arrayKLP);
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
