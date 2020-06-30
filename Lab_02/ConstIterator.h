#pragma once
#include "Exceptions.h"
#include "IteratorBase.hpp"
#include <memory>
#include <time.h>

template <typename Type>
class Vector;

template <typename Type>
class ConstIterator: public IteratorBase, public std::iterator<std::input_iterator_tag, Type>
{
public:
    ConstIterator(const ConstIterator<Type> &iterator) noexcept;
    ConstIterator(const Vector<Type> &vector) noexcept;

    const Type &operator *() const;
    const Type *operator ->() const;
    operator bool() const noexcept;

    ConstIterator<Type> &operator=(const ConstIterator<Type> &iterator);

    ConstIterator<Type> &operator-=(size_t number);
    ConstIterator<Type> operator-(size_t number) const;
    ConstIterator<Type> &operator--();
    ConstIterator<Type> operator--(int number);

    ConstIterator<Type> &operator+=(size_t number);
    ConstIterator<Type> operator+(size_t number) const;
    ConstIterator<Type> &operator++();
    ConstIterator<Type> operator++(int number);

    bool operator<=(const ConstIterator<Type> &boolean) const;
    bool operator<(const ConstIterator<Type> &boolean) const;
    bool operator>=(const ConstIterator<Type> &boolean) const;
    bool operator>(const ConstIterator<Type> &boolean) const;
    bool operator==(const ConstIterator<Type> &boolean) const;
    bool operator!=(const ConstIterator<Type> &boolean) const;
private:
    std::weak_ptr<Type> wPtr;  // кв. скобки
protected:
    void NullPointerCheck(int errLine) const;
    void ValidityCheck(int errLine) const;
};
