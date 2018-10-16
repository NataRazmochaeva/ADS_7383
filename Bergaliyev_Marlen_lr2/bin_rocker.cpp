#include <string>
#include <cstdlib>
#include "bin_rocker.hpp"
#include <stdexcept>


class Bin_rocker::Shoulder {
    class Weight : public Cargo {
    public:
        Weight(std::string::iterator &it) {
            char* num = &(*it);
            size_t count = 0;
            while(isdigit(*it)) {
                ++count;
                ++it;
            }
            if(count == 0)
                throw std::invalid_argument("Missing number");
            weight = atoi(num);
        }
        unsigned int numbers() const {
            return 1;
        }
	std::string to_str() const {
	    return std::to_string(weight);
	}
    private:
        unsigned int weight;
    };

    friend unsigned int Bin_rocker::numbers() const;
    friend std::string Bin_rocker::to_str() const;

public:
    Shoulder(std::string::iterator &it) {
        if(*it != '(')
            throw std::invalid_argument("Missing opening bracket");
        ++it;
        while(isspace(*it))
            ++it;
        size_t count = 0;
        char* num = &(*it);
        while(isdigit(*it)) {
            ++count;
            ++it;
        }
        if(count == 0)
            throw std::invalid_argument("Missing number");
        lenght = atoi(num);
        while(isspace(*it))
            ++it;
        if(*it == '(')
            cargo = new Bin_rocker(it);
        else
            cargo = new Weight(it);
	while(isspace(*it))
	    ++it;
        if(*it != ')')
            throw std::invalid_argument("Missing closing bracket");
	++it;
    }
    ~Shoulder(){
	delete cargo;
    }
private:
    int lenght;
    Cargo* cargo;
};

Bin_rocker::Bin_rocker(std::string::iterator &it) {
    while(isspace(*it))
	++it;
    if(*it != '(')
        throw std::invalid_argument("Missing opening bracket");
    ++it;
    while(isspace(*it))
	++it;
    left = new Shoulder(it);
    while(isspace(*it))
        ++it;
    right = new Shoulder(it);
    while(isspace(*it))
	++it;
    if(*it != ')')
        throw std::invalid_argument("Missing closing bracket");
    ++it;
}

Bin_rocker::~Bin_rocker(){
    delete left;
    delete right;
}

unsigned int Bin_rocker::numbers() const {
    return left->cargo->numbers() + right->cargo->numbers();
}

std::string Bin_rocker::to_str() const {
    std::string result = "((";
    result += std::to_string(left->lenght);
    result.push_back(' ');
    result += left->cargo->to_str();
    result.push_back(')');
    result.push_back(' ');
    result.push_back('(');
    result += std::to_string(right->lenght);
    result.push_back(' ');
    result += right->cargo->to_str();
    result.push_back(')');
    result.push_back(')');
    return result;
}
