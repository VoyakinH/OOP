#include "manager.h"
//#include <QWidget>
//#include <QVBoxLayout>
//#include <vector>
//#include <memory>
//#include <iostream>
//#include "button.h"
//#include "defines.h"

manager::manager(QWidget *parent) : QWidget(parent)
{
    //----------------------------------------------------------------------------//
    QObject::connect(this, SIGNAL(vacant_signal()), this, SLOT(vacant_manager()));
    //----------------------------------------------------------------------------//

    this->location = std::unique_ptr<QVBoxLayout>(new QVBoxLayout);
    this->setLayout(this->location.get());

    for (int i = 0; i < FLOORS_NUM; i++)
    {
        std::shared_ptr<button> btn(new button);
        btn->set_floor(FLOORS_NUM - i);
        btn->setText(QString::number(FLOORS_NUM - i));
        btn->setStyleSheet("background-color:white;");

        this->buttons.insert(buttons.begin(), btn);
        this->location->addWidget(dynamic_cast<QPushButton *>(btn.get()));

        this->need_stop.push_back(false);
        //--------------------------------------------------------------------------------------//
        QObject::connect(btn.get(), SIGNAL(press_signal(size_t)), this, SLOT(new_task(size_t)));
        //--------------------------------------------------------------------------------------//
    }
}

void manager::new_task(size_t floor)
{
    this->status = BUSY;
    this->need_stop[floor - 1] = true;

    this->live_task(floor);
    this->desired_floor = floor;
    emit get_task_signal(floor);
}

void manager::floor_reached(size_t floor, direction dir)
{
    if (status == BUSY)
    {
        this->current_floor = floor;
        this->dir = dir;

        if (current_floor == desired_floor)
        {
            std::cout << "Остановка на этаже: " << floor << std::endl;

            emit this->buttons[floor - 1]->unpress_signal();
            this->need_stop[floor - 1] = false;

            if (live_task(floor))
            {
                this->desired_floor = floor;

                emit stop_signal(floor);
            }
            else
            {
                emit vacant_signal();
                emit stop_signal(floor);
            }
        }
    }
}


void manager::vacant_manager()
{
    this->status = FREE;
}

bool manager::live_task(size_t &new_floor)
{
    int dir = this->dir != STOP ? this->dir : DOWN;
    bool stop = false;

    for (int i = this->current_floor - 1; i >= 0 && i < FLOORS_NUM && !stop; i += dir)
    {
        if (this->need_stop[i])
        {
            new_floor = i + 1;
            stop = true;
        }
    }

    for (int i = this->current_floor - 1; i >= 0 && i < FLOORS_NUM && !stop; i -= dir)
    {
        if (this->need_stop[i])
        {
            new_floor = i + 1;
            stop = true;
        }
    }

    return stop;
}
