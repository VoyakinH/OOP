#pragma once
#include <QObject>
#include <QTimer>
#include <iostream>
#include "defines.h"

enum doors_status
{
    OPEN,
    OPENING,
    CLOSING,
    CLOSED
};

class doors : public QObject
{
    Q_OBJECT;

public:
    doors();
    ~doors() = default;

public slots:
    void opened();
    void closed();

private slots:
    void opening();
    void closing();

signals:
    void closed_signal(size_t);

private:
    doors_status status;
    QTimer opening_timer;
    QTimer closing_timer;
    QTimer opened_timer;
};
