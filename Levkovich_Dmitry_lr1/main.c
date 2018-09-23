#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int* getToken(char*); //Получает лексему из строки
void pars(char*, FILE*); //Точка входа анализатора
int fSum(int*, FILE*); //Обрабатывает сложение и вычитание
int fMulti(int*, FILE*); //Обрабатывает умножение и деление
int fUnary(int*); //Обработка унарных операторов
int fAtom(int*); //Получает значение числа

enum {Empty, Operator, Number} type;
int count = 0;//счетчик шагов 
int max = 0;//максимум выражения
int deep = 0;//глубина
char *expr; //Указатель на обрабатываемую строку
char token[80]; //Лексема
int k = 0;

int main()
{
	int run=1;
    int value=0;
    char expr[255]; //Содержит вычисляемое выражение
    FILE *in=fopen("input.txt", "r");
    FILE *out=fopen("output.txt", "w");
    while(run){
    printf("Введите 1, если хотите ввести выражение из терминала, 2-из файла, 3-завершить программу:");
   	scanf("%d", &k);
    switch(k){
	    case 1:
	        printf("Введите максимальное значение результата выражения:");
    		scanf("%d\n", &max);
    			        printf("Введите выражение:\n");
	        fgets(expr,80, stdin);
	        if(!*expr) 
	        	return 0;    //Если введена пустая строка - завершить программу
	        pars(expr, out); //Вычислить выражение
	        value=atoi(expr);
	        if(value>max){
	            printf("Значение выражения(%d) больше максимума(%d). Программа завершилась на %d-ом шаге.\n", value, max, count);
	            break;
	        }
	        printf("Result: %d, вложенность рекурсии %d\n", value, deep);
	        break;
	    case 2:
	    	fscanf(in,"%d\n",&max);
	        fgets(expr, 80, in);
	        fprintf(out,"%s", expr);
	        pars(expr, out);
	        value=atoi(expr);
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

void pars(char *line, FILE* out)
{
    int *pointer;
    int result;
    expr=line;
    pointer=getToken(expr);
    fSum(&result, out);
    *pointer=0;
    sprintf(expr, "%d", result);
}

int* getToken(char *expr)
{
    type=Empty;
    static int i=0;

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
    i++;
return &i;
}

int fSum(int *anw, FILE* out)
{
    char op;
    int temp;
    if(fMulti(anw, out)) return 1;
    while((op = *token) == '+' || op == '-')
    {
        getToken(expr);
        fMulti(&temp, out);
        switch(op)
        {
         case '+':
         if(k==1)
         	printf("Вы здесь: %d + %d\n", *anw, temp);
         if(k==2)
         	fprintf(out, "Вы здесь: %d + %d\n", *anw, temp);
            *anw += temp;
            count ++;
            if(*anw>max)
                return -1;
            break;
         case '-':
         if(k==1)
         	printf("Вы здесь: %d - %d\n", *anw, temp);
         if(k==2)
         	fprintf(out, "Вы здесь: %d - %d\n", *anw, temp);
            *anw -= temp;
            count++;
            if(*anw>max)
                return -1;
            break;
        }
    }
	deep++;
return 0;
}

int fMulti(int *anw, FILE* out)
{
    char op;
    int temp;
    if(fUnary(anw)) return 1; //Ошибка

    while((op = *token) == '*')
    {
        getToken(expr);
        if(fUnary(&temp)) return 1; //Ошибка
        switch(op)
        {
         case '*':
         if(k==1)
         	printf("Вы здесь: %d * %d\n", *anw, temp);
         if(k==2)
         	fprintf(out,"Вы здесь: %d * %d\n", *anw, temp);
            *anw *= temp;
            count++;
            if(*anw>max)
                return -1;
            break;
        }
    }
	deep++;
return 0;
}

int fUnary(int *anw)
{
    char op=0;
    if(*token == '+' || *token == '-')
    {
        op = *token;
        getToken(expr);
    }
    if(fAtom(anw)) return 1; //Ошибка

    if(op == '-') *anw = -(*anw);
deep++;
return 0;
}

int fAtom(int *anw){

    if(type==Number){
        *anw = atoi(token);
        getToken(expr);
    }
    else
        return 1;
    deep++;
return 0;
}
