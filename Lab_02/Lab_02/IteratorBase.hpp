#pragma once
#include "IteratorBase.h"

IteratorBase::IteratorBase()
{
    this->curInd = 0;
    this->vecLen = 0;
}

IteratorBase::IteratorBase(const IteratorBase& iterator)
{
    this->curInd = iterator.curInd;
    this->vecLen = iterator.vecLen;
}

IteratorBase::~IteratorBase() { }
