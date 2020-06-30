#include "button.h"
//#include <QPushButton>
//#include <QObject>

button::button(QWidget *parrent) : QPushButton(parrent)
{
    //------------------------------------------------------------------------//
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(pressed()));
    QObject::connect(this, SIGNAL(unpress_signal()), this, SLOT(unpressed()));
    //------------------------------------------------------------------------//

    this->status = not_active;
    this->floor = 1;
}

void button::set_floor(const size_t &floor)
{
    this->floor = floor;
}

void button::pressed()
{
    if (status == not_active)
    {
        this->setStyleSheet("background-color:green;");
        this->update();
        this->status = active;
        emit press_signal(this->floor);
    }
}

void button::unpressed()
{
    if (status == active)
    {
        this->setStyleSheet("background-color:white;");
        this->update();
        this->status = not_active;
    }
}
