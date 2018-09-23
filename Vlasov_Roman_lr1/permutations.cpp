#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "permutations.h"

using namespace std;

void Permutations::run()
{
    clock_t t1s, t1e, t2s, t2e, d1, d2;
    cout << "Printing Iteratively" << endl;
    t1s = clock();
    print_iteratively();
    t1e = clock();
    cout << "Printing Recursively" << endl;
    t2s = clock();
    print_recursively();
    t2e = clock();
    d1 = t1e - t1s;
    d2 = t2e - t2s;
    cout << "Iteratively it takes " << d1 << " μs." << endl;
    cout << "Recursively it takes " << d2 << " μs." << endl;
    cout << (d2 < d1 ? "Recursively" : "Iteratively") << " is faster on "
                                                    << abs(d2 - d1) << " μs.\n" << endl;
}

Permutations::Permutations(int n, int* el) : n(n), it(el) {
    tmp = new int[n];
    for (int i = 0; i < n; i++)
        elements.push_back(el[i]);
};

void Permutations::print_current(int *el)
{
    for (int i = 0; i < n; i++)
        cout << el[i] << " ";
    cout << endl;
}

bool Permutations::next_permutation()
{ // next permutation algorithm by Narayana
    int j = n - 2;
    int k = n - 1;
    // find first decreasing element from the right
    while(j >= 0 && it[j] >= it[j + 1])
        j--;
    // if j < 0 there is no next permutation
    if (j < 0)
        return false;
    // find first element that larger than it[j]
    while(it[j] >= it[k])
        k--;
    swap(it[j], it[k]);
    // reverse the elements that are to the right for it[j]
    int l = n - 1;
    int r = j + 1;
    while(r < l)
    {
        swap(it[r], it[l]);
        r++;
        l--;
    }
    return true;
}

void Permutations::print_iteratively()
{
    int j = 1;
    for (int i = 1; i <= n; i++)
        j *= i;
    for (j; j > 0; j--)
        {
            print_current(it);
            next_permutation();
        }
}

void Permutations::print_recursively(int c)
{
    if (c == n - 1)
    {
        tmp[c] = elements.back();
        print_current(tmp);
        return;
    }
    for (int i = 0; i < elements.size(); i++)
    {
        tmp[c] = elements[i];
        elements.erase(elements.begin() + i);
        print_recursively(c + 1);
        elements.push_back(tmp[c]);
        sort(elements.begin(), elements.end());
    }
}

Permutations::~Permutations()
{
    delete[] tmp;
}
