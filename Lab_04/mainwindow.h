#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <memory>
#include "lift.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<QVBoxLayout> location;
    lift lift_obj;
};
