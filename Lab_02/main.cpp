#include <iostream>
#include "Vector.hpp"

int main()
{
    Vector<double> initializing = {1, 2, 3};
    const Vector<int> constVect = {0, 1, 2, 3, 4};
    Vector<float> lenExample(3);
    Vector<double> lenFillExample(3, 6.66);
    Vector<long double> emptyVector(0);

    std::cout<< "Вектор с инициализацией: "<< initializing<< std::endl;
    std::cout<< "Вектор с заданной длиной: "<< lenExample<< std::endl;
    std::cout<< "Вектор заданной длины с инициализацией: "<< lenFillExample<< std::endl;
    std::cout<< "Пустой вектор: "<< emptyVector<< std::endl;

    Vector<int> operVecF = {1, 2, 1};
    Vector<int> operVecS = {3, 2, 4};

    std::cout<< "Длина вектора: "<<initializing.len()<< std::endl;
    std::cout<< "Нулевой ли вектор: "<<initializing.isZeroVector()<< std::endl;
    std::cout<< "Единичный ли вектор: "<<initializing.isUnitVector()<< std::endl;
    std::cout<< "Угол между векторами: "<< lenFillExample.angle(initializing)<< std::endl;


    std::cout<< "Установка второго элемента в 10: "<<initializing.setItem(1, 10)<< std::endl;
    std::cout<< "Второй элемент вектора: "<<initializing.getItem(1)<< std::endl;
    std::cout<< "Второй элемент константного вектора: "<<constVect.getItem(1)<< std::endl;
    std::cout<< "Векторы *: "<< operVecF * operVecS<< std::endl;
    std::cout<< "Векторы +: "<< operVecF + operVecS<< std::endl;
    std::cout<< "Векторы -: "<< operVecF - operVecS<< std::endl;

    Vector<float> orthVecF = {1, 0, 0};
    Vector<float> orthVecS = {0, 1, 0};
    Vector<float> nonOrthVec = {1, 2, 3};

    std::cout<< "Ортогональность: "<< orthVecF.ifOrthgonal(orthVecS)<< std::endl;
    std::cout<< "Не ортогональность: "<<orthVecF.ifOrthgonal(nonOrthVec)<< std::endl;

    Vector<int> colVecF = {1, 1, 0};
    Vector<int> colVecS = {1, 1, 0};

    std::cout<< "Коллинеарность: "<< colVecF.ifCollinear(colVecS)<< std::endl;
    std::cout<< "Не коллинеарность: "<< colVecF.ifCollinear(operVecF)<< std::endl;

    try {
        orthVecF.ifCollinear(lenExample);
    } catch (ZeroDivisionException &er) {
        std::cout<< "Пойманная ошибка:"<< er.what()<< std::endl;
    }
    return 0;
}
