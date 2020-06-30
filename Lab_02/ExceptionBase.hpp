#pragma once
#include "ExceptionBase.h"

ExceptionBase::ExceptionBase(std::string fileName, std::string className, int curLine, const char *errTime, std::string info)
{
    errInfo = "\nFile: " + fileName + "\nClass: " + className + "\nLine: " + std::to_string(curLine) + "\nTime: " + errTime + "\nInfo: " + info;
}

const char *ExceptionBase::what() const noexcept
{
    return errInfo.c_str();
}
