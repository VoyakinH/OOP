#pragma once
#include "Iterator.hpp"
#include "ConstIterator.hpp"
#include "VectorBase.hpp"

template<typename Type>
class Vector: public VectorBase
{
public:
    friend class Iterator<Type>;
    friend class ConstIterator<Type>;

    Vector();
    // У меня спрашивал что такое explicit
    explicit Vector(size_t len);
    Vector(size_t len, Type *arr);
    Vector(size_t len, Type elem, ...);
    Vector(std::initializer_list<Type> elems);
    explicit Vector(const Vector<Type> &vector);
    Vector(Vector<Type> &&vector);

    ~Vector();

    Vector<Type> &operator =(const Vector<Type> &vector);
    Vector<Type> &operator =(std::initializer_list<Type> args);
    Vector<Type> &operator =(Vector<Type> &&vector);

    // Спрашивал что такое isUnit
    bool isZero() const;
    bool isUnit() const;

    Type len() const;

    bool setItem(size_t index, const Type &item);
    Type &getItem(size_t index);
    const Type &getItem(size_t index) const;
    Vector<Type> getUnitV() const;

    Type &operator [](size_t index);
    const Type &operator [](size_t index) const;

    double angle(const Vector<Type> &vector) const;
    bool ifCollinear(const Vector<Type> &vector) const;
    bool ifOrthgonal(const Vector<Type> &vector) const;

    // Сумма двух векторов.
    Vector<Type> operator +(const Vector<Type> &vector) const;
    Vector<Type> &operator +=(const Vector<Type> &vector);
    Vector<Type> sum(const Vector<Type> &vector) const; // Реализовать

    // Разность двух векторов.
    Vector<Type> &operator -=(const Vector<Type> &vector);
    Vector<Type> operator -(const Vector<Type> &vector) const;
    Vector<Type> operator -();
    Vector<Type> sub(const Vector<Type> &vector) const;  // Реализовать

    // Умножение вектора на число.
    Vector<Type> operator *(const Type &num) const;
    Vector<Type> &operator *=(const Type &num);
    Vector<Type> multonum(const Vector<Type> &vector) const;  // Реализовать

    // Скалярное произведение.
    Type operator *(const Vector<Type> &vector) const;
    Type operator *=(const Vector<Type> &vector) const;
    Type mulscal(const Vector<Type> &vector) const;   // Реализовать

    // Векторное произведение.
    Vector<Type> operator &(const Type &num) const;
    Vector<Type> &operator &=(const Type &num);
    Vector<Type> mulvect(const Vector<Type> &vector) const;   // Реализовать

    // Деление вектора на число.
    Vector<Type> &operator /=(const Type& num);
    Vector<Type> operator /(const Type& num) const;
    Vector<Type> divtonum(const Type& num);   // Реализовать

    bool operator ==(const Vector<Type> &vector) const;
    bool operator !=(const Vector<Type> &vector) const;

    Iterator<Type> begin() noexcept;
    Iterator<Type> end() noexcept;
    ConstIterator<Type> begin() const noexcept;
    ConstIterator<Type> end() const noexcept;
private:
    std::shared_ptr<Type> values;  // Вот тут где-то должны быть квадратные скобки но на маке с ними не робит

protected:
    Type summaryValue();
    void allocNewVectorMem(int num);
};

template<typename Type>   // Не обязательно как я понял .
std::ostream &operator <<(std::ostream &os, const Vector<Type> &vector) {
    Iterator<Type> iterator(vector);
    if (!iterator) {
        os<< "Пустой вектор.";
        return os;
    }
    os<< *iterator;
    for (iterator++; iterator; iterator++)
            os<< ", "<< *iterator;
    return os;
}
