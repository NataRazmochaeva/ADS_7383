#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 501


// Бинарное коромысло
typedef struct BinCor
{
    unsigned int length_left;
    unsigned int length_right;
    unsigned int weight_left;
    unsigned int weight_right;
    struct BinCor * cor_1;
    struct BinCor * cor_2;
} BinCor;


// вывод сообщений об ошибках
void errorMassage(int error_number, char * str, int index)
{
    printf("\nОшибка! Вы ввели некорректные данные:\n");
    switch (error_number)
    {
        case 1:
            printf("Символ №%d - '%c'.\n", index+1, str[index]);
            printf("Ожидался символ - '('.\n");
            break;
        case 2:
            printf("Символ №%d - '%c'.\n", index+1, str[index]);
            printf("Ожидался символ - ')'.\n");
            break;
        case 3:
            printf("Символ №%d - '%c'.\n", index+1, str[index]);
            printf("Ожидалось значение от 1 до 9.\n");
            break;
        case 4:
            printf("Символ №%d - '%c'.\n", index+1, str[index]);
            printf("Ожидался пробел.\n");
            break;
        case 5:
            printf("Символ №%d - '%c'.\n", index+1, str[index]);
            printf("Отсутствует закрывающая скобка.\n");
            break;
        case 6:
            printf("Символ №%d - '%c'.\n", index+1, str[index]);
            printf("Ожидалось значение от 1 до 9 или '('.\n");
            break;
        case 7:
            printf("После символа №%d присутствуют лишние символы.\n", index+1);
            break;
    }
}


BinCor* initBinCorElement()// Инициализация элемента списка
{
    BinCor * element = (BinCor*)malloc(sizeof(BinCor));
    element->length_left = 0;
    element->length_right = 0;
    element->weight_left = 0;
    element->weight_right = 0;
    element->cor_1 = NULL;
    element->cor_2 = NULL;
    return element;
}


// считывание и создание бинарного коромысла
// функция возвращает 1, если возникла ошибка
int readBinCorElement(char * str, int index_1, int index_2, BinCor ** element)
{
    *element = initBinCorElement();

    if (str[index_1++] != '(')
    {
        errorMassage(1, str, index_1 - 1);
        return 1;
    }
    if (str[index_2--] != ')')
    {
        errorMassage(2, str, index_2 + 1);
        return 1;
    }

    // считывание левого плеча
    if (str[index_1++] != '(')// открывающая скобка левого плеча
    {
        errorMassage(1, str, index_1 - 1);
        return 1;
    }
    // первое число(длина)
    if (!isdigit(str[index_1]) || str[index_1] == '0')
    {
        errorMassage(3, str, index_1);
        return 1;
    }

    while(1)// считывание числа
    {
        if (isdigit(str[index_1]))
        {
            (*element)->length_left = (*element)->length_left * 10 + str[index_1] - '0';
            index_1++;
        }
        else
            break;
    }

    if (str[index_1++] != ' ')// пробел после первого числа
    {
        errorMassage(4, str, index_1 - 1);
        return 1;
    }

    if (isdigit(str[index_1]) && str[index_1] != 0)// случай, если гирька cout<<"\t"
    {
        while(1)
        {
            if (isdigit(str[index_1]))
            {
                (*element)->weight_left = (*element)->weight_left * 10 + str[index_1] - '0';
                index_1++;
            }
            else
                break;
        }
    }
    else
        if (str[index_1] == '(')// случай, если ещё одно коромысло
        {
        int bracket_count = 0;
        int index;
        // поиск закрывающей скобки
        for (index = index_1; index < index_2; index++)
        {
            if (str[index]=='(')
                bracket_count++;
            if (str[index]==')')
                bracket_count--;

            if (bracket_count == 0)
            {
                if ( readBinCorElement(str, index_1, index, &((*element)->cor_1)) )
                    return 1;
                index_1 = index + 1;
                break;
            }
        }
        if (bracket_count != 0)
        {
            errorMassage(5, str, index_1);
            return 1;
        }
    }
        else
        {
        errorMassage(6, str, index_1);
        return 1;
        }

    if (str[index_1++] != ')')// закрывающая скобка левого плеча
    {
        errorMassage(2, str, index_1 - 1);
        return 1;
    }


    if (str[index_1++] != ' ')// пробел между плечами
    {
        errorMassage(4, str, index_1 - 1);
        return 1;
    }


    // считывание правого плеча
    if (str[index_1++] != '(')// открывающая скобка прового плеча
    {
        errorMassage(1, str, index_1 - 1);
        return 1;
    }

    // первое число(длина)
    if (!isdigit(str[index_1]) || str[index_1] == 0)
    {
        errorMassage(3, str, index_1);
        return 1;
    }
    while(1)// считывание числа
    {
        if (isdigit(str[index_1]))
        {
            (*element)->length_right = (*element)->length_right * 10 + str[index_1] - '0';
            index_1++;
        }
        else
            break;
    }

    if (str[index_1++] != ' ')// пробел после первого числа
    {
        errorMassage(4, str, index_1 - 1);
        return 1;
    }

    if (isdigit(str[index_1]) && str[index_1] != '0')// случай, если гирька
    {
        while(1)
        {
            if (isdigit(str[index_1]))
            {
                (*element)->weight_right = (*element)->weight_right * 10 + str[index_1] - '0';
                index_1++;
            }
            else
                break;
        }
    }
    else
        if (str[index_1] == '(')// случай, если ещё одно коромысло
        {
        int bracket_count = 0;
        int index;
        // поиск закрывающей скобки
        for (index = index_1; index < index_2; index++)
        {
            if (str[index]=='(')
                bracket_count++;
            if (str[index]==')')
                bracket_count--;

            if (bracket_count == 0){
                if ( readBinCorElement(str, index_1, index, &((*element)->cor_2)) )
                    return 1;
                index_1 = index + 1;
                break;
            }
        }

        if (bracket_count != 0)
        {
            errorMassage(5, str, index_1);
            return 1;
        }
    }
        else
        {
        errorMassage(6, str, index_1);
        return 1;
        }
    if (str[index_1] != ')')// закрывающая скобка левого плеча
    {
        errorMassage(2, str, index_1);
        return 1;
    }

    // проверка на лишние символы
    if (index_2 != index_1)
    {
        errorMassage(7, str, index_1);
        return 1;
    }

    return 0;
}


// создание бинарного коромысла
// функция возвращает 1, если возникла ошибка
int createBinCor(char * str, BinCor ** binCor)
{
    int index_1 = 0;
    int index_2 = strlen(str) - 2;

    return readBinCorElement(str, index_1, index_2, binCor);
}


/*void print_bin_kor(BinCor *binCor, unsigned int i)
{
    if (binCor->cor_2)  //1
    {
        for (unsigned int j=0; j<i; j++)
            printf("\t");
        printf ("\n(F1) %d", binCor->length_right);
        print_bin_kor(binCor->cor_2, i++);
    }
    if (binCor->cor_1) //2
    {
        for (unsigned int j=0; j<i; j++)
            printf("\t");
        printf ("\n(F2) %d", binCor->length_left);
        print_bin_kor(binCor->cor_1, i++);
    }
    if (!binCor->cor_2 && !binCor->cor_1) //3
    {
        for (unsigned int j=0; j<i; j++)
            printf("\t");
        printf ("\t(F3) %d; %d\n", binCor->length_right, binCor->weight_right);
        printf ("\n\t(F3) %d; %d\n", binCor->length_left, binCor->weight_left);

    }
    if (!binCor->cor_1 && binCor->cor_2) //4
    {
        for (unsigned int j=0; j<i; j++)
            printf("\t");
        printf ("\n(F4) %d", binCor->length_right);
        printf ("\n\t(F4) %d; %d\n", binCor->length_left, binCor->weight_left);
        print_bin_kor(binCor->cor_2, i++);
    }
    if (binCor->cor_1 && !binCor->cor_2)  //5
    {
        for (unsigned int j=0; j<i; j++)
            printf("\t");
        printf ("\n\t(F5) %d; %d\n", binCor->length_right, binCor->weight_right);
        printf ("\n(F5) %d", binCor->length_left);
        print_bin_kor(binCor->cor_1, i++);

    }
*/

/*void print_bin_kor (BinCor *binCor, int deep_of_recursion)
{
    if (binCor->cor_2 != NULL)
        print_bin_kor(binCor->cor_2, deep_of_recursion++);
    for (int i = 0; i < deep_of_recursion; i++)
       printf("\t");
    if (binCor->cor_2 == NULL)
    {
        printf("%d  ", binCor->length_right);
        printf("%d(гирька)\n\n", binCor->weight_right);
    }
    else
        printf("%d  ", binCor->length_right);


    if (binCor->cor_1 != NULL)
        print_bin_kor(binCor->cor_1, deep_of_recursion++);
    for (int i = 0; i < deep_of_recursion; i++)
       printf("\t");
    if (binCor->cor_1 == NULL)
    {
        printf("%d  ", binCor->length_left);
        printf("%d(гирька)\n\n", binCor->weight_left);
    }
    else
        printf("%d  ", binCor->length_left);
}*/

void print_bin_kor(BinCor *binCor, int deep_of_recursion)
{
    for (int i = 0; i < deep_of_recursion; i++)
       printf("\t");
    printf("%d  ", binCor->length_right);

    if (binCor->cor_2 == NULL)
    {
        printf("%d(гирька)\n\n", binCor->weight_right);
    }
    else
    {
        printf("\t\n");
        print_bin_kor(binCor->cor_2, deep_of_recursion+1);
    }

    for (int i = 0; i < deep_of_recursion; i++)
        printf("\t");
    printf("%d  ", binCor->length_left);

    if (binCor->cor_1 == NULL)
    {
        printf("%d(гирька)\n\n", binCor->weight_left);
    }
    else
    {
        printf("\t\n");
        print_bin_kor(binCor->cor_1, deep_of_recursion+1);
    }
}


//Возвращаемое значение равно длине всех плеч
//в заданном бинарном коромысле
short length(const BinCor binCor, int deep_of_recursion)
{
    int result = 0;

    for (int i = 0; i < deep_of_recursion; i++)
        printf("     ");
    printf("левое плечо(+%d): ", binCor.length_left);
    result+=binCor.length_left;

    if (binCor.cor_1 == NULL)
    {
        printf("гиря.\n");
    }
    else
    {
        printf("коромысло: \n");
        result += length(*(binCor.cor_1), deep_of_recursion+1);
    }

    for (int i = 0; i < deep_of_recursion; i++)
        printf("     ");
    printf("правое плечо(+%d): ", binCor.length_right);
    result+=binCor.length_right;

    if (binCor.cor_2 == NULL)
    {
        printf("гиря.\n");
    }
    else
    {
        printf("коромысло:\n");
        result += length(*(binCor.cor_2), deep_of_recursion+1);
    }

    return result;
}



// очистка памяти
void free_memory(BinCor * binCor)
{
    if (binCor != NULL)
    {
        free(binCor->cor_1);
        free(binCor->cor_2);
    }
    free(binCor);
}



int main()
{
    char str[N]; // строка для ввода
    BinCor * binCor = NULL; // бинарное коромысло
    int in=0; //для определения способа ввода данных


    // начало считывания и обработки данных
    printf("\nПрограмма выводит общую длину всех плеч в указанном бинарном коромысле.\n");
    printf("\nБинарное коромысло записывается в виде:\n");
    printf("(ПЛЕЧО ПЛЕЧО)\n");
    printf("Плечо имеет следующий вид:\n");
    printf("(ДЛИНА ГРУЗ)\n");
    printf("В качестве груза может выступать ещё одно бинарное коромысло или груз (число).\n");
    printf("\nВыберите способ ввода бинарного коромысла (не больше 500 символов): \n");
    printf("\n1. Ввод коромысла из файла.");
    printf("\n2. Ввод коромысла с консоли.\n");
    scanf ("%d", &in);

    if (in == 1)
    {
        FILE* file = fopen ("input.txt", "r");
        if (file == NULL)
            perror("Ошибка открытия файла");
        fgets(str, N, file);
        fclose(file);
    }
    if (in == 2)
    {
        printf("\nВведите бинарное коромысло (не более 500 символов):");
        fgets(str, 2, stdin);
        fgets(str, N, stdin);
    }

    // обработка данных и проверка на ошибки
    if (createBinCor(str, &binCor))
    {
        printf("Программа завершила работу.\n\n");
        free_memory(binCor);
        return 0;
    }
    printf("\nВведены корректные данные.\n\n");
    // конец считывания и обработки данных

    print_bin_kor(binCor, 0);

    printf("\n\n\n");

    // вывод результата
    printf("Ход работы алгоритма:\n\n");
    printf("\nОбщая длина плеч: %u.\n\n", length(*binCor, 1));

    free_memory(binCor);

    return 0;
}
