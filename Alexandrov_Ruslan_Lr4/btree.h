#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

template<typename Elem>
class BT {
private:
    enum sides {
        leftSide, rightSide
    };
    Elem element;
    BT *root;
    BT *left;
    BT *right;
public:
    BT();

    void createBT(const string &str, int &i);

    void createRoot(const string &str, int &i);

    void createChildren(const string &str, int &i, int side);

    bool findElem(Elem elem, BT *bt);

    bool findOnSides(Elem elem, BT *bt);

    int countElems(Elem elem, BT *bst, int &count);

    bool countOnSides(Elem elem, BT *bt, int &count);

    int getLeastLength(Elem elem, BT *bst);

    void getSidesLeastLength(Elem elem, BT *bst, int &count, bool &flag);

    ~BT();
};

template<typename Elem>
BT<Elem>::BT() {
    root = NULL;
    left = NULL;
    right = NULL;
}

// Init Binary Tree
template<typename Elem>
void BT<Elem>::createBT(const string &str, int &i) {
    if (str[i] == '(') {
        i++;
        createRoot(str, i);
        createChildren(str, i, leftSide);
        createChildren(str, i, rightSide);
        if (str[i] == ')') {
            i++;
        }
    } else {
        throw invalid_argument("");
    }
}

template<typename Elem>
void BT<Elem>::createRoot(const string &str, int &i) {
    string resStr;
    if (isspace(str[i + 1]) && str[i + 1] == ')' && str[i + 1] == '(') {
        resStr = str[i];
        element = resStr;
        i++;
    } else {
        while (!isspace(str[i]) && str[i] != ')' && str[i] != '(' ) {
            resStr.push_back(str[i]);
            i++;
        }
        element = resStr;
    }
}

template<typename Elem>
void BT<Elem>::createChildren(const string &str, int &i, int side) {
    if (str[i] != ')') {
        if (side == leftSide) {
            left = new BT;
            left->root = this;
            left->createBT(str, i);
        } else {
            right = new BT;
            right->root = this;
            right->createBT(str, i);
        }
    }
}

// function wrapper
template<typename Elem>
bool BT<Elem>::findElem(Elem elem, BT *bst) {
    if (bst == NULL) {
        return false;
    }
    if (bst->element == elem) {
        return true;
    }
    if (!bst->left && !bst->right) {
        return false;
    }
    if (findOnSides(elem, bst->left)) {
        return true;
    }
    return findOnSides(elem, bst->right);
}

template<typename Elem>
bool BT<Elem>::findOnSides(Elem elem, BT *bst) {
    if (bst->element == elem) {
        return true;
    }
    if (bst->left) {
        if (bst->left->element == elem) {
            return true;
        }
        findOnSides(elem, bst->left);
    }
    if (bst->right) {
        if (bst->right->element == elem) {
            return true;
        }
        findOnSides(elem, bst->right);
    }
    return false;
}

// function wrapper
template<typename Elem>
int BT<Elem>::countElems(Elem elem, BT *bst, int &count) {
    if (bst == NULL) {
        return 0;
    }
    if (bst->element == elem) {
        count++;
    }
    if (bst->left) {
        if (bst->left->element == elem) {
            count++;
        }
        countOnSides(elem, bst->left, count);
    }
    if (bst->right) {
        if (bst->right->element == elem) {
            count++;
        }
        countOnSides(elem, bst->right, count);
    }
    return count;
}

template<typename Elem>
bool BT<Elem>::countOnSides(Elem elem, BT *bst, int &count) {
    if (bst->left) {
        if (bst->left->element == elem) {
            count++;
        }
        countOnSides(elem, bst->left, count);
    }
    if (bst->right) {
        if (bst->right->element == elem) {
            count++;
        }
        countOnSides(elem, bst->right, count);
    }
    return false;
}

template<typename Elem>
int BT<Elem>::getLeastLength(Elem elem, BT *bst) {
    if (!findElem(elem, bst)) {
        return -1;
    }
    int countLeft = 0;
    int countRight = 0;
    bool flag = false; // true if we will see our element
    if (bst->left || bst->right) {
        if (bst->left->root->element == elem || bst->right->root->element == elem) {
            return countLeft;
        }
    }
    if (bst->left) {
        if (bst->left->element == elem) {
            return ++countLeft;
        }
        getSidesLeastLength(elem, bst->left, countLeft, flag);
        if (!flag) countLeft = 0;
    }
    flag = false;
    if (bst->right) {
        if (bst->right->element == elem) {
            return ++countRight;
        }
        getSidesLeastLength(elem, bst->right, countRight, flag);
        if (!flag) countRight = 0;
    }
    if (countLeft == 0) {
        return countRight;
    }
    if (countRight == 0) {
        return countLeft;
    }
    return ((countLeft > countRight) ? countRight : countLeft);
}

template<typename Elem>
void BT<Elem>::getSidesLeastLength(Elem elem, BT *bst, int &count, bool &flag) {
    if (bst->element != elem) {
        count++;
    }
    if (bst->left) {
        if (bst->left->element == elem) {
            flag = true;
            return;
        }
        getSidesLeastLength(elem, bst->left, count, flag);
    }
    if (bst->right) {
        if (bst->right->element == elem) {
            flag = true;
            return;
        }
        getSidesLeastLength(elem, bst->right, count, flag);
    }
}

template<typename Elem>
BT<Elem>::~BT() {
    if (left != NULL) {
        delete left;
    }
    if (right != NULL) {
        delete right;
    }
}