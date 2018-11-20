#include <exception>
#include <iostream>
#include <cstring>

using namespace std;

#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

class analyzer_err : public exception
{
public:
    analyzer_err(int index, const char* exp="") noexcept
    {
    sprintf(msg, "Index: %d, Error msg: ", index+1);
        msg = strcat(msg, exp);
    }
    virtual const char* what() const noexcept
    {
        return msg;
    }
    virtual ~analyzer_err(){}
private:
    char* msg;
};
class client_err : public exception
{
public:
    client_err(const char* exp) noexcept
    {
        msg = exp;
    }
    virtual const char* what() const noexcept
    {
        return msg;
    }
    virtual ~client_err(){}
private:
    const char* msg;
};

#endif // MYEXCEPTION_H
