#include "doors.h"
//#include <QObject>
//#include <QTimer>
//#include <iostream>
//#include "defines.h"

doors::doors()
{
    this->status = CLOSED;
    //---------------------------------------------------------------------------//
    QObject::connect(&opening_timer, SIGNAL(timeout()), this, SLOT(opened()));
    QObject::connect(&opened_timer,  SIGNAL(timeout()), this, SLOT(closing()));
    QObject::connect(&closing_timer, SIGNAL(timeout()), this, SLOT(closed()));
    //---------------------------------------------------------------------------//
}

void doors::opening()
{
    std::cout << "Двери открываются." << std::endl;
    if (this->status == CLOSED)
    {
        this->status = OPENING;
        this->opening_timer.start(DOORS_TIME);
    }
    else if (this->status == CLOSING)
    {
        this->status = OPENING;
        auto timer = closing_timer.remainingTime();
        closing_timer.stop();
        this->opening_timer.start(DOORS_TIME - timer);
    }
}

void doors::opened()
{
    if (status == OPENING)
    {
        this->status = OPEN;
        std::cout << "Двери открыты!" << std::endl;
        this->opened_timer.start(DOORS_TIME);
    }
}

void doors::closing()
{
    if (status == OPEN)
    {
        this->status = CLOSING;
        std::cout << "Двери закрываются." << std::endl;
        this->closing_timer.start(DOORS_TIME);
    }
}

void doors::closed()
{
    if (status == CLOSING)
    {
        this->status = CLOSED;
        std::cout << "Двери закрыты." << std::endl;

        emit closed_signal(0);
    }
}
