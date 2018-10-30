#include "func.hpp"      




	  void forstack(string a){
            int i=0;
            int k=0;
            bracket* arr_bracket = new bracket[k];
            bool check=false;
            Stack<int> s;
            int n = a.length();
            for(i=0; i<n; i++){
                if(a[i]=='(')
                    s.Push(i);
                if(a[i]==')'){
                    check=true;
                    arr_bracket[k].open=s.Pop();
                    arr_bracket[k].close=i;
                    k++;
                    bracket* arr_bracket = new bracket[k];
                }
            }
            if(s.IsEmpty()){
                if(!check)
                    cout<<"Скобок нет"<<endl;
                else
                    written(k, arr_bracket);
            }
            else
                cout<<"Некоректное расположение скобок!"<<endl;
	}



        int comp_open(const void* a, const void* b){
            const bracket* k = (const bracket*)a;
            const bracket* m = (const bracket*)b;
            return ((k->open) - (m->open));
        }




        int comp_close(const void* a, const void* b){
            const bracket* k = (const bracket*)a;
            const bracket* m = (const bracket*)b;
            return ((k->close) - (m->close));
        }




        void written(int k, struct bracket* arr_bracket){
            cout<<"Введите 1 для вывода в порядке возрастания для открывающих скобок, 2 - для закрывающих"<<endl;
            int m;
            int i;
            cin>>m;
            switch (m) {
                case 1:
                        qsort(arr_bracket, k, sizeof(bracket), comp_open);
                break;
                case 2:
                        qsort(arr_bracket, k, sizeof(bracket), comp_close);
                break;
            }
            for(i=0; i<k; i++){
                cout<<arr_bracket[i].open<<';'<<arr_bracket[i].close<<endl;
            }
            delete [] arr_bracket;
        }





        string except(string str0){
            int i = 0;
            string nuli = "null";
            while(str0[i]!='\0'){
                if(str0[i]=='('){
			if(str0[i+1]==')')
				return nuli;
		}   
                i++;
            }
            return str0;
        }
