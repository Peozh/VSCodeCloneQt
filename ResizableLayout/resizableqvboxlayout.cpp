#include "resizableqvboxlayout.h"

#include <QStyleOption>
#include <QPainter>

ResizableQVBoxLayout::ResizableQVBoxLayout(QWidget* parent)
    : QWidget(parent)
{
    this->setStyleSheet("background-color: rgb(180, 180, 180);");
    layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    this->setLayout(layout);

    line = new HorizontalLineHandle(this);
    line->connectTargetLayout(layout);

    connect(line, SIGNAL(lineDragged()), this, SLOT(updateLineGeometry()));
}

void ResizableQVBoxLayout::resizeEvent(QResizeEvent *event)
{
    updateLineGeometry();
}

void ResizableQVBoxLayout::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

void ResizableQVBoxLayout::addWidget(QWidget *child)
{
    this->layout->addWidget(child);
    line->raise();
}

void ResizableQVBoxLayout::setBaseLineColor(int r, int g, int b, int a)
{
    line->setBaseColor(r, g, b, a);
}

void ResizableQVBoxLayout::updateLineGeometry()
{
    int height =  this->layout->count() >= 2 ? 5 : 0;
    int y = this->layout->count() >= 2 ? this->layout->itemAt(0)->geometry().height() + this->layout->contentsMargins().top() + this->layout->spacing()/2 - height/2 : 0;
    line->setGeometry(0, y, this->geometry().width(), height);
}

