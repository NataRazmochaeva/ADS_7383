#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#define LEFT 0
#define RIGHT 1

using namespace std;


class BinaryTree {
    private:
            char element;

        BinaryTree *left;
        BinaryTree *parent;
        BinaryTree *right;

    public:
        void readBT(const string &string, int &i) {
                if (string[i] == '(') {
                    i++;
                    read_root(string, i);
                    readUnder(string, i, LEFT);
                    readUnder(string, i, RIGHT);
                    if (string[i] == ')')
                            i++;
                    else{
                        cout << "')' expected at the index:"<<i<<endl;
                        exit(1);


                }

                }
            else{
                cout << "'(' expected at the index:"<<i<<endl;
                exit(1);

                }

        }

            void read_root(const string &string, int &i){
            if (isdigit(string[i]) || isalpha(string[i])) {
                    element = string[i];
                    i++;
                }
                else {
                     cout<<"Expected number or letter at the index: "<<i<<endl;
                    exit(1);
                }
        }
            void readUnder(const string &string, int &i, int side){
            if (string[i] == '#')
                    i++;
                else if(string[i] != ')'){
                    if (side == LEFT) {
                            left = new BinaryTree;
                            left->parent = this;
                            left->readBT(string, i);
                    }
                    else {
                            right = new BinaryTree;
                            right->parent = this;
                            right->readBT(string, i);
                    }
                }

        }

        BinaryTree(){
                left = NULL;
                parent = NULL;
                right = NULL;
        }

        ~BinaryTree(){
            if (left)
                    delete left;
                if (right)
                    delete right;
        }

        int height(){
            int height_left = 0;
                if (left != NULL)
                    height_left = left->height();
                int height_right = 0;
                if (right != NULL)
                    height_right = right->height();
                if (height_left > height_right)
                return 1 + height_left;
                return 1 + height_right;
        }


        int nodes(){
            if (left == NULL && right == NULL)
                return 1;
            int left_nodes = 0 , right_nodes = 0;
            if (left != NULL)
                left_nodes = left->nodes();
            if (right != NULL)
                right_nodes = right->nodes();
            return left_nodes + right_nodes + 1;
        }


        void leafs(){
            if(left == NULL && right == NULL)
                    cout << element << " ";
            if(left != NULL)
                    left->leafs();
            if(right != NULL)
                    right->leafs();
            }


        int nodesLvl(int n){
            int result = 0;
            if (n<=0){
            cout<<"Expected positive number and not zero"<<endl;
            }
            else if (n == 1)
                return 1;
            else{
                if(left)
                    result += left->nodesLvl(n-1);
                if(right)
                    result += right->nodesLvl(n-1);
            }
            return result;
        }


        int internal_lenght(){
             int lenght = 0;
            if(left != NULL)
                lenght += left->internal_lenght() + left->nodes();
            if(right != NULL)
                lenght += right->internal_lenght() + right->nodes();
            return lenght;

        }
};

