#ifndef permutations
#define permutations
#include <vector>

class Permutations {
private:
    int n;
    int *it;
    int *tmp;
    std::vector <int> elements;

private:
    void print_current(int *el);
    bool next_permutation();
    void print_iteratively();
    void print_recursively(int c = 0);

public:
    void run();
    Permutations(int n, int* el);
    ~Permutations();
};

#endif /* end of include guard: permutations */
