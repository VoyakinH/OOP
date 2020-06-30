#pragma once

#include <QPushButton>
#include <QObject>

enum button_status
{
    active,
    not_active
};

class button : public QPushButton
{
    Q_OBJECT;

public:
    button(QWidget *parent = nullptr);
    ~button() = default;

    void set_floor(const size_t &floor);

public slots:
    void pressed();
    void unpressed();

signals:
    void press_signal(size_t floor);
    void unpress_signal();

private:
    button_status status;
    size_t floor;
};
