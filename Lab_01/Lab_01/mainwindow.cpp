#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QMainWindow>
//#include <QFileDialog>
//#include "task_manager.h"
//#include "cdio.h"
//#include "operations.h"
//#include "object.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    request task;
    task.act = INIT;
    task_manager(task);
}

MainWindow::~MainWindow()
{
    request task;
    task.act = QUIT;
    task_manager(task);
    delete ui;
}

void MainWindow::update_obj_center_info()
{
    if (ui->graphicsView->scene())
    {
        ui->lineEdit_center_x->setText(QString::number(ui->graphicsView->scene()->itemsBoundingRect().center().x()));
        ui->lineEdit_center_y->setText(QString::number(-ui->graphicsView->scene()->itemsBoundingRect().center().y()));
    }
    ui->lineEdit_center_x->repaint();
    return;
}

void MainWindow::on_pushButton_choose_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Выберите 3Д объект", "/Users/Alex/Documents/OOP/Lab_01/Lab_01/3D Objects/", "*.txt");
    ui->lineEdit_file->setText(str);
    return;
}

void MainWindow::on_lineEdit_file_textChanged(const QString &arg1)
{
    if (arg1.length() != 0)
        ui->pushButton_load->setEnabled(1);
    else
        ui->pushButton_load->setEnabled(0);
    return;
}

void MainWindow::draw()
{
    request task_d;
    task_d.act = DRAW;
    struct draw dr;
    dr.QGV = ui->graphicsView;
    dr.h = ui->graphicsView->height();
    dr.w = ui->graphicsView->width();
    task_d.dr = dr;
    show_message(task_manager(task_d));
    ui->graphicsView->repaint();
    return;
}

void MainWindow::on_pushButton_load_clicked()
{
    request task;
    task.act = LOAD_FILE;
    struct load_file lf;
    lf.file_name = ui->lineEdit_file->text().toLocal8Bit().data();
    task.lf = lf;
    show_message(task_manager(task));
    draw();
    update_obj_center_info();
    return;
}

void MainWindow::on_pushButton_unload_clicked()
{
    ui->graphicsView->scene()->clear();
    ui->graphicsView->repaint();
    update_obj_center_info();
    return;
}

void MainWindow::on_button_move_clicked()
{
    request task;
    task.act = MOVE;
    struct move mo;
    bool dx_ok = 1, dy_ok = 1, dz_ok = 1;
    mo.dx = ui->lineEdit_dx->text().toFloat(&dx_ok);
    mo.dy = ui->lineEdit_dy->text().toFloat(&dy_ok);
    mo.dz = ui->lineEdit_dz->text().toFloat(&dz_ok);
    if (!dx_ok || !dy_ok || !dz_ok)
    {
        show_message(INPUT_ERR);
        return;
    }
    task.mo = mo;
    show_message(task_manager(task));
    draw();
    update_obj_center_info();
    return;
}

void MainWindow::on_button_scale_clicked()
{
    request task;
    task.act = SCALE;
    struct scale sc;
    bool kx_ok = 1, ky_ok = 1, kz_ok = 1, xm_ok = 1, ym_ok = 1, zm_ok = 1;
    sc.kx = ui->lineEdit_KX->text().toFloat(&kx_ok);
    sc.ky = ui->lineEdit_KY->text().toFloat(&ky_ok);
    sc.kz = ui->lineEdit_KZ->text().toFloat(&kz_ok);
    if (ui->checkBox_UseCenterScale->isChecked())
    {
        sc.xm = ui->graphicsView->scene()->itemsBoundingRect().center().x();
        sc.ym = ui->graphicsView->scene()->itemsBoundingRect().center().y();
        sc.zm = 0;
    }
    else
    {
        sc.xm = ui->lineEdit_XM->text().toFloat(&xm_ok);
        sc.ym = ui->lineEdit_YM->text().toFloat(&ym_ok);
        sc.zm = ui->lineEdit_ZM->text().toFloat(&zm_ok);
    }
    if (!kx_ok || !ky_ok || !kz_ok || !xm_ok || !ym_ok || ! zm_ok)
    {
        show_message(INPUT_ERR);
        return;
    }
    task.sc = sc;
    show_message(task_manager(task));
    draw();
    update_obj_center_info();
    return;
}

void MainWindow::on_button_rotate_clicked()
{
    request task;
    task.act = ROTATE;
    struct rotate ro;
    bool dgx_ok = 1, dgy_ok = 1, dgz_ok = 1, xc_ok = 1, yc_ok = 1, zc_ok = 1;
    ro.dgx = ui->lineEdit_dgX->text().toInt(&dgx_ok);
    ro.dgy = ui->lineEdit_dgY->text().toInt(&dgy_ok);
    ro.dgz = ui->lineEdit_dgZ->text().toInt(&dgz_ok);
    if (ui->checkBox_UseCenterRotation->isChecked())
    {
        ro.xc = ui->graphicsView->scene()->itemsBoundingRect().center().x();
        ro.yc = ui->graphicsView->scene()->itemsBoundingRect().center().y();
        ro.zc = 0;
    }
    else
    {
        ro.xc = ui->lineEdit_XC->text().toFloat(&xc_ok);
        ro.yc = ui->lineEdit_YC->text().toFloat(&yc_ok);
        ro.zc = ui->lineEdit_ZC->text().toFloat(&zc_ok);
    }
    if (!dgx_ok || !dgy_ok || !dgz_ok || !xc_ok || !yc_ok || ! zc_ok)
    {
        show_message(INPUT_ERR);
        return;
    }
    task.ro = ro;
    show_message(task_manager(task));
    draw();
    update_obj_center_info();
    return;
}
void MainWindow::show_message(const int &err)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    switch(err)
    {
    case OK:
    case OPEN_FILE_ERR:
        msgBox.setText("Не удалось открыть файл, либо он не найден.");
        break;
    case FILE_INCORRECT:
        msgBox.setText("Файл заполнен неверно.");
        break;
    case ALLOCATION_ERR:
        msgBox.setText("Возникла ошибка при выделении памяти.");
        break;
    case POINTS_INCORR:
        msgBox.setText("Кол-во точек должно быть натуральным числом.");
        break;
    case LINKS_INCORR:
        msgBox.setText("Кол-во граней должно быть натуральным числом, либо нулём.");
        break;
    case INPUT_ERR:
        msgBox.setText("Введённые переменные должны быть целого или вещественного типа.");
        break;
    case ARR_UNINITIALIZED:
        msgBox.setText("Массивы вершин и граней не были инициализированы.");
        break;
    case LINKS_CONTAIN_INCORR_POINTS:
        msgBox.setText("Файл заполнен неверно. Грани связывают отсутствующие вершины.");
        break;
    default:
        msgBox.setText("Неизвестная ошибка.");
        break;
    }
    msgBox.exec();
}
