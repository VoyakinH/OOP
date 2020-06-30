#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <vector>
#include <memory>
#include <iostream>
#include "button.h"
#include "defines.h"

enum direction
{
    DOWN = -1,
    STOP = 0,
    UP = 1
};

enum manager_status
{
    FREE,
    BUSY
};

class manager : public QWidget
{
    Q_OBJECT;

public:
    explicit manager(QWidget *parent = nullptr);
    ~manager() = default;

public slots:
    void new_task(size_t floor);
    void floor_reached(size_t floor, direction dir);
    void vacant_manager();

signals:
    void get_task_signal(size_t floor);
    void stop_signal(size_t floor);
    void vacant_signal();

private:
    manager_status status;
    direction dir;
    size_t current_floor;
    size_t desired_floor;

    std::vector<std::shared_ptr<button>> buttons;
    std::vector<bool> need_stop;
    std::unique_ptr<QVBoxLayout> location;

    bool live_task(size_t &new_floor);
};
