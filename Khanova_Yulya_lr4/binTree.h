#pragma once
namespace binTree_modul
{

	struct node {
		char info;
		int lt;
		int rt;
		node(char inputinfo= 0, int inputlt = 0, int inputrt = 0) {
			info = inputinfo;
			lt=inputlt;
			rt=inputrt;
		};
	};
	bool isNull(int);
	char RootBT(int);
	int Left(int);
	int Right(int);
	int freeND();
	int ConsBT(const char &x, int lt, int rt);
	//void destroy(node*&);

}
