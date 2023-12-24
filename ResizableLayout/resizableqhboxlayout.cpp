#include "resizableqhboxlayout.h"

#include <QStyleOption>
#include <QPainter>

ResizableQHBoxLayout::ResizableQHBoxLayout(QWidget *parent)
    : QWidget{parent}
{
    this->setStyleSheet("background-color: rgb(180, 180, 180);");
    layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    this->setLayout(layout);

    line = new VerticalLineHandle(this);
    line->connectTargetLayout(layout);

    connect(line, SIGNAL(lineDragged()), this, SLOT(updateLineGeometry()));
}

void ResizableQHBoxLayout::resizeEvent(QResizeEvent *event)
{
    updateLineGeometry();
}

void ResizableQHBoxLayout::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

void ResizableQHBoxLayout::addWidget(QWidget *child)
{
    this->layout->addWidget(child);
    line->raise();
}

void ResizableQHBoxLayout::setBaseLineColor(int r, int g, int b, int a)
{
    line->setBaseColor(r, g, b, a);
}

void ResizableQHBoxLayout::updateLineGeometry()
{
    int width =  this->layout->count() >= 2 ? 5 : 0;
    int x = this->layout->count() >= 2 ? this->layout->itemAt(0)->geometry().width() + this->layout->contentsMargins().left() + this->layout->spacing()/2 - width/2 : 0;
    line->setGeometry(x, 0, width, this->geometry().height());
}

