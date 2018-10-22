#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include "binkor.h"
#include "main.h"
#include "action.h"

using namespace std;

void Action::start(std::string str) {
    stringstream sstream;
    string resultStr;

    if (str.empty()) {
        cout << "The entering string is empty!" << endl;
        return;
    }
    resultStr = getResultString(str);
    if (resultStr.empty())
        return;

    sstream << resultStr;
    BinKor list(sstream);

    int answer = list.getWeight();
    cout << "Full weight of the binary rocket = " << answer << endl;
    cout << endl;
}

string Action::getResultString(string str) {
    string midStr;
    for (char c : str) {
        if (c == '(') {
            if (isspace(midStr.back()))
                midStr.erase(midStr.size() - 1, 1);
            midStr.push_back(c);
        } else if (c == ' ') {
            if (isdigit(midStr.back()))
                midStr.push_back(c);
        } else if (c == ')') {
            if (isspace(midStr.back()))
                midStr.erase(midStr.size() - 1, 1);
            midStr.push_back(c);
        } else if (isdigit(c)) {
            midStr.push_back(c);
        } else {
            cout << "Unexpected char [ " << str << " ]" << endl;
            cout << endl;
            return "";
        }
    }
    for (int i = 0; i < midStr.size(); i++) {
        switch (midStr[i]) {
            case '(':
                i++;
                if (midStr[i] == '(') {
                    i++;
                    if (isdigit(midStr[i]))
                        continue;
                }
                cout << "Error. Wrong string format" << endl;
                return "";
            case ')':
                i++;
                if (midStr[i] == '(') {
                    i++;
                    if (isdigit(midStr[i]))
                        continue;
                } else if (str[i] == ')')
                    continue;
                cout << "Error. Wrong string format" << endl;
                return "";
        }
        return midStr;
    }
}
