#pragma once
#include "VectorBase.h"

VectorBase::VectorBase()
{
    this->vector_size = 0;
}

VectorBase::VectorBase(const VectorBase& base)
{
   this-> vector_size = base.vector_size;
}

VectorBase::~VectorBase() { }

size_t VectorBase::size() const
{
    return this->vector_size;
}

VectorBase::operator bool() const
{
    return bool(this->vector_size);
}
