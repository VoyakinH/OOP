#pragma once
#include "Vector.h"
#include <limits>
#include <math.h>

// Конструктор пустого вектора.
template<typename Type>
Vector<Type>::Vector() {
    vector_size = 0;
    allocNewVectorMem(vector_size);
}

// Конструктор вектора нужной длины.
template<typename Type>
Vector<Type>::Vector(size_t len) {
    time_t currentTime = time(NULL);
    if (len < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    vector_size = len;
    allocNewVectorMem(vector_size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator(*this);
    for (; iterator; iterator++)
        *iterator = 0;
}

// Конструктор на основе массива.
template<typename Type>
Vector<Type>::Vector(size_t len, Type *arr) {
    time_t currentTime = time(NULL);
    if (len <= 0)
        throw EmptyVectorException(__FILE__, typeod(*this).name(), __LINE__, ctime(&currentTime));
    if (!arr)
        throw InvalidCopyArrayPointer(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    vector_size = len;
    allocNewVectorMem(vector_size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator(*this);
    for (int i = 0; iterator; iterator++, i++)
        *iterator = arr[i];
}

// Конструктор на основе элементов.
template<typename Type>
Vector<Type>::Vector(size_t len, Type elem, ...) {
    time_t currentTime = time(NULL);
    if (len < 1)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    vector_size = len;
    allocNewVectorMem(vector_size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator(*this);
    va_list var;
    va_start(var, elem);
    for (; iterator; iterator++)
    {
        *iterator = elem;
        elem = va_arg(var, Type);
    }
    va_end(var);
}

// Конструктор с инициализацией.
template<typename Type>
Vector<Type>::Vector(std::initializer_list<Type> arguments) {
    if (arguments.size() == 0)
    {
        Vector();
        return;
    }
    time_t currentTime = time(NULL);
    vector_size = int(arguments.size());
    allocNewVectorMem(vector_size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator(*this);
    for (auto &currentItem : arguments)
    {
        *iterator = currentItem;
        iterator++;
    }
}

// Конструктор от вектора.
template<typename Type>
Vector<Type>:: Vector(const Vector<Type> &vector) {
    time_t currentTime = time(NULL);
    vector_size = vector.vector_size;
    allocNewVectorMem(vector_size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator_new(*this);
    Iterator<Type> iterator(vector);
    for (; iterator_new; iterator++, iterator_new++)
        *iterator_new = *iterator;
}

// Конструктор с захватом.
template<typename Type>
Vector<Type>:: Vector(Vector<Type> &&vector) {
    time_t currentTime = time(NULL);
    vector_size = vector.vector_size;
    allocNewVectorMem(vector_size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    values = vector.values;
    vector.values = nullptr;
}

// Деструктор.
template<typename Type>
Vector<Type>::~Vector() {
    if (values)
        values.reset();
}

// Сумма двух векторов.
template <typename Type>
void Vector<Type>::vecSum(Vector<Type> &res, const Vector<Type> &fV, const Vector<Type> &sV) const
{
    Iterator<Type> resIter(res);
    Iterator<Type> fIter(fV);
    Iterator<Type> sIter(sV);
    for (size_t i = 0; resIter; i++, resIter++, fIter++, sIter++)
    {
        if (i < fV.vector_size && i < sV.vector_size)
            *resIter = *fIter + *sIter;
        else if (i >= fV.vector_size)
            *resIter = *fIter;
        else
            *resIter = *sIter;
    }
}

// Разница двух векторов.
template<typename Type>
void Vector<Type>::vecSub(Vector<Type> &res, const Vector<Type> &fV, const Vector<Type> &sV) const {
    Iterator<Type> resIter(res);
    Iterator<Type> fIter(fV);
    Iterator<Type> sIter(sV);
    for (size_t i = 0; resIter; i++, resIter++, fIter++, sIter++)
    {
        if (i < fV.vector_size && i < sV.vector_size)
            *resIter = *fIter - *sIter;
        else if (i >= fV.vector_size)
            *resIter = *fIter;
        else
            *resIter = -*sIter;
    }
}

// Произведение двух векторов.
template<typename Type>
void Vector<Type>::vecMul(Vector<Type> &res, const Vector<Type> &fV, const Vector<Type> &sV) const{
    Iterator<Type> resIter(res);
    Iterator<Type> fIter(fV);
    Iterator<Type> sIter(sV);
    for (size_t i = 0; resIter; i++, resIter++, fIter++, sIter++)
    {
        if (i < fV.vector_size && i < sV.vector_size)
            *resIter = *fIter * *sIter;
        else
            *resIter = 0;
    }
}

// Выделение памяти под новый вектор.
template<typename Type>
void Vector<Type>::allocNewVectorMem(int num) {
    time_t currentTime = time(NULL);
    try
    {
        values.reset();
    }
    catch (std::bad_alloc &exception)
    {
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    }
    std::shared_ptr<Type> temp(new Type[num], std::default_delete<Type[]>());
    values = temp;
}

// Угол между векторами.
template<typename Type>
double Vector<Type>::angle(const Vector<Type> &vector) const
{
    time_t currentTime = time(NULL);
    if (!this->len() || !vector.len())
        throw ZeroDivisionException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    double angle = (*this * vector) / (this->len() * vector.len());
    if (angle > 1) angle--;
    return acos(angle) * 180 / M_PI;
}

// Проверка коллинеарности векторов.
template<typename Type>
bool Vector<Type>::ifCollinear(const Vector<Type> &vector) const {
    if (this->angle(vector) < __DBL_EPSILON__)
        return true;
    return false;
}

// Проверка ортогональности векторов.
template<typename Type>
bool Vector<Type>::ifOrthgonal(const Vector<Type> &vector) const {
    if (this->angle(vector) - 90 < __DBL_EPSILON__)
        return true;
    return false;
}

// Получение единичного вектора.
template<typename Type>
Vector<Type> Vector<Type>::getUnitV() const {
    Vector<Type> unitVector(*this);
    Type len = this->length;
    Iterator<Type> iterator(unitVector);
    for (; iterator; iterator++)
        *iterator /= len;
    return unitVector;
}

// Получение элемента по индексу.
template<typename Type>
Type &Vector<Type>::getItem(size_t index) {
    time_t currentTime = time(NULL);
    if (index < 0 || index >= vector_size)
        throw InvalidIndexException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator(*this);
    for (size_t i = 0; i < index; i++, iterator++) { }
    return *iterator;
}

// Получение элемента по индексу Const.
template<typename Type>
const Type &Vector<Type>::getItem(size_t index) const {
    time_t currentTime = time(NULL);
    if (index < 0 || index >= vector_size)
        throw InvalidIndexException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator(*this);
    for (int i = 0; i < index; i++, iterator++) { }
    return *iterator;
}

// Установка элемента по индексу.
template<typename Type>
bool Vector<Type>::setItem(size_t index, const Type& item)
{
    if (index < 0 || index >= vector_size)
        return false;
    Iterator<Type> iterator(*this);
    for (size_t i = 0; i < index; i++, iterator++) { }
    (*iterator) = item;
    return true;
}

// Проверка на единичный вектор.
template<typename Type>
bool Vector<Type>::isUnitVector() const {
    if (fabs(this->len() - 1) < __DBL_EPSILON__)
        return true;
    return false;
}

// Проверка на нулевую длину вектора.
template<typename Type>
bool Vector<Type>::isZeroVector() const {
    if (this->len() == 0)
        return true;
    return false;
}

// Суммирование всех элементов.
template<typename Type>
Type Vector<Type>::summaryValue() {
    time_t currentTime = time(NULL);
    if (vector_size <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator(*this);
    Type summary = 0;
    for (; iterator; iterator++)
        summary += *iterator;
    return summary;
}

// Вычисление длины вектора.
template<typename Type>
double Vector<Type>::len(void) const {
    time_t currentTime = time(NULL);
    if (vector_size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator(*this);
    Type sum = 0;
    for (; iterator; iterator++)
        sum += *iterator * *iterator;
    sum = sqrt(sum);
    return sum;
}

// Равны ли вектора.
template<typename Type>
bool Vector<Type>::operator ==(const Vector<Type> &vector) const {
    time_t currentTime = time(NULL);
    if (vector_size < 0 || vector.vector_size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    if (vector_size != vector.vector_size)
        return false;
    Iterator<Type> fIter(*this);
    Iterator<Type> sIter(vector);
    for (; fIter; sIter++, fIter++)
        if (fabs(*fIter - *sIter) > __DBL_EPSILON__)
            return false;
    return true;
}

// Различны ли вектора.
template<typename Type>
bool Vector<Type>::operator !=(const Vector<Type> &vector) const {
    time_t currentTime = time(NULL);
    if (vector_size < 0 || vector.vector_size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    if (vector_size != vector.len())
        return true;
    Iterator<Type> fIter(*this);
    Iterator<Type> sIter(vector);
    for (; fIter; sIter++)
        if (*fIter != *sIter)
            return true;
    return false;
}

// Добавление к текущему.
template<typename Type>
Vector<Type> &Vector<Type>::operator +=(const Vector<Type> &vector) {
    time_t currentTime = time(NULL);
    if (vector_size < 0 || vector.vector_size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    vecSum(*this, *this, vector);
    return *this;
}

// Вычесть из текущего.
template<typename Type>
Vector<Type> &Vector<Type>::operator -=(const Vector<Type> &vector) {
    time_t currentTime = time(NULL);
    if (vector_size < 0 || vector.vector_size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    vecDif(*this, *this, vector);
    return *this;
}

// Умножить текущий на константу.
template<typename Type>
Vector<Type> &Vector<Type>::operator *=(const Type &num) {
    time_t currentTime = time(NULL);
    if (vector_size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator(*this);
    for (; iterator; iterator++)
        *iterator *= num;
    return *this;
}

// Разделить текущий на константу.
template<typename Type>
Vector<Type> &Vector<Type>::operator /=(const Type &num) {
    time_t currentTime = time(NULL);
    if (vector_size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator(*this);
    for (; iterator; iterator++)
        *iterator /= num;
    return *this;
}

// Оператор сложения.
template<typename Type>
Vector<Type> Vector<Type>::operator +(const Vector<Type> &vector) const{
    time_t currentTime = time(NULL);
    if (vector_size < 0 || vector.vector_size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    size_t maxLength = std::max(vector_size, vector.vector_size);
    Vector<Type> newVector(maxLength);
    vecSum(newVector, *this, vector);
    return newVector;
}

// Оператор вычитания.
template<typename Type>
Vector<Type> Vector<Type>::operator -(const Vector<Type> &vector) const {
    time_t currentTime = time(NULL);
    if (vector_size < 0 || vector.vector_size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    int maxLength = std::max(vector_size, vector.vector_size);
    Vector<Type> newVector(maxLength);
    vecSub(newVector, *this, vector);
    return newVector;
}

// Оператор умножения.
template<typename Type>
Type Vector<Type>::operator *(const Vector<Type> &vector) const {
    time_t currentTime = time(NULL);
    if (vector_size <= 0 || vector.vector_size <= 0)
        EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    int maxLength = std::max(vector_size, vector.vector_size);
    Vector<Type> newVector(maxLength);
    vecMul(newVector, *this, vector);
    return newVector.summaryValue();
}

// Оператор умножения.
template<typename Type>
Type Vector<Type>::operator /(const Vector<Type> &vector) const {
    time_t currentTime = time(NULL);
    if (vector_size <= 0 || vector.vector_size <= 0)
        EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    int maxLength = std::max(vector_size, vector.vector_size);
    Vector<Type> newVector(maxLength);
    vecDiv(newVector, *this, vector);
    return newVector.summaryValue();
}

// Оператор индексации.
template<typename Type>
Type &Vector<Type>::operator [](int index) {
    return getItem(index);
}

// Оператор индексации Const.
template<typename Type>
const Type &Vector<Type>::operator [](int index) const {
    return getItem(index);
}

// Оператор вычитания вектора из самого себя.
template<typename Type>
Vector<Type> Vector<Type>::operator -() {
    Vector<Type> newVector(*this);
    Iterator<Type> iterator(newVector);
    for (; iterator; iterator++)
        *iterator = -*iterator;
    return newVector;
}

// Оператор присвоения от вектора по ссылке.
template<typename Type>
Vector<Type> &Vector<Type>::operator =(const Vector<Type> &vector) {
    time_t currentTime = time(NULL);
    vector_size = vector.vector_size;
    allocNewVectorMem(vector_size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iteratorTo(*this);
    Iterator<Type> iteratorFrom(vector);
    for (; iteratorTo; iteratorTo++, iteratorFrom++)
        *iteratorTo = *iteratorFrom;
    return *this;
}

// Оператор присвоения при инициализации.
template<typename Type>
Vector<Type> &Vector<Type>::operator =(std::initializer_list<Type> arguments) {
    time_t currentTime = time(NULL);
    vector_size = int(arguments.size());
    allocNewVectorMem(vector_size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    Iterator<Type> iterator(*this);
    for (auto &currentItem : arguments)
    {
        *iterator = currentItem;
        iterator++;
    }
    return *this;
}

// Оператор захвата.
template<typename Type>
Vector<Type> &Vector<Type>::operator =(Vector<Type> &&vector) {
    time_t currentTime = time(NULL);
    vector_size = vector.vector_size;
    allocNewVectorMem(vector_size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    values = vector.values;
    vector.values = nullptr;
    return *this;
}

template<typename Type>
Iterator<Type> Vector<Type>::begin() noexcept {
    Iterator<Type> iterator(*this);
    return iterator;
}

template<typename Type>
Iterator<Type> Vector<Type>::end() noexcept{
    Iterator<Type> iterator(*this);
    return iterator + this->vector_size;
}

template<typename Type>
ConstIterator<Type> Vector<Type>::begin() const noexcept {
    ConstIterator<Type> iterator(*this);
    return iterator;
}

template<typename Type>
ConstIterator<Type> Vector<Type>::end() const noexcept{
    ConstIterator<Type> iterator(*this);
    return iterator + this->vector_size;
}
