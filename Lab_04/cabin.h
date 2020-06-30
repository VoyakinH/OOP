#pragma once
#include <QObject>
#include <iostream>
#include "doors.h"
#include "manager.h"

enum cabin_status
{
    GET,
    VACANT,
    MOVING
};

class cabin : public QObject
{
    Q_OBJECT;

public:
    explicit cabin();
    ~cabin() = default;

public slots:
    void cab_moving();
    void cab_get_task(size_t floor);
    void cab_stopped(size_t new_floor = 0);

signals:
    void open_doors_signal();
    void floor_reached(size_t floor, direction dir);
    void moving_signal();
    void stopped_signal(size_t = 0);

private:
    doors doors_obj;
    size_t current_floor;
    size_t desired_floor;

    direction dir;
    cabin_status status;

    QTimer move_timer;
};
