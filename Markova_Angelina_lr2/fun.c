#include "fun.h"

El* CreateEl(int tag, char* sym, El* up, El* prev){ //создание элемента списка
	El* new_element = (El*)malloc(sizeof(El));
	new_element -> tag = tag;
	if(tag){
		new_element -> sym = (char*)malloc(sizeof(char)*N);
		strcpy(new_element -> sym, sym);
	}
	if(up) up -> down = new_element; //поднялись на элемент выше и зполнили поле, указывающее на след.элемент  
	if(prev) prev -> next = new_element;
	new_element -> down = NULL;
	new_element -> next = NULL;
	return new_element;
}

El* CreateList(FILE** test, El* UpEl, int* count, int* countmax){ //создает иерархический список
	int tag, index=0, run=1;
	El *up=UpEl, *prev=NULL, *Head_El, *El;
	char osym; //one symbol
	fpos_t pos;
	char* sym = (char*)malloc(sizeof(char)*N);
	while(run){
		sym[0]=0; //обнуление строки
		if (index) up=NULL;//для того чтобы указывал на первый нижний элемент, не меняясь
		osym=fgetc(*test);
		if(osym == '\n' || osym == '\0') break;
		if(osym == ' ') continue; // пропуск пробелов
		if(osym == '(' && *count == 0 && index == 0){ 
			(*count)++;
			continue; //пропуск первой скобки
		}
		if(index==0 && osym == ')') (*count)--; //пустой уровень 
		while(isalpha(osym)){
			strncat(sym, &osym,1);
			fgetpos(*test, &pos); //сохранение позиции
			osym=fgetc(*test); //файловый поток
		}
		if(sym[0]){
			osym='0';
			fsetpos(*test, &pos); //возвращение на пред.символ, чтобы не потерять скобочки
			tag=1;
		}
		else tag=0;
		if(osym==')'){
			if(*count>*countmax) *countmax=*count; //поиск максимального уровня вложенности 
			(*count)--;
			return Head_El;
		}
		if(!index){ //проверка на нулевую позицию - голову 
			Head_El=CreateEl(tag, sym, up, prev);
			prev=Head_El;
			El=Head_El;
		} 
		else{
			El=CreateEl(tag, sym, up, prev); //создание элементов
			prev=El;
		}
		index++;
		if(osym=='('){
			(*count)++;
			CreateList(test, El, count, countmax);
		} 
	} 
return Head_El;
}

void clearList(El* element){ //очистка памяти
	El* temp;
	temp=element;
	while(temp!=NULL){
		if(temp->down!=NULL){
			clearList(temp->down);
		}
		temp=temp->next;
	}
	free(temp);
}

void check(FILE** test, int* c, int* cm){ //работа с файлом
	if(!(*test)){printf("\033[31mФайл не может быть открыт!\n\033[0m"); return;}
	El* Head = CreateList(test, NULL, c, cm);
	if(!(*cm)) printf("Список пуст!\n");
	else printf("Максимальное число уровней вложенности %d\n", *cm);
	clearList(Head);
	fclose(*test);
	return;
}

