#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int* getToken(char*, char*); //Получает лексему из строки
void pars(char *expr, char* token, FILE* out, int* count, int* max, int* deep, int k); //Точка входа анализатора
int fSum(int*,char*, FILE*, char *token, int *count, int *max, int *deep, int k); //Обрабатывает сложение и вычитание
int fMulti(int*,char*, FILE*, char *token, int *count, int *max, int *deep, int k); //Обрабатывает умножение и деление
int fUnary(int*, char* token, int* deep, char*); //Обработка унарных операторов
int fAtom(int*,char*, int* deep, char*); //Получает значение числа

enum {Empty, Operator, Number, Char} type;
enum {No, Syntax} error;

int main()
{
    int count = 0;//счетчик шагов
    int max = 0;//максимум выражения
    int deep = 0;//глубина
    char *expr=(char*)malloc(255*sizeof(char)); //Указатель на обрабатываемую строку
    char token[80]; //Лексема
    int k = 0;
    int run=1;
    int value=0;
    //char expr[255]; //Содержит вычисляемое выражение
    FILE *in=fopen("input.txt", "r");
    FILE *out=fopen("output.txt", "w");
    while(run){
    printf("Введите 1, если хотите ввести выражение из терминала, 2-из файла, 3-завершить программу: ");
    scanf("%d", &k);
    switch(k){
        case 1:
            printf("Введите максимальное значение результата выражения: ");
            scanf("%d", &max);
            getchar();
            printf("Введите выражение: ");
            fgets(expr, 255, stdin);
            if(!*expr)
                return 0;    //Если введена пустая строка - завершить программу
            pars(expr, token, out, &count, &max, &deep, k); //Вычислить выражение
            value=atoi(expr);
            if(error==Syntax){
            	printf("%s\n", expr);
            }
            if(value>max){
                printf("Значение выражения(%d) больше максимума(%d). Программа завершилась на %d-ом шаге.\n", value, max, count);
                break;
            }
            printf("Result: %d, вложенность рекурсии %d\n\n", value, deep);
            break;
        case 2:
            fscanf(in,"%d\n",&max);
            fgets(expr, 80, in);
            fprintf(out,"%s", expr);
            pars(expr,token, out, &count, &max, &deep ,k);
            value=atoi(expr);
            if(error==Syntax){
            	fprintf(out, "%s\n", expr);
            }
            if(value>max){
                fprintf(out ,"Значение выражения(%d) больше максимума(%d). Программа заверилась на %d-ом шаге\n\n", value, max, count);
                break;
            }
            fprintf(out, "Result: %d, вложенность рекурии %d\n\n", value, deep);
            break;
        case 3:
            return 0;
        default:
            printf("Введен неверный символ\n");
            break;
        }
        count=0;
        deep=0;
        if(k==3)
            run=0;
    }
    fclose(in);
    fclose(out);
    return 0;
}

void pars(char *expr,char* token, FILE* out, int* count,int* max, int* deep, int k)
{
    int *pointer;
    int result;
    error=No;
    pointer=getToken(expr, token);
    fSum(&result,expr, out, token, count, max, deep, k);
    *pointer=0;
    switch(error)
    {
     case No:
        sprintf(expr, "%d", result);
        break;
     case Syntax:
        strcpy(expr, "Syntax error!");
        break;
    }
}

int* getToken(char *expr, char* token)
{
    static int i=0;
    type=Empty;
    if(expr[i]=='\0') //Если конец выражения
    {
        i=0;
        return 0;
    }
    while(isspace(expr[i])) i++; //Пропустить разделительные символы

    if(strchr("+-*", expr[i]))
    {
        *token = expr[i];
        *(token+1) = '\0';
        type=Operator;
    }
    else if(isdigit(expr[i]))
    {
        int j=0;
        token[j]=expr[i];
        while(isdigit(expr[i+1]))
            token[++j]=expr[++i];
        token[j+1]='\0';
        type=Number;
    }
    else if(!isdigit(expr[i])){
        error=Syntax;
    }
    i++;
return &i;
}

int fSum(int *anw,char* expr, FILE* out, char* token, int* count, int* max, int* deep, int k)
{
    char op;
    int temp;
    if(fMulti(anw,expr, out, token, count, max, deep, k)) return 1;
    while((op = *token) == '+' || op == '-')
    {
        getToken(expr, token);
        fMulti(&temp,expr ,out, token, count, max, deep, k);
        switch(op)
        {
         case '+':
         if(k==1)
            printf("Вы здесь: %d + %d\n", *anw, temp);
         else if(k==2)
            fprintf(out, "Вы здесь: %d + %d\n", *anw, temp);
            *anw += temp;
            (*count) ++;
            if(*anw>*max)
                return -1;
            break;
         case '-':
         if(k==1)
            printf("Вы здесь: %d - %d\n", *anw, temp);
         else if(k==2)
            fprintf(out, "Вы здесь: %d - %d\n", *anw, temp);
            *anw -= temp;
            (*count)++;
            if(*anw>*max)
                return -1;
            break;
        }
    }
    (*deep)++;
return 0;
}

int fMulti(int *anw,char* expr, FILE* out, char* token, int* count, int* max, int* deep, int k)
{
    char op;
    int temp;
    if(fUnary(anw, token, deep, expr)) return 1; //Ошибка

    while((op = *token) == '*')
    {
        getToken(expr, token);
        if(fUnary(&temp, token, deep, expr)) return 1; //Ошибка
        switch(op)
        {
         case '*':
         if(k==1)
            printf("Вы здесь: %d * %d\n", *anw, temp);
        else if(k==2)
            fprintf(out,"Вы здесь: %d * %d\n", *anw, temp);
            *anw *= temp;
            (*count)++;
            if(*anw>*max)
                return -1;
            break;
        }
    }
    (*deep)++;
return 0;
}

int fUnary(int *anw, char* token, int* deep, char* expr)
{
    char op=0;
    if(*token == '+' || *token == '-')
    {
        op = *token;
        getToken(expr,token);
    }
    if(fAtom(anw, token, deep, expr)) return 1; //Ошибка

    if(op == '-') *anw = -(*anw);
(*deep)++;
return 0;
}

int fAtom(int *anw,char* token, int* deep, char* expr){

    if(type==Number){
        *anw = atoi(token);
        getToken(expr, token);
    }
    else{
        error=Syntax;
        return 1;
    }
    (*deep)++;
return 0;
}


