#include <iostream>
#include <fstream>
#include "bt.h"
#include <sstream>
#include <ctype.h>
#include <cstring>

using namespace std;
extern int count;

bool check_inp(base* arrayKLP, base* arrayLKP)
{
  int k=0;
  for(int i=0; i<strlen(arrayKLP); i++)
  {
    for(int j=0; j<strlen(arrayLKP); j++)
    {
      if(arrayLKP[j] == arrayKLP[i])
        k++;
    }
  }
  if(k == strlen(arrayKLP))
      return true;
  else
  {
    cerr << "Перечисления содержат разные узлы" << endl;
    exit(1);
  }

}

int main()
{
  bool k = 0;
  char c;
  int run = 0;
    cout << "Введите 1, если хотите ввести выражение с клавиатуры.\n"
            "Введите 2, если использовать выражение из файла test.txt.\n"
            "Введите 3, если хотите закончить работу." << endl;
    cin >> run;
  int size = 20;
  int size2 = 20;
  base *arrayKLP=(char*)calloc(size, sizeof(char));
  base *arrayLKP=(char*)calloc(size2, sizeof(char));
    switch(run)
    {
      case 1:
        {
          cout << "Введите КЛП и ЛКП: \n";
          cin.get();
          base c;
          do
            c=getchar();
          while(c == ' ');
          int j=0;
          while(!isspace(c))
          {
            arrayKLP[j]=c;
            j++;
            if(j>=size)
            {
              size+=size;
              arrayKLP = (char*)realloc(arrayKLP, size*sizeof(char));
            }
            c=getchar();
          }
          do
            c=getchar();
          while(c == ' ');
          j=0;
          while(!isspace(c))
          {
            arrayLKP[j]=c;
            j++;
            if(j>=size2)
            {
              size2+=size2;
              arrayLKP = (char*)realloc(arrayLKP, size2*sizeof(char));
            }
            c=getchar();
          }
          check_inp(arrayKLP, arrayLKP);
          k=1;
          break;
        }
      case 2:
        {
          ifstream outfile;
          outfile.open("test.txt");
          if (!outfile)
          {
            cout << "Входной файл не открыт!\n";
            k = 0;
            break;
          }
          outfile >> arrayKLP;
          outfile >> arrayLKP;
          check_inp(arrayKLP, arrayLKP);
          outfile.close();
          k=1;
          break;
        }
      case 3:
        {
          k=0;
          break;
        }
      default:
        {
	  run = 3;
          cout << "Введите верное число\n";
          k=0;
          break;
        }
    }
    if(k)
    {
      count = 1;
      binTree b;
      b = new Node[strlen(arrayKLP)+1];
      int i=0, res=0, n=0;
      res = createBT(arrayKLP, arrayLKP, i, b, size);
      cout << "Результат работы программы: \n";
      printBT(b, i, n);
      cout << endl;
      LPK(b, i);
      free(arrayKLP);
      free(arrayLKP);
      delete [] b;
      cout << endl << endl;
    }
return 0;
}
