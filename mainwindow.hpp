#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QDateTimeEdit>
#include <QPainter>
#include <QEvent>
#include "libnova/libnova.h"
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;

private slots:


    void on_startButton_clicked();


    void on_KorolevButton_clicked() const;
    void on_rightNowButton_clicked() const;
    void on_TokyoButton_clicked() const;
};

#endif
