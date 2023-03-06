#include "mytexteditwithspace.h"

MyTextEditWithSpace::MyTextEditWithSpace(QWidget *parent)
    : QWidget{parent}
{
    auto outter_layout = new QVBoxLayout(this);
    this->setLayout(outter_layout);
    this->p_area = new QScrollArea(this);
    outter_layout->addWidget(this->p_area);
    this->p_contents = new QWidget(p_area);

    this->p_area->setWidgetResizable(true);
    this->setContentsMargins(0, 0, 0, 0);

    this->p_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->p_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->p_area->setContentsMargins(0, 0, 0, 0);
    this->p_area->setWidget(p_contents);


    this->p_contents->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
    this->p_contents->setContentsMargins(0, 0, 0, 0);
    this->p_contents->setGeometry(QRect(0, 0, 492, 447));
    this->p_contents->setStyleSheet("background-color: #ffffff;");

    this->p_layout = new QVBoxLayout(p_contents);
    this->p_textEdit = new QTextEdit(p_contents);
    this->p_space = new QTextEdit(p_contents);

    this->p_contents->setLayout(p_layout);
    this->p_layout->setContentsMargins(0, 0, 0, 0);
    this->p_layout->setSpacing(0);
    this->p_layout->addWidget(p_textEdit);
    this->p_layout->addWidget(p_space);

    auto frameFormat = this->p_textEdit->document()->rootFrame()->frameFormat();
    frameFormat.setBottomMargin(100);
    frameFormat.setRightMargin(10);
    this->p_textEdit->document()->rootFrame()->setFrameFormat(frameFormat);
    this->p_textEdit->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
    this->p_textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->p_textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->p_textEdit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
    this->p_textEdit->setContentsMargins(0, 0, 0, 0);

//    this->p_textEdit->setFixedHeight(this->p_textEdit->document()->size().height());

//    this->p_space->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
//    this->p_space->setFixedHeight(this->height() - this->p_textEdit->height());

//    connect(this->p_textEdit, SIGNAL(textChanged()), this, SLOT(resizeTextEdit()));
//    this->p_space->setBackgroundRole(QPalette::ColorRole::Light);
//    p_textEdit->document()->set
//    p_textEdit->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
//    p_textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    p_textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    p_textEdit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
//    p_space->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
//    p_space->setFixedHeight(this->height());
//    p_space->set

//    p_layout->setSpacing(0);

//    this->setWidget(p_textEdit);
//    p_layout->addWidget(p_textEdit);
//    p_layout->addWidget(p_space);
//    this->setLayout(p_layout);
//    p_textEdit->setFixedSize(100, 100);
//    p_textEdit->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
//    p_textEdit->setGeometry(0, 0, 100, 100);
//    this->setWidgetResizable(true);
//    p_frame->setMinimumSize(400, 400);

//    p_textEdit->setMinimumSize(100, 100);

//    p_textEdit->setMinimumSize(400, 400);

//    this->setWidgetResizable(false);
//    this->setWidget(p_textEdit);
//    this->setLayout(nullptr);
//    this->setLayout(p_layout);

//    this->p_layout->addWidget(p_textEdit);
//    this->p_layout->addWidget(p_space);

//    this->setAlignment(Qt::AlignLeft);
//    this->setAlignment(Qt::AlignTop);

//    this->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
//    p_widget->setLayout(p_layout);
//    p_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

//    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    p_widget->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
//    p_widget->setFixedSize(100, 100);
//    p_widget->setGeometry(0, 0, 100, 100);

//    this->setContentsMargins(0, 0, 0, 0);
//    this->setViewportMargins(0, 0, 0, 0);
//    this->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
//    this->setWidgetResizable(false);
//    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    this->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
//    this->p_textEdit->setGeometry(0, 0, 100, 100);

//    this->p_textEdit->setGeometry(0, 0, this->geometry().width(), this->p_textEdit->document()->size().height());
//    this->p_space->setGeometry(0, this->geometry().bottom()-3, this->width(), 4);
}

void MyTextEditWithSpace::resizeEvent(QResizeEvent *event)
{
//    this->p_frame->setGeometry(0,0, this->width(), this->height());
//    this->widget()->setMinimumHeight(this->height());
//    this->widget()->setMinimumWidth(this->width());
//    this->p_textEdit->setFixedHeight(this->p_textEdit->document()->size().height());
//    this->p_space->setFixedHeight(this->height() - this->p_textEdit->height());
    QWidget::resizeEvent(event);
}

void MyTextEditWithSpace::resizeTextEdit()
{
//    this->p_textEdit->setFixedHeight(this->p_textEdit->document()->size().height() + 2);
}
