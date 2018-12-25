#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "bt.h"
using namespace std;
extern int count = 1;

bool isNull(binTree b, int i)
{
  return b[i].info == '\0';
}

char RootBT(int i, binTree b)
{
	if (b == NULL)
	{
		cerr << "Error: RootBT(null) \n";
		exit(1);
	}
	else
		return b[i].info;
}

int Left(int i, binTree b)
{
	if (b == NULL)
	{
		cerr << "Error: Left(null) \n";
		exit(1);
	}
	else
		return b[i].lt;
}

int Right(int i, binTree b)
{
	if (b == NULL)
	{
		cerr << "Error: Right(null) \n";
		exit(1);
	}
	else
		return b[i].rt;
}

int ConsBT(char x, int lst, int rst, binTree b, int i)
{
  if (b != NULL)
	{
		b[i].info = x;
		b[i].lt = lst;
		b[i].rt = rst;
		return i;
	}
	else
	{
		cerr << "Memory not enough\n";
		exit(1);
	}
}

int createBT(base* arrayKLP, base* arrayLKP, int &i, binTree b, int size)
{
  int l, r;
  char c,c1;
  if(i<strlen(arrayKLP) && strlen(arrayLKP)!=0)
  {
    c=arrayKLP[i];
    c1=arrayLKP[strlen(arrayLKP)-1-i];
    for(int j=0;j<strlen(arrayLKP);j++)
    {
      if(arrayKLP[i]==arrayLKP[j])
      {
        char* gap_left_str=(char*)calloc(size,sizeof(char));
        strncpy(gap_left_str,arrayLKP,j);
        char* gap_right_str=(char*)calloc(size,sizeof(char));
        strncpy(gap_right_str,arrayLKP+j+1,strlen(arrayLKP)-j-1);
        i++;
        l=createBT(arrayKLP, gap_left_str, i, b, size);
        r=createBT(arrayKLP, gap_right_str, i, b, size);
        return ConsBT(c, l, r, b, count++);
      }
    }
  }
  else
      return 0;
}

void printBT(binTree b, int i, int n)
{
  if (i!=0)
  {
    if (!isNull(b, Right(i, b)))
      printBT(b, Right(i, b), n+1);
    else cout << endl;
    if(n==0)
      cout << RootBT(i, b)<<endl;
    for(int j=0; j<=n; j++)
      cout << "  ";
    if(n!=0)
      cout << RootBT(i, b)<<endl;
    if(!isNull(b, Left(i, b)))
      printBT(b, Left(i, b), n+1);
  }
  else
      return;
}

void LPK(binTree b, int i)
{
  if(b!=NULL && i!=0)
  {
    LPK(b, Left(i, b));
    LPK(b, Right(i, b));
    cout << RootBT(i, b);
  }
  else
    return;
}
