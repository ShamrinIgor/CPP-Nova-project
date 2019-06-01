#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDateTimeEdit>
#include <QDateTime>
#include <QTime>
#include <libnova/libnova.h>
#include <ctime>
#include "secondwindow.hpp"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    QDateTime DateTime = ui->dateTimeEdit->dateTime();

    double Lat = ui->doubleSpinBox->value();
    double Lon = ui->doubleSpinBox_2->value();

    auto window = new SecondWindow(this, DateTime, Lat, Lon);
    window->setStyleSheet("background-color:black");
    window->setAttribute(Qt::WA_DeleteOnClose,true);
    window->setModal(true);
    window->show();
}



void MainWindow::on_KorolevButton_clicked() const
{
    ui->doubleSpinBox->setValue(55.54);
    ui->doubleSpinBox_2->setValue(37.49);
}

void MainWindow::on_rightNowButton_clicked() const
{
    QDateTime dt = QDateTime::currentDateTime();
    ui->dateTimeEdit->setDateTime(dt);
}


void MainWindow::on_TokyoButton_clicked() const
{
    ui->doubleSpinBox->setValue(35.65);
    ui->doubleSpinBox_2->setValue(139.5);
}
