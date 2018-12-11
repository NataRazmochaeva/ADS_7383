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
  int run = 0;
  BST* tree = NULL;
  base arr[N];
    cout << "Введите 1, если хотите ввести выражение с клавиатуры.\n"
            "Введите 2, если хотите использовать выражение из файла test.txt.\n"
            "Введите 3, если хотите закончить работу." << endl;
    cin >> run;
    switch(run)
    {
      case 1:
        {
          cout << "Введите последовательность различных элементов: \n";
          cin.get();
          base c;
          do
            c=getchar();
          while(c == ' ');
          while(!isspace(c))
          {
            cin>>arr[count];
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
            cout<<count<<" "<<arr[count]<<endl;
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
return 0;
}
