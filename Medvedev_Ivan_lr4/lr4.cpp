#include "BT.hpp"

#include <fstream>


    int main(){
        BinaryTree b;
        int i = 0, lvl;
        string string;
        char forSwitch;
        while (true){
            i = 0;
            cout<<"Press 1 to read from console, press 2 to read from file, press 0 to exit."<<endl;
            cin >> forSwitch;
            switch (forSwitch) {
                case '2':{
                    ifstream infile("BT.txt");
                    if(!infile){
                        cout<<"There is no file BT.txt"<<endl;
                        continue;
                    }
                    getline(infile, string);
                    break;
                }
                case '1':{
                    cout<<"Enter the BT"<<endl;
                    cin>>string;
                    break;
                }
                case '0':{
                    return 0;
                }
                default:{
                    cout<<"Incorrect input"<<endl;
                    break;
                }
            }
            b.readBT(string, i);
            cout<<"Height of binary tree: "<<b.height()<<endl;
            cout<<"Enter level of tree"<<endl;
            cin>>lvl;
            cout<<"Number of nodes on the "<<lvl<<" level: "<<b.nodesLvl(lvl)<<endl;
            cout<<"Leafs: ";
            b.leafs();
            cout<<endl;
            cout<<"Internal length: "<<b.internal_lenght()<<endl;
            b.~BinaryTree();
        }


}


