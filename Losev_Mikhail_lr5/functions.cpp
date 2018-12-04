/* Функции Лосева */
#include "bst_interf.h"
#include "functions.h"

using namespace std;
using namespace losev_BST;


namespace losev_functions
{
		bool is_digit( char c )
		{
			return ( (c <= '9') && (c >= '0'));
		}

		int check_for_externs(string str)
		{
			char* arr = new char[str.size()];
			strcpy(arr, str.c_str());
			for (int i = 0; i < str.size(); i++)
				if (!is_digit(arr[i]) && arr[i] != ' ')
					return 1; // not OK
			return 0; // OK
		} 

	void rand_init()
	{
		srand(time(NULL));
		// rand надо инициализировать, поскольку иначе он будет выдавать 
		// одну и ту же последовательность псевдослучайных чисел при каждом
		// запуске программы. rand инициализируется временем, потому что 
		// время в каждый момент времени различно, и поэтому последовательность
		// псевдослучайных чисел будет всегда различная.
	}
}
