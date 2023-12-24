#include "customeffectedmenu.h"
//#include "menuactionproxystyle.h"

//#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPainterPath>

CustomEffectedMenu::CustomEffectedMenu(QWidget* parent) : QMenu(parent)
{
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint); //
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setStyleSheet(
        "QMenu {"
        "   margin: 6px;"
        "   padding: 4px 0px;"
        "   background-color: rgba(35, 35, 35, 100%);"
        "   border: solid;"
        "   border-radius: 8px;"
        "   border-color: rgb(70, 70, 70);"
        "   border-width: 1px;"
        "   color: rgba(255, 255, 255, 70%);"
        "   font: 10pt 'Segoe UI Semibold';"
        "}"
        "QMenu::separator {"
        "   margin: 4px 0px;"
        "   height: 1px;"
        "   background: rgb(70, 70, 70);"
        "}"
        "QMenu::item::label {"
        "   padding-left: 28px;"
        "   padding-right: 32px;"
        "}"


        "QMenu::item {"
        "   margin: 0px 4px;"
        "   background: transparent;"
        "   border-radius: 4px;"
        "   padding: 5px 10px 4px 10px;"
        "}"
        "QMenu::item:selected {"
        "   background-color: rgba(0, 60, 100, 90%);"
        "   color: rgba(255, 255, 255, 100%);"
        "}"
        "QMenu::right-arrow {"
        "   padding-right: 10px;"
        "   width: 10px;"
        "   height: 10px;"
        "   image: url(':/icons/right-arrow-9-white.svg');"
        "}"
    );

    { // initialize shadow brush
        this->brush_pixmap = new QPixmap(12, 12);
        brush_pixmap->fill(Qt::transparent);
        QPainter painter(this->brush_pixmap);

        QRadialGradient gradient(6, 6, 6, 6, 6);
        gradient.setColorAt(0, QColor::fromRgbF(0, 0, 0, 0.1));
        gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
        QBrush brush(gradient);

        painter.fillRect(brush_pixmap->rect(), brush);
        this->shadow_brush = new QBrush();
        this->shadow_brush->setTexture(*brush_pixmap);
        painter.end();
    }

    {
//        connect(this, SIGNAL(aboutToShow()), this, SLOT(adjustLocation()));
        connect(this, &QMenu::aboutToShow, this, &CustomEffectedMenu::adjustLocation);
//        connect(this, , this, &CustomEffectedMenu::adjustLocation);
    }
//    this->setStyle(new MenuActionProxyStyle);
}

void CustomEffectedMenu::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);
    QPainterPath path;
    path.addRoundedRect(QRectF(2, 2, this->width()-this->brush_pixmap->width()-2, this->height()-this->brush_pixmap->height()-2), 8, 8);
    qreal length = path.length();
    qreal pos = 0;
    qreal spacing = 2;
    while (pos < length) {
        qreal percent = path.percentAtLength(pos);
        QRect rect (path.pointAtPercent(percent).x(), path.pointAtPercent(percent).y(), this->brush_pixmap->width(), this->brush_pixmap->height());
        painter.drawPixmap(rect, this->shadow_brush->texture()); // pseudo method, use QPainter and your brush pixmap instead
        pos += spacing;
    }
    painter.end();

    QMenu::paintEvent(e);

    qDebug() << this->x();
    qDebug() << this->y();
}

void CustomEffectedMenu::moveEvent(QMoveEvent *event)
{
    adjusted = false;
    adjustLocation();
    qDebug() << "moveEvent() Called";
}

void CustomEffectedMenu::adjustLocation()
{
    if (adjusted) { return; }
    if (this->x() == 0 && this->y() == 0) { return; }
    if (this->x_origin == this->x() && this->y_origin == this->y()) { return; }
//    if ()
    this->x_origin = this->x()-6;
    this->y_origin = this->y()-6;
    this->adjusted = true;
    if (this->x_origin > 0 && this->y_origin > 0) { this->move(this->x_origin, this->y_origin); }
    qDebug() << "adjustLocation() Called";
}
