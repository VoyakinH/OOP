#pragma once
#include <iostream>

class VectorBase
{
public:
    VectorBase();
    VectorBase(const VectorBase&);
    virtual ~VectorBase() = 0;

    virtual size_t size() const;
    virtual operator bool() const;
protected:
    size_t vector_size = 0;
};
