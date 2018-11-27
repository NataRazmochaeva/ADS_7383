#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>
 #include "functions.h"

 #define N 500

 int main(){
 char *name;
 FILE *file;
 int quit = 1;
while(quit != 0){
 printf("Please input your expression\n");
 	scanf("\n");
 	name = (char*)malloc(sizeof(char)*N);
 	fgets(name, N, stdin);
 	file = fopen("input.txt","w+");
 	fputs(name, file);
 	fclose(file);
 	file = fopen("input.txt","r");
 
 fpos_t txt_pointer;
 fgetpos(file, &txt_pointer);
 fgets(name, N, file);
 printf("\nINPUT EXPRESSION:\n");
 printf("%s\n", name);
 fsetpos(file, &txt_pointer);

 printf("\nSTEPS:\n");
 char symbol;
 int level = 0;
 Element * Head=NULL;
 Element * El;
 Element * Up=NULL;
 int tag;
 Head = makeList(level,Up,file);
 symbol = fgetc(file);
 fclose(file);

 file = fopen("log.txt","a");
 if (file == NULL)
 	file = fopen("log.txt","w+");
 if (level != 0)
 	fprintf(file,"Brackets do not match!\n");
 if (symbol != '\n')
 	fprintf(file,"Arguments out of brackets!\n");
 if (Head != NULL) El = Head;
 else{
 	printf("List is empty!\n");
 	return 0;
 }
 fclose(file);

 name[0] = '\0';
 check_mistakes(Head);
 file=fopen("log.txt","r");
 if (file == NULL)
 	printf("\nSyntactically correct!\n");
 else{
 	fgetpos(file, &txt_pointer);
 	fgets(name, N, file);
 	if (name[0] == '\0')
 		printf("\nSyntactically correct!\n");
 	else{
 		fsetpos(file, &txt_pointer);
 		printf("\n\nSyntactically incorrect!\nAll errors:\n");
 		while (1){
 			fgets(name, N, file);
 			if (feof(file)) break;
 			printf("%s", name);
 		}
 	}
 }
 free(name);
 fclose(file);
 remove("log.txt");
 //remove("input.txt");
 clearList(Head);
 printf("If you want to finish press 0, else press 1\n");
 scanf("%d", &quit);
 }






  return 0;
 }