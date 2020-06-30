#pragma once
#include "Iterator.h"

template <typename Type>
Iterator<Type>::Iterator(const Iterator<Type> &iterator) noexcept{
    this->wPtr = iterator.wPtr;
    this->curInd = iterator.curInd;
    this->vecLen = iterator.vecLen;
}

template<typename Type>
Iterator<Type>::Iterator(const Vector<Type> &vector) noexcept{
    this->curInd = 0;
    this->vecLen = vector.size();
    this->wPtr = vector.values;
}

template<typename Type>
Type &Iterator<Type>::operator*() {
    this->NullPointerCheck(__LINE__);
    this->ValidityCheck(__LINE__);
    std::shared_ptr<Type> copiedPtr = this->wPtr.lock();
    return copiedPtr.get() + this->curInd;
}

template<typename Type>
const Type &Iterator<Type>::operator*() const {
    this->NullPointerCheck(__LINE__);
    this->ValidityCheck(__LINE__);
    std::shared_ptr<Type> copiedPtr = this->wPtr.lock();
    return copiedPtr.get() + this->curInd();
}

template<typename Type>
Type *Iterator<Type>::operator->() {
    this->NullPointerCheck(__LINE__);
    this->ValidityCheck(__LINE__);
    std::shared_ptr<Type> copiedPtr = this->wPtr.lock();
    return copiedPtr.get() + this->curInd();
}

template<typename Type>
const Type *Iterator<Type>::operator->() const {
    this->NullPointerCheck(__LINE__);
    this->ValidityCheck(__LINE__);
    std::shared_ptr<Type> copiedPtr = this->wPtr.lock();
    return copiedPtr.get() + this->curInd();
}

template<typename Type>
Iterator<Type> &Iterator<Type>::operator=(const Iterator<Type>& iterator){
    iterator->NullPointerCheck(__LINE__);
    this->wPtr = iterator.wPtr;
    this->curInd = iterator.curInd;
    this->vecLen = iterator.vecLen;
    return *this;
}

template<typename Type>
Iterator<Type> &Iterator<Type>::operator+=(size_t num) {
    this->NullPointerCheck(__LINE__);
    this->curInd += num;
    return *this;
}

template<typename Type>
Iterator<Type> Iterator<Type>::operator+(size_t num) const {
    this->NullPointerCheck(__LINE__);
    Iterator<Type> iterator(*this);
    iterator += num;
    return iterator;
}

template <typename Type>
Iterator<Type> &Iterator<Type>::operator-=(size_t num) {
    this->NullPointerCheck(__LINE__);
    this->curInd -= num;
    return *this;
}

template <typename Type>
Iterator<Type> Iterator<Type>::operator-(size_t num) const {
    this->NullPointerCheck(__LINE__);
    Iterator<Type> iterator(*this);
    iterator -= num;
    return iterator;
}

template<typename Type>
Iterator<Type> Iterator<Type>::operator++(int) {
    this->NullPointerCheck(__LINE__);
    ++(*this);
    return *this;
}

template<typename Type>
Iterator<Type> &Iterator<Type>::operator++() {
    this->NullPointerCheck(__LINE__);
    ++curInd;
    return *this;
}

template<typename Type>
Iterator<Type> Iterator<Type>::operator--(int) {
    this->NullPointerCheck(__LINE__);
    --(*this);
    return *this;
}

template<typename Type>
Iterator<Type> &Iterator<Type>::operator--() {
    this->NullPointerCheck(__LINE__);
    --curInd;
    return *this;
}

template<typename Type>
bool Iterator<Type>::operator<(const Iterator<Type> &iter) const {
    this->NullPointerCheck(__LINE__);
    return this->curInd < iter.curInd;
}

template<typename Type>
bool Iterator<Type>::operator<=(const Iterator<Type> &iter) const {
    this->NullPointerCheck(__LINE__);
    return this->curInd <= iter.curInd;
}

template<typename Type>
bool Iterator<Type>::operator>(const Iterator<Type> &iter) const {
    this->NullPointerCheck(__LINE__);
    return this->curInd > iter.curInd;
}

template<typename Type>
bool Iterator<Type>::operator>=(const Iterator<Type> &iter) const {
    this->NullPointerCheck(__LINE__);
    return this->curInd >= iter.curInd;
}

template<typename Type>
bool Iterator<Type>::operator==(const Iterator<Type> &iter) const {
    this->NullPointerCheck(__LINE__);
    return this->curInd == iter.curInd;
}

template<typename Type>
bool Iterator<Type>::operator!=(const Iterator<Type> &iter) const {
    this->NullPointerCheck(__LINE__);
    return this->curInd != iter.curInd;
}

template<typename Type>
Iterator<Type>::operator bool() const noexcept{
    bool res = true;
    if (curInd >= vecLen || vecLen == 0 || curInd < 0)
        res =  false;
    return res;
}

template<typename Type>
void Iterator<Type>::NullPointerCheck(int errLine) const {
    if (this->wPtr.expired())
    {
        time_t currentTime = time(NULL);
        throw DeletedObjectException(__FILE__, typeid(*this).name(), errLine, ctime(&currentTime));
    }
}

template<typename Type>
void Iterator<Type>::ValidityCheck(int errLine) const {
    if (this->curInd >= this->vecLen)
    {
        time_t currentTime = time(NULL);
        throw InvalidIndexException(__FILE__, typeid(*this).name(), errLine, ctime(&currentTime));
    }
}
