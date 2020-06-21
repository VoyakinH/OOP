#pragma once
#include <iostream>

class IteratorBase
{
public:
    IteratorBase();
    IteratorBase(const IteratorBase&);

    virtual ~IteratorBase() = 0;
protected:
    size_t curInd = 0;
    size_t vecLen = 0;
};
