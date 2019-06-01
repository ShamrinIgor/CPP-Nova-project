#include "secondwindow.hpp"
#include "ui_secondwindow.h"
#include "QPainter"
#include "mainwindow.hpp"
#include <cmath>
#include <QDialog>
#include <QDesktopWidget>
#include <QToolTip>

constexpr double COF_tD = M_PI/360;

void (*ptr_get_equ_cd[N])(double, ln_equ_posn*) = {&ln_get_lunar_equ_coords, &ln_get_jupiter_equ_coords, &ln_get_mars_equ_coords,
      &ln_get_saturn_equ_coords, &ln_get_pluto_equ_coords, &ln_get_mercury_equ_coords, &ln_get_neptune_equ_coords,
        &ln_get_venus_equ_coords};

std::array<const QString,N> planet_name = {"lunar", "jupiter", "mars", "saturn", "pluto", "mercury", "neptune", "venus"};

void Dec_coord(double lat, double lon, double JD, std::array<int, N>& x, std::array<int, N>& y, std::array<double, N>& alt,
               double width, double hieght)
{
    ln_lnlat_posn observer;
    observer.lat = lat;
    observer.lng = lon;
    for (std::size_t i = 0; i < N; i++)
    {
        ln_equ_posn equ;
        (*ptr_get_equ_cd[i])(JD, &equ);
        ln_hrz_posn posn;
        ln_get_hrz_from_equ(&equ ,&observer, JD, &posn);
        alt[i] = posn.alt;
        if (alt[i] > 0)
        {
            x[i] = width/2 + (hieght/2)*std::cos((posn.alt)*COF_tD)*std::cos((posn.az)*COF_tD)/(1 + std::sin((posn.alt)*COF_tD));
            y[i] = width/2 + (hieght/2)*std::cos((posn.alt)*COF_tD)*std::sin((posn.az)*COF_tD)/(1 + std::sin((posn.alt)*COF_tD));
        }
    }
}

void My_Painter(QPainter& planet,int x, int y, int a, Qt::GlobalColor color)
{
    planet.setBrush(QBrush(color, Qt::SolidPattern));
    planet.drawEllipse(x, y, a, a);
}


SecondWindow::SecondWindow(QWidget *parent, QDateTime Datetime, double lat, double lon) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    setMouseTracking(true);
    setBackgroundRole(QPalette::Base);
    ui->setupUi(this);
    QRect r = QApplication::desktop()->screenGeometry();
    this->resize(r.width() * 0.6, r.height() * 0.8);

    std::time_t DataTime_time_t = Datetime.toTime_t();
    double JD = ln_get_julian_from_timet(&DataTime_time_t);
    for (std::size_t i = 0 ; i < N ; i++)
    {
        Dec_coord(lat, lon, JD, x, y, alt, 0.6*r.width(), 0.8*r.height());
    }
}

SecondWindow::~SecondWindow()
{
    delete ui;
}
int SecondWindow::Check_Mouse_pos(const QPoint &pos)
{
    for (std::size_t i = 0; i < N; i++)
    {
        if ((std::abs(x[i] - pos.x()) < 10) && (std::abs(y[i] - pos.y()) < 10))
            return i;
    }
    return -1;
}
bool SecondWindow::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip)
    {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
        int index = Check_Mouse_pos(helpEvent->pos());
        if (index != -1)
        QToolTip::showText(helpEvent->globalPos(),planet_name[index]);
        else
        {
            QToolTip::hideText();
            event->ignore();
        }
        return true;
    }
    return QWidget::event(event);
}
void SecondWindow::paintEvent(QPaintEvent*)
{
        std::array<Qt::GlobalColor, N> Colors = {Qt::blue, Qt::red, Qt::yellow, Qt::darkYellow, Qt::darkGray,
        Qt::cyan, Qt::darkBlue, Qt::darkRed};
        std::array<const int, N> size = {15, 10, 8, 5, 3, 6, 4, 7};

        QPainter painter(this);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        for (std::size_t i = 0; i < N; i++)
        {
            if (alt[i] > N)
            {
                My_Painter(painter, x[i], y[i], size[i], Colors[i]);
            }
        }
}

