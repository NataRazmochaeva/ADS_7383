#include "fun.h"
#define Type char
#define elMax 50

int main() {
    int check = 1, run = 1;

    std::ifstream file;                      //определяем файловый поток
    char name[20];                           //название, используемого файла
    std::string str;                         //строка, вводимая пользователем
    int i = -1;
    std::cout << "\033[34m\tЗдравствуйте!Выберите, что вы хотите:\033[0m\n 1) Нажмите 1, чтобы считать с файла.\n 2) Нажмите 2, чтобы считать с консоли.\n 3) Нажмите 3, чтобы выйти из программы.\n" << std::endl;
    while(run) {
        if(!check) {
        	binTree<Type> user_bt(elMax);
        	char c;
        	for(c = getchar(); c == ' ' && c != '\n'; c = getchar());
        	while(c != EOF && c != '\n'){
				if(c != '('){
					std::cout << "Incorrect input" << std::endl;
					exit(1);
				} 
				user_bt.fill_from_input(i);
				for(c = getchar(); c == ' ' && c != '\n'; c = getchar());
			}
            std::cout << "\n"<< "Бинарное дерево:" << std::endl;
            user_bt.printTree(0, nullptr, true);
            int bt_depth = user_bt.depth(0);
            std::cout << "Глубина: " <<  bt_depth << std::endl;
            Forest<Type> user_forest(elMax+1,bt_depth,bt_depth);
            int posf=1;
            convert_bt_to_forest(&user_bt,&user_forest,0,0,&posf,0);
            std::cout << "\n"<< "Лес:" << std::endl;
            user_forest.print_forest(0,bt_depth);
	    std::string * levels= new std::string[bt_depth];
            user_forest.print_horizontal(levels,0,0);
            std::cout << "Выберите следующую команду:" << std::endl;

        }
    	std::cin >> check;
        std::cin.ignore();
        switch(check) {
        case(1):
            std::cout << "Введите имя нужного файла:" << std::endl;
            std::cin.getline(name,20);
            file.open(name);
            if (!file.is_open())
            	std::cout << "\n\033[31mВходной файл не может быть открыт!\033[0m\nВыберите следующую команду:" << std::endl;
            else {
                std::getline(file,str);
                file.close();
                check=0;
                continue;
            }
            break;
        case(2):
            std::cout << "Введите бинарное дерево:" << std::endl;
            check = 0;
            continue;
        case(3): 
            std::cout<<"\033[34mEnd!"<<std::endl;
            run = 0;
            break;
        default:
            std::cout<<"\033[31mIncorrect pick!\033[0m"<<std::endl;
            run = 0;
            break;
        }
    }
}
