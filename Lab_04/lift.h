#pragma once
#include <QObject>
#include "manager.h"
#include "cabin.h"

class lift : public QObject
{
    Q_OBJECT;
public:
    explicit lift(QObject *parent = nullptr);
    ~lift() = default;

    QWidget *widget();

private:
    manager manager_obj;
    cabin cabin_obj;
};
