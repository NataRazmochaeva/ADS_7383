#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include "main.h"
#include "codetree.h"

using namespace std;

void Main::menu() {
    cout << "1. Shannon-Fano coding/decoding" << endl;
    cout << "2. Huffman coding/decoding" << endl;
    cout << "0. Exit" << endl;
}

string Main::fileRead() {
    string fileName;
    string message;
    cout << "What`s the file name?" << endl;
    cin >> fileName;
    cout << "--------------" << endl;
    cout << "Reading from " << fileName << endl;
    cout << "--------------" << endl;
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile) {
        cout << "Cannot find this file" << endl;
        cout << endl;
        return "";
    }
    string result;
    while (!inFile.eof()) {
        getline(inFile, message);
        if (message.empty()) continue;
        result += message;
    }
    cout << result << endl;
    inFile.close();
    return result;
}

void Main::getHuffman() {
    string message;
    message = fileRead();
    if (message.empty()) {
        return;
    }
    CodeTree *huffman = huffmanCode(message);
    char *huffCode = encode(huffman, message);
    int decodingLength = message.size();
    vector<string> stringRows;
    char *decodeFano = decode(huffman, huffCode, stringRows);
    cout << "------------------------" << endl;
    cout << "3. We`ve just got tree`s leafs" << endl;
    cout << "4. Now we should build the huffman tree" << endl;
    cout << " Remember: assign 1 to leafs with smaller weights (left)" << endl;
    cout << "    and assign 0 to leafs with larger weights (right)" << endl;
    cout << "------------------------" << endl;
    displayTree(huffman, 1);
    cout << "------------------------" << endl;
    cout << "5. As we can see it`s very simple to create a binary code to the each character in our text" << endl;
    cout << "6. Finally go to write it" << endl;
    cout << huffCode << endl;
    cout << "___________ Decoding Huffman algorithm ___________" << endl;
    cout << "We received the prefix code that can be decoded very easy using the binary tree" << endl;
    for (int i = 0; i < decodingLength; i++) {
        cout << "[" << i << "] " << stringRows[i] << endl;
    }
    cout << "Result decoding message = " << decodeFano << endl;
    cout << endl;
}

void Main::getFanoShannon() {
    string message;
    message = fileRead();
    if (message.empty()) {
        return;
    }
    CodeTree *fsTree = fanoShanon(message);
    int decodingLength = message.size();
    vector<string> stringRows;
    char *fsCode = encode(fsTree, message);
    char *decodeFano = decode(fsTree, fsCode, stringRows);
    cout << "3. We`ve just got tree`s leafs" << endl;
    cout << "4. Now we should build the Shannon-Fano tree" << endl;
    cout << " Remember: assign 1 to leafs with smaller weights (left)" << endl;
    cout << "    and assign 0 to leafs with larger weights (right)" << endl;
    cout << "------------------------" << endl;
    displayTree(fsTree, 1);
    cout << "------------------------" << endl;
    cout << "5. As we can see it`s very simple to create a binary code to the each character in our text" << endl;
    cout << "6. Finally go to write it" << endl;
    cout << fsCode << endl;
    cout << "___________ Decoding Shannon-Fano algorithm ___________" << endl;
    cout << "We received the prefix code that can be decoded using the binary tree very easy" << endl;
    for (int i = 0; i < decodingLength; i++) {
        cout << "[" << i << "] " << stringRows[i] << endl;
    }
    cout << "Result decoding message = " << decodeFano << endl;
    cout << endl;
}


int main() {
    Main main;
    while (true) {
        main.menu();
        cin >> main.choice;
        switch (main.choice) {
            case 1:
                main.getFanoShannon();
                break;
            case 2:
                main.getHuffman();
                break;
            case 0:
                exit(1);
        }
    }
}