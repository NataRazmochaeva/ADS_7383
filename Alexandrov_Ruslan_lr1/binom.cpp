#include <iostream>
#include "binom.h"

using namespace std;


uint64_t Binom::eval(uint64_t m, uint64_t n, uint64_t &half, uint64_t &full) {
        i++;
        printUnderscore(i);
        cout << "in [" << i << "]" << " with m = " << m << " and n = " << n ;
    if (m > n && n >= 0) {
        cout << ",  x = " << 0 << endl;
        return 0;
    } else if ((m == 0 && n > 0) || (n >= 0 && m == n)) {
    	cout << ",  x = " << 1 << endl;
        return 1;
    } else {
	cout << " call recursive " << endl;
        half = eval(m - 1, n - 1, half, full);  // solve a smaller problem
	i--;
        full = half + eval(m, n - 1, half, full);  // use the solution of the smaller problem

        printUnderscore(i);
        cout << "out [" << i << "]" << " with m = " << m << " and n = " << n << ",  x = " << full << endl;
        i--;

        return full;
    }
}

uint64_t Binom::count(uint64_t m, uint64_t n) {
    uint64_t h = 0;
    uint64_t f = 0;
    return eval(m, n, h, f);
}

void Binom::printUnderscore(unsigned short int i) {
    for (short j = 1; j <= i; j++) cout << "_";
}
