#ifndef SECONDWINDOW_HPP
#define SECONDWINDOW_HPP
#include <QDateTimeEdit>
#include <QDateTime>
#include <libnova/libnova.h>
#include <cmath>
#include <array>
#include <QDialog>

constexpr std::size_t N = 8;
namespace Ui {
class SecondWindow;
}
class SecondWindow : public QDialog
{
private:
    Ui::SecondWindow *ui;

    std::array<double, N> alt;
    std::array<int, N> x;
    std::array<int, N> y;

public:


     explicit SecondWindow(QWidget *parent = 0, QDateTime Datetime = QDateTime::currentDateTime(), double lat = 0, double lon = 0);
    ~SecondWindow();
    bool event(QEvent *event) override;
    int Check_Mouse_pos(const QPoint &pos);
    void paintEvent(QPaintEvent *) override;
};

#endif
