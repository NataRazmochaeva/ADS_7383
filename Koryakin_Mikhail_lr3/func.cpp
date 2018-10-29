#include "func.hpp"      




	  void forstack(string a){
            int i=0;
            int k=0;
            bracket* obj = new bracket[k];
            bool check=false;
            Stack<int> s;
            int n = a.length();
            for(i=0; i<n; i++){
                if(a[i]=='(')
                    s.Push(i);
                if(a[i]==')'){
                    check=true;
                    obj[k].open=s.Pop();
                    obj[k].close=i;
                    k++;
                    bracket* obj = new bracket[k];
                }
            }
            if(s.IsEmpty()){
                if(!check)
                    cout<<"Скобок нет"<<endl;
                else
                    written(k, obj);
            }
            else
                cout<<"Некоректное расположение скобок!"<<endl;
	}



        int comp1(const void* a, const void* b){
            const bracket* k = (const bracket*)a;
            const bracket* m = (const bracket*)b;
            return ((k->open) - (m->open));
        }




        int comp2(const void* a, const void* b){
            const bracket* k = (const bracket*)a;
            const bracket* m = (const bracket*)b;
            return ((k->close) - (m->close));
        }




        void written(int k, struct bracket* obj){
            cout<<"Введите 1 для вывода в порядке возрастания для открывающих скобок, 2 - для закрывающих"<<endl;
            int m;
            int i;
            cin>>m;
            switch (m) {
                case 1:
                        qsort(obj, k, sizeof(bracket), comp1);
                break;
                case 2:
                        qsort(obj, k, sizeof(bracket), comp2);
                break;
            }
            for(i=0; i<k; i++){
                cout<<obj[i].open<<';'<<obj[i].close<<endl;
            }
            delete [] obj;
        }





        string except(string str0){
            int i = 0;
            string nuli = "null";
            while(str0[i]!='\0'){
                if(str0[i]==',')
                    return nuli;
                i++;
            }
            return str0;
        }
