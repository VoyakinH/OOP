#include "Exceptions.h"
#include "IteratorBase.hpp"
#include <memory>
#include <time.h>

template <typename Type>
class Vector;

template <typename Type>
class Iterator: public IteratorBase, public std::iterator<std::input_iterator_tag, Type>
{
public:
    Iterator(const Iterator<Type> &iterator) noexcept;
    Iterator(const Vector<Type> &vector) noexcept;

    Type &operator *();
    const Type &operator *() const;
    Type *operator ->();
    const Type *operator ->() const;
    operator bool() const noexcept;

    Iterator<Type> &operator=(const Iterator<Type> &iterator);

    Iterator<Type> &operator-=(size_t number);
    Iterator<Type> operator-(size_t number) const;
    Iterator<Type> &operator--();
    Iterator<Type> operator--(int number);

    Iterator<Type> &operator+=(size_t number);
    Iterator<Type> operator+(size_t number) const;
    Iterator<Type> &operator++();
    Iterator<Type> operator++(int number);

    bool operator<=(const Iterator<Type> &iterator) const;
    bool operator<(const Iterator<Type> &iterator) const;
    bool operator>=(const Iterator<Type> &iterator) const;
    bool operator>(const Iterator<Type> &iterator) const;
    bool operator==(const Iterator<Type> &iterator) const;
    bool operator!=(const Iterator<Type> &iterator) const;

private:
    std::weak_ptr<Type> wPtr;  // Так же кв. скобки.
protected:
    void NullPointerCheck(int errLine) const;
    void ValidityCheck(int errLine) const;
};
