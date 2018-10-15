#include "fun.h"

int main(){
	char* str;
	FILE* test;
	int c=0, cm=0, flag=1, var; //c-счетчик, cm-максимальный счетчик, т.е показывает уровень вложенности
		printf("\t\033[34mЗдравствуйте! Выберите что вы хотите:\033[0m\n 1) Нажмите 1, чтобы посчитать уровень вложенности списка в файле\n 2) Нажмите 2, чтобы посчитать уровень вложенности списка с консоли\n 3) Нажмите 3, чтобы выйти из программы\n");
		while(flag){
		scanf("%d", &var);
		switch(var){
			case 1: 
				test=fopen("test.txt", "r");
				c=0;
				cm=0;
				check(&test, &c, &cm);
				break;
			case 2:
				scanf("\n");
				str=(char*)malloc(sizeof(char)*N);
				fgets(str, N, stdin);
				test=fopen("test1.txt", "w+");
				fputs(str, test);
				fclose(test);
				test=fopen("test1.txt", "r");
				c=0;
				cm=0;
				check(&test, &c, &cm);
				remove("test1.txt");
				free(str);
				break;
			case 3:
				flag=0;
				break;
			default: 
				flag=0;
				printf("\033[31mНекорректный выбор!\033[0m\n");
				break;
		}
		}
	printf("\033[34mДо свидания!\033[0m\n");
return 0;
}
