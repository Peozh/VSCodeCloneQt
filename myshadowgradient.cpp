#include "myshadowgradient.h"
#include "qpainter.h"

MyShadowGradient::MyShadowGradient(QWidget *parent)
    : QWidget{parent}
{
    this->setAutoFillBackground(false);
//    this->setAttribute(Qt::WA_NoSystemBackground);
//    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void MyShadowGradient::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QLinearGradient linearGradient(0, 0, this->width(), 0);
    linearGradient.setColorAt(0, Qt::transparent);
    linearGradient.setColorAt(0.5, qRgba64(0,0,0,10000));
    linearGradient.setColorAt(1, qRgba64(0,0,0,30000));

    QRect rect(0, 0, this->width(), this->height());
    painter.fillRect(rect, linearGradient);
}
