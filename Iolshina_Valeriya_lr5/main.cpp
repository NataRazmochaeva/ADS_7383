#include <iostream>
#include <fstream>
#include "bst.h"
#include <sstream>
#include <ctype.h>
#include <cstring>

using namespace std;

int main()
{
  bool b = 0;
  int count=0;
  int k;
  base el;
  int run = 0;
  base arr[N];
while(run!=3)
{
    cout << "Введите 1, если хотите ввести выражение с клавиатуры.\n"
            "Введите 2, если хотите использовать выражение из файла test.txt.\n"
            "Введите 3, если хотите закончить работу." << endl;
    cin >> run;
    BST* tree = NULL;
    count=0;
    switch(run)
    {
      case 1:
        {
          cout << "Введите последовательность различных элементов: \n";
          cin.get();
          char c=getchar();
          while(c!='\n')
          {
            cin>>el;
	    arr[count] = el;
            count++;
            c=getchar();
          }
          cout << "Введите искомый элемент: \n";
          cin >> k;
          b=1;
          break;
        }
      case 2:
        {
          ifstream outfile;
          outfile.open("test.txt");
          if (!outfile)
          {
            cout << "Входной файл не открыт!\n";
            b = 0;
            break;
          }
          while(outfile >> arr[count])
          {
            count++;
          }
          outfile.close();
          b=1;
          cout << "Введите искомый элемент: \n";
          cin >> k;
          break;
        }
      case 3:
        {
          b=0;
          break;
        }
      default:
        {
          cout << "Введите верное число\n";
          b=0;
          break;
        }
    }
    if(b)
    {
      for (int i=0; i<count; i++)
      tree = createBST(tree, arr[i]);
      if(find_add(tree, k))
        cout << "Элемент в дереве уже есть\n";
      else
        cout << "Элемент вставлен в дерево\n";
      cout << "Дерево: \n";
      printBST(tree, 1);
      tree = destroy(tree);
      cout << endl;
    }
}
return 0;
}
