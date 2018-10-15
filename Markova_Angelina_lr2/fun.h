#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 50

typedef struct Element{
	struct Element* next;
	struct Element* down;
	int tag;
	char* sym;
} El;

El* CreateEl(int tag, char* sym, El* up, El* prev);
El* CreateList(FILE** test, El* UpEl, int* count, int* countmax);
void clearList(El* element);
void check(FILE** test, int* c, int* cm);
