#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <cctype>

#define SIZE_OF_NAME 30

using namespace std;

typedef struct queue{
    int que[SIZE_OF_NAME];
    int startptr,endptr;
}queue;

char** list_of_names(FILE* ptr,int num,bool** children){
    char **name=(char**)calloc(num,sizeof(char*));
    int j=0;
    int i=0;
    name[i]=(char*)calloc(SIZE_OF_NAME,sizeof(char));
    char* gap_name;
    while(!feof(ptr)){
        gap_name=(char*)calloc(SIZE_OF_NAME,sizeof(char));
        fgets(gap_name,SIZE_OF_NAME,ptr);
        gap_name[strlen(gap_name)-1]='\0';
        for(int j=0;j<strlen(gap_name);j++){
            if(isalpha(gap_name[j])){
                name[i][strlen(name[i])]=gap_name[j];
            }else if(gap_name[j]==' '){
                name[i][strlen(name[i])]='\0';
                int counter=0;
                for(int k=0;k<i;k++){
                    if(strcmp(name[i],name[k])==0){
                        counter++;
                    }
                }
                if(counter==0){
                    i++;
                    name[i]=(char*)calloc(SIZE_OF_NAME,sizeof(char));
                }else{
                    free(name[i]);
                    name[i]=(char*)calloc(SIZE_OF_NAME,sizeof(char));
                }
            }else if(isdigit(gap_name[j])){
                for(int n=0;n<i;n++){
                    if(strstr(gap_name,name[n])==gap_name){
                        for(int l=0;l<i;l++){
                            if(strstr(gap_name,name[l])==(gap_name+1+strlen(name[n])) && gap_name[j]=='1'){
                                children[n][l]=true;
                            }
                        }
                    }
                }
            }
        }
        free(gap_name);
    }
    return name;
}

int isempty(queue *q){
    if(q->endptr < q->startptr)
        return 1;
    else
        return 0;
}

queue* init(){
    queue* q=(queue*)malloc(sizeof(queue));
    q->startptr=1;
    q->endptr=0;
    return q;
}

void push(queue* q,int x){
    if(q->endptr < SIZE_OF_NAME-1){
        if(q->que[q->endptr]!=x){
            q->endptr++;
            q->que[q->endptr]=x;
        }
    }else{
        
    }
    return;
}

void pop(queue* q,char** name,FILE* exit){
    if(isempty(q)==1){
        cout<<"Queue is empty!"<<endl;
        return;
    }else{
        fprintf(exit,"%s\n",name[q->que[q->startptr]]);
        for(int i=q->startptr;i<q->endptr;i++)
            q->que[i]=q->que[i+1];
        q->endptr--;
        return;
    }
}

int main(){
    char fname[SIZE_OF_NAME];
    printf("Choose file\n");
    fgets(fname,SIZE_OF_NAME,stdin);
    fname[strlen(fname)-1]='\0';
    FILE * ptr = fopen (fname, "r");
    FILE * exit = fopen("generation.txt", "w");
    if(ptr==NULL){
        printf("Error.\n");
        return 0;
    }
    int num;
    fscanf(ptr,"%d\n",&num);
    bool** children=(bool**)calloc(num,sizeof(bool*));
    for(int i=0;i<num;i++){
        children[i]=(bool*)calloc(num,sizeof(bool));
        for(int j=0;j<num;j++){
            children[i][j]=false;
        }
    }
    char** name=list_of_names(ptr,num,children);
    for(int i=0;i<num;i++)
        cout<<name[i]<<endl;
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++)
            cout<<children[i][j];
        cout<<endl;
    }
    fclose(ptr);
    queue* generation=init();
    cout<<"Input name: "<<endl;
    char*person=(char*)calloc(SIZE_OF_NAME,sizeof(char));
    fgets(person,SIZE_OF_NAME,stdin);
    person[strlen(person)-1]='\0';
    for(int i=0;i<num;i++){
        if(strcmp(person,name[i])==0){
            for(int j=0;j<num;j++)
                if(children[i][j]==true)
                    push(generation,j);
        }
    }
    if(isempty(generation)){
        cerr<<"Wrong name was inputed."<<endl;
        return 0;
    }
    while(isempty(generation)!=1){
        for(int i=0;i<num;i++){
            if(children[generation->que[generation->startptr]][i]==true)
                push(generation,i);
        }
        pop(generation,name,exit);
    }
    for(int j=0;j<num;j++){
        free(children[j]);
    }
    free(children);
    free(person);
    fclose(exit);
    return 0;
}
