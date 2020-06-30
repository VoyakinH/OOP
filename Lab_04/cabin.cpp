#include "cabin.h"
//#include <QObject>
//#include <iostream>
//#include "doors.h"
//#include "manager.h"

cabin::cabin()
{
    this->status = VACANT;
    this->current_floor = 1;
    this->desired_floor = 1;
    this->dir = STOP;

    //------------------------------------------------------------------------------------------//
    QObject::connect(&move_timer, SIGNAL(timeout()), this, SLOT(cab_moving()));
    QObject::connect(this, SIGNAL(moving_signal()), this, SLOT(cab_moving()));
    QObject::connect(this, SIGNAL(stopped_signal(size_t)), this, SLOT(cab_stopped(size_t)));
    QObject::connect(this, SIGNAL(open_doors_signal()), &doors_obj, SLOT(opening()));
    QObject::connect(&doors_obj, SIGNAL(closed_signal(size_t)), this, SLOT(cab_get_task(size_t)));
    //------------------------------------------------------------------------------------------//
}

// Исправить логику сначала запускаем таймер а потом едем (прибавляем этаж)
void cabin::cab_moving()
{
    if (status == MOVING || status == GET)
    {
        this->status = MOVING;
        if (this->current_floor == this->desired_floor)
            emit floor_reached(this->current_floor, this->dir);
        else
        {
            this->move_timer.start(MOVING_TIME);
            std::cout << "Этаж: " << this->current_floor << std::endl;
            this->dir = this->current_floor > this->desired_floor ? DOWN : UP;
            this->current_floor = this->current_floor > this->desired_floor ?
                        this->current_floor - 1 : this->current_floor + 1;
        }
    }
}

void cabin::cab_stopped(size_t new_floor)
{
    if (status == MOVING)
    {
        this->status = VACANT;
        this->move_timer.stop();
        this->desired_floor = new_floor;

        emit open_doors_signal();
    }
}

void cabin::cab_get_task(size_t floor)
{
        this->status = GET;
        if (floor != 0)
            this->desired_floor = floor;

        if (this->current_floor == this->desired_floor)
        {
            emit floor_reached(this->current_floor, this->dir);
        }
        else
        {
            this->dir = this->desired_floor > this->current_floor ? UP : DOWN;

            emit moving_signal();
        }
}

