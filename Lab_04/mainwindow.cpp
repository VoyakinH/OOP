#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(200, 300);
    this->location = std::unique_ptr<QVBoxLayout>(new QVBoxLayout);
    this->ui->centralwidget->setLayout(this->location.get());
    this->location->addWidget(this->lift_obj.widget());
}

MainWindow::~MainWindow()
{
    delete ui;
}

