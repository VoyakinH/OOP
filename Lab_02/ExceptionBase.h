#ifndef EXCEPTIONBASE_H
#define EXCEPTIONBASE_H

#include <exception>
#include <iostream>

// Попросил меня переименовать этот класс. так что в exceptions надо поменять.
class ExceptionVector: public std::exception
{
public:
    ExceptionVector(std::string fileName, std::string className, int curLine, const char *errTime, std::string info);
    virtual const char *what() const noexcept override;
protected:
    std::string errInfo;
};

#endif // EXCEPTIONBASE_H
