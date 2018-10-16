#pragma once

class Cargo{
    public:
        virtual unsigned int numbers() const = 0;
	virtual std::string to_str() const = 0;
	Cargo(){}
	virtual ~Cargo(){}
};


class Bin_rocker : public Cargo{
public:
    Bin_rocker(std::string::iterator&);
    ~Bin_rocker();
    unsigned int numbers() const;
    std::string to_str() const;
private:
    class Shoulder;
    Shoulder* left;
    Shoulder* right;
};

