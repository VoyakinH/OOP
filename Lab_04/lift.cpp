#include "lift.h"
//#include <QObject>
//#include "manager.h"
//#include "cabin.h"

lift::lift(QObject *parent) : QObject(parent)
{
    //-------------------------------------------------------------------------------------------------------------------------//
    QObject::connect(&cabin_obj, SIGNAL(floor_reached(size_t, direction)), &manager_obj, SLOT(floor_reached(size_t, direction)));
    QObject::connect(&manager_obj, SIGNAL(get_task_signal(size_t)), &cabin_obj, SLOT(cab_get_task(size_t)));
    QObject::connect(&manager_obj, SIGNAL(stop_signal(size_t)), &cabin_obj, SLOT(cab_stopped(size_t)));
    //-------------------------------------------------------------------------------------------------------------------------//
}

QWidget *lift::widget()
{
    return &this->manager_obj;
}
