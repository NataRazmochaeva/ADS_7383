#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

struct b_tree{
    char a;
    b_tree* left;
    b_tree* right;
};

struct forest{
    char a;
    int count;
    forest* branch[25];
};

void pr_menu(){
	cout << "Выберите действие:" << endl;
    cout << "1 - ввод с клавиатуры" << endl;
    cout << "2 - ввод из файла" << endl;
    cout << "0 - выход" << endl;
}

int full_b_tree(b_tree* tree, string str){
    int flag = 0;
    int count = 0;
    int current_count = 0;
    if(str[0] != '(')
        return -1;
    string tmp;
    if(str[1] != ')'){
        tree->a = str[1];
        tmp = str.substr(2);
        str = tmp;
        current_count = 2;
    } else {
        tree->a = '0';
        tmp = str.substr(1);
        str = tmp;
        current_count = 1;
    }
    if(str[0] == '('){
        tree->left = new b_tree;
        count += full_b_tree(tree->left, str);
        tmp = str.substr(count);
        str = tmp;
    } else if(str[0] == '#'){
        tree->left = new b_tree;
        tree->left->a = '#';
        tree->left->left = NULL;
        tree->left->right = NULL;
        count++;
        tmp = str.substr(1);
        str = tmp;
    } else if(str[0] == ')'){
        tree->left = NULL;
        tree->right = NULL;
    } else 
        return -1;
    if(str[0] == '('){
        flag = 1;
        tree->right = new b_tree;
        count += full_b_tree(tree->right, str);
    } else if(str[0] == ')')
        tree->right = NULL;
        else 
            return -1;
    return count+current_count+1;
}

struct trunk{
	trunk* prev;
	string str;
	trunk(trunk* prev, string str){
		this->prev = prev;
		this->str = str;	
	}
};

void show_tr(trunk* p, int &count){
	if(p == NULL)
		return;
	show_tr(p->prev, count);
	count++;
	cout << p->str;
}

void PR_b_tree(b_tree* tree, trunk* prev, bool is_right){
	if(tree == NULL)
		return;
	string prev_str = "    ";
	trunk* tmp = new trunk(prev, prev_str);
	PR_b_tree(tree->right, tmp, 1);
	if(!prev)
		tmp->str = "---";
	else if(is_right){
		tmp->str = ".---";
		prev_str = "   |";	
	} else {
		tmp->str = "`---";
		prev->str = prev_str;	
	}
	int count = 0;
	show_tr(tmp, count);
	cout << tree->a << endl;

	if(prev)
		prev->str = prev_str;
	tmp->str = "   |";
	PR_b_tree(tree->left, tmp, 0);
}

void PR_forest(forest* f_tree, trunk* prev, bool is_right){
	if(f_tree == NULL){
		return;
    }
	string prev_str = "    ";
	trunk* tmp = new trunk(prev, prev_str);
    int count_br = f_tree->count - 1;
    while(count_br > 0){
    	PR_forest(f_tree->branch[count_br], tmp, 1);
        count_br--;
    }
	if(!prev)
		tmp->str = "---";
	else if(is_right){
		tmp->str = ".---";
		prev_str = "   |";	
	} else {
		tmp->str = "`---";
		prev->str = prev_str;	
	}
	int count = 0;
	show_tr(tmp, count);
	cout << f_tree->a << endl;

	if(prev)
		prev->str = prev_str;
	tmp->str = "   |";
    if(f_tree->count != 0)
	    PR_forest(f_tree->branch[0], tmp, 0);
}

void process(b_tree* tree, forest* f_tree){
    f_tree->branch[f_tree->count] = new forest;
    f_tree->branch[f_tree->count]->count = 0;
    f_tree->branch[f_tree->count]->a = tree->a;
    f_tree->count++;
    if(tree->left != NULL)
        process(tree->left, f_tree->branch[f_tree->count-1]);
    if(tree->right != NULL)
        process(tree->right, f_tree);
}

int pr_elem(forest* f_tree, int cur_level, int level){
    int flag = 0;
    if(cur_level == level){
        cout << f_tree->a;
        return 1;
    }else
        if(f_tree->count)
            for(int i = 0; i < f_tree->count; i++)
                flag += pr_elem(f_tree->branch[i], cur_level+1, level);
        else
            return 0;
    return flag;
}
int pr_elements(forest* f_tree){
    int flag = 1;
    int level = 1;
    while(flag){
        flag = 0;
        flag += pr_elem(f_tree, 0, level);
        level++;
    }
}

void del_b_tree(b_tree* tree){
    if(tree->left != NULL){
        del_b_tree(tree->left);
        delete(tree->left);
    }
    if(tree->right != NULL){
        del_b_tree(tree->right);
        delete(tree->right);
    }
}

void del_forest(forest* f_tree){
    if(f_tree->count){
        for(int i = 0; i < f_tree->count; i++){
            del_forest(f_tree->branch[i]);
            delete(f_tree->branch[i]);
        }
    }
}

int work_with_console(){
    cout << "Введите выражение" << endl;
    string str;
    getline(cin, str);
    getline(cin, str);
    int i = 0;
    while((i=str.find(' '))!=std::string::npos)
        str.erase(i, 1);
    b_tree* tree = new b_tree;
    int count = full_b_tree(tree, str);
    if(count == -1){
        cout << "Неверная строка!" << endl;
        return 0;
    }
    cout << "Бинарное дерево:" << endl;
    PR_b_tree(tree, NULL, 0);
    forest* f_tree = new forest;
    f_tree->a = '*';
    f_tree->count = 0;
    process(tree, f_tree);
    cout << "Лес:" << endl;
    PR_forest(f_tree, NULL, 0);
    cout << "Перечисление элементов в горизонтальном порядке:" << endl;
    pr_elements(f_tree);
    del_b_tree(tree);
    delete(tree);
    del_forest(f_tree);
    delete(f_tree);
    return 0;
}

int work_with_file(){
    cout << "Введите имя файла, в котором записано выражение" << endl;
    string file_name;
    cin >> file_name;
    ifstream f;
    f.open(file_name.c_str());
    if (!f){
        cout << "Файл не открыт!" << endl;
        return 0;
    }
    string str;
    getline(f, str);
    cout << str << endl;
    int i = 0;
    while((i=str.find(' '))!=std::string::npos)
        str.erase(i, 1);
    b_tree* tree = new b_tree;
    int count = full_b_tree(tree, str);
    if(count == -1){
        cout << "Неверная строка!" << endl;
        return 0;
    }
    cout << "Бинарное дерево:" << endl;
    PR_b_tree(tree, NULL, 0);
    forest* f_tree = new forest;
    f_tree->a = '#';
    process(tree, f_tree);
    cout << "Лес:" << endl;
    PR_forest(f_tree, NULL, 0);
    cout << "Перечисление элементов в горизонтальном порядке:" << endl;
    pr_elements(f_tree);
    del_b_tree(tree);
    delete(tree);
    del_forest(f_tree);
    delete(f_tree);
    return 0;
}

int main(){
    pr_menu();
    char way;
    cin >> way;
    while(way != '0'){
        switch (way){
            case '1':
                work_with_console();
                cout << endl;
                pr_menu();
                cin >> way;
                break;
            case '2':
				work_with_file();
                cout << endl;
                pr_menu();
                cin >> way;
                break;
            default:
                cout << "Неверно введены данные!" << endl;
                pr_menu();
                cin >> way;
        }
    }
    return 0;
}
