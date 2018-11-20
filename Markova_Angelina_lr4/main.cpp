#include "fun.h"

int main() {

    int level=0,bt_depth=0,length=0,elMax=0; //уровень/глубина дерева, длина входной строки, максимальное кол-во элементов
    int check,run=1;
    std::ifstream file;                      //определяем файловый поток
    char name[20];                           //название, используемого файла
    std::string str;                         //строка, вводимая пользователем


    std::cout << "\033[34m\tЗдравствуйте!Выберите что вы хотите:\033[0m\n 1) Нажмите 1, чтобы считать с файла.\n 2) Нажмите 2, чтобы считать с консоли.\n 3) Нажмите 3, чтобы выйти из программы.\n" << std::endl;
    while(run) {
        if(check==0) {                        
            std::cout << "Ваши данные:" << str << std::endl;
            for (int i=0; i<(str.length()); i++) {
                if (str[i]=='(')
                    level++;
                if (str[i]==')')
                    level--;
                if (bt_depth<level) bt_depth=level;
            }

            if (level) {
                std::cout <<"\n\033[31mError! Неверное количество скобок!\033[0m" << std::endl;
                return 0;
            }

            if (!bt_depth) {
                std::cout << "\n\033[31mError! Это не дерево!\033[0m" << std::endl;
                return 0;
            }
            elMax=(int)pow(2.0,(double)bt_depth)-1; //максимальное кол-во элементов в дереве
            binTree<char> user_bt(bt_depth);
            int curr_pos=0;
            if (str[curr_pos]=='(') {
                curr_pos++;
                fill_from_str(&user_bt,str,&curr_pos,-1);
            }
            std::cout << "\n"<< "Бинарное дерево:" << std::endl;
            user_bt.print_tree(0,bt_depth);
            Forest<char> user_forest(elMax+1,bt_depth,bt_depth);
            int posf=1;
            convert_bt_to_forest(&user_bt,&user_forest,0,0,&posf,0);
            std::cout << "\n"<< "Лес:" << std::endl;
            user_forest.print_forest(0,bt_depth);
            std::string * levels= new std::string[bt_depth];
            user_forest.print_horizontal(levels,0,0);
            int index=0;
            std::cout << "\n"<< "Обход леса в ширину: ";
            while(index<bt_depth) {
                std::cout << levels[index];
                index++;
            }
            std::cout << std::endl;

            delete [] levels;
            std::cout<<"Выберите следующую команду:"<<std::endl;
        }
        std::cin>>check;
        std::cin.ignore();
        switch(check) {
        case(1): {
            std::cout << "Введите имя нужного файла:" << std::endl;
            std::cin.getline(name,20);
            file.open(name);
            if (!file.is_open())std::cout << "\n\033[31mВходной файл не может быть открыт!\033[0m\nВыберите следующую команду:" << std::endl;
            else {
                std::getline(file,str);
                file.close();
                check=0;
                continue;
            }
            break;
        }
        case(2): {
            std::cout << "Введите бинарное дерево:" << std::endl;
            std::getline(std::cin,str);
            check=0;
            continue;
        }
        case(3): {
            std::cout<<"\033[34mEnd!"<<std::endl;
            run=0;
            break;
        }
        default: {
            std::cout<<"\033[31mIncorrect pick!\033[0m"<<std::endl;
            run=0;
            break;
        }
        }
    }
    return 0;
}
