#include <chrono>
#include <random>
#include <tuple>
#include "coding.h"

void create_task(std::vector<std::pair<int, char>> &freq, std::string &message, std::string &encoded, CodeTree*(*coding)(std::set<std::pair<int, char>>)){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);
    if(message == "" && encoded == ""){
        int message_len = generator() % 10 + 10;
        if(freq.size() != 0){
            std::string alphabet;
            for(auto i : freq)
                alphabet.append(1, std::get<1>(i));
            for(int i=0; i<message_len; ++i)
                message.append(1, alphabet[generator() % alphabet.length()]);
        }
        else for(int i=0; i<message_len; ++i)
            message.append(1, ('a'+(generator()%26)));
    }
    if(freq.size() == 0){
        std::set<char> alphabet;
        for(auto it : message)
            alphabet.insert(it);
        int count = 0;
        for(char a : alphabet){
            for(char c : message)
                if(a == c)
                    ++count;
            freq.push_back(std::make_pair(count, a));
            count = 0;
        }
    }
    std::set<std::pair<int, char>> freq_table(freq.begin(), freq.end());
    CodeTree* code = coding(freq_table);
    if(encoded == "")
        encoded = code->encode(message);
    else
        message = code->decode(encoded);
    delete code;
    //return std::tuple<std::vector<std::pair<int, char>>, std::string, CodeTree*, std::string>(freq, message, code, encoded);
}

/*auto create_task(std::vector<std::pair<int, char>> freq, std::string message, CodeTree*(*coding)(std::set<std::pair<int, char>>)){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);
    if(message == ""){
        int message_len = generator() % 10 + 10;
        if(freq.size() != 0){
            std::string alphabet;
            for(auto i : freq)
                alphabet.append(1, std::get<1>(i));
            for(int i=0; i<message_len; ++i)
                message.append(1, alphabet[generator() % alphabet.length()]);
        }
        else for(int i=0; i<message_len; ++i)
            message.append(1, ('a'+(generator()%26)));
    }
    if(freq.size() == 0){
        std::set<char> alphabet;
        for(auto it : message)
            alphabet.insert(it);
        for(auto it : alphabet)
            freq.push_back(std::make_pair(generator() % 30 + 1, it));
    }
    std::set<std::pair<int, char>> freq_table(freq.begin(), freq.end());
    CodeTree* code = coding(freq_table);
    std::string encoded = code->encode(message);
    return std::tuple<std::vector<std::pair<int, char>>, std::string, CodeTree*, std::string>(freq, message, code, encoded);
}*/
