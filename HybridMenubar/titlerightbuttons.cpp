#include "titlerightbuttons.h"

#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>

TitleRightButtons::TitleRightButtons(QWidget *parent)
    : QWidget{parent}
{
    auto* w = new QWidget(this);
    {
        auto policy = w->sizePolicy();
        policy.setHorizontalPolicy(QSizePolicy::Expanding);
        policy.setVerticalPolicy(QSizePolicy::Fixed);
        w->setSizePolicy(policy);
        w->setStyleSheet("QWidget { background-color: rgba(45, 45, 45, 0%); }");
    }

    this->minimize_button = new FlatButton(this);
    {
        minimize_button->setColors(QColor{45, 45, 45}, QColor{80, 80, 80}, QColor{130, 130, 130});
        minimize_button->setIcon(QIcon(":/icons/minimize-white-128.png"));
        connect(minimize_button, SIGNAL(clicked(bool)), this, SLOT(emitMinimizeSignal()));
    }
    this->maximize_button = new FlatButton(this);
    {
        maximize_button->setColors(QColor{45, 45, 45}, QColor{80, 80, 80}, QColor{130, 130, 130});
        maximize_button->setIcon(QIcon(":/icons/maximize-white-128.png"));
        connect(maximize_button, SIGNAL(clicked(bool)), this, SLOT(emitProperMaximizeSignals()));
    }
    auto* layout = new QHBoxLayout(this);
    {
        layout->addWidget(w);
        layout->addWidget(minimize_button);
        layout->addWidget(maximize_button);
        layout->setStretch(0, 1);
        layout->setStretch(1, 0);
        layout->setStretch(2, 0);
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
    }

    {
        constexpr int fixedHeight = 30;
        auto policy = this->sizePolicy();
        policy.setHorizontalPolicy(QSizePolicy::Preferred);
        policy.setVerticalPolicy(QSizePolicy::Fixed);
        this->setSizePolicy(policy);
        this->setMinimumWidth(205);
        this->setFixedHeight(fixedHeight);
        this->setStyleSheet("TitleRightButtons { background-color: rgba(45, 45, 45, 0%); }");
        this->setContentsMargins(0, 0, 0, 0);
        this->setLayout(layout);
    }
}

void TitleRightButtons::emitMinimizeSignal()
{
    emit minimizePressed();
}

void TitleRightButtons::emitProperMaximizeSignals()
{
    this->shouldMaximize = !shouldMaximize;
    if (shouldMaximize)
    {
        maximize_button->setIcon(QIcon(":/icons/restore-white-128.png"));
        emit maximizePressed();
    }
    else
    {
        maximize_button->setIcon(QIcon(":/icons/maximize-white-128.png"));
        emit restorePressed();
    }
}


void TitleRightButtons::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}
