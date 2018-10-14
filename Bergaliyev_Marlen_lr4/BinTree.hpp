#pragma once

template <class T>

class BinTree{
public:
    BinTree(T value) : left(nullptr), right(nullptr), value(value){}
    BinTree(BinTree const& tree){
	value = tree.value;
	if(tree.left != nullptr)
	    left = new BinTree(*tree.left);
	else left = nullptr;
	if(tree.right != nullptr)
	    right = new BinTree(*tree.right);
	else right = nullptr;
    }
    void push_left(BinTree<T> tree){
	delete left;
	left = new BinTree<T>(tree);
    }
    void push_right(BinTree<T> tree){
	delete right;
	right = new BinTree<T>(tree);
    }
    unsigned int depth(){
	unsigned int lenght = 0;
	if(left != nullptr)
	    lenght = left->depth() + 1;
	if(right != nullptr){
	    unsigned int right_lenght = right->depth() + 1;
	    if(right_lenght > lenght)
		lenght = right_lenght;
	}
	return lenght;
    }
    unsigned int node_number(){
	unsigned int res = 1;
	if(left != nullptr)
	    res += left->node_number();
	if(right != nullptr)
	    res += right->node_number();
	return res;
    }

    unsigned int internal_lenght(){
	unsigned int lenght = 0;
	if(left != nullptr)
	    lenght += left->internal_lenght() + left->node_number();
	if(right != nullptr)
	    lenght += right->internal_lenght() + right->node_number();
	return lenght;
    }

    void print_leafs(std::ostream &output){
	if(left == nullptr && right == nullptr)
	    output << value << " ";
	if(left != nullptr)
	    left->print_leafs(output);
	if(right != nullptr)
	    right->print_leafs(output);
    }

    unsigned int nlvl_node_number(unsigned int n){
	if(n == 1)
	    return 1;
	int res = 0;
	if(left != nullptr)
	    res += left->nlvl_node_number(n-1);
	if(right != nullptr)
	    res += right->nlvl_node_number(n-1);
	return res;
    }

    T get(unsigned int n){
	if(n == 0)
	    return value;
	unsigned int left_num = 0;
	if(left != nullptr)
	    left_num = left->node_number();
	if(n > left_num)
	    return right->get(n - left_num - 1);
	return left->get(n-1);
    }
	    
    bool equal_elem(){
	for(unsigned int i=0; i<node_number(); ++i)
	    for(unsigned int j=0; j<node_number(); ++j)
		if(i != j && get(i) == get(j))
		    return true;
	return false;
    }

    ~BinTree(){
	delete left;
	delete right;
    }
	    
private:
    T value;
    BinTree<T>* left;
    BinTree<T>* right;
};

