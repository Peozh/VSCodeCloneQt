#include "myuppertextpart.h"

MyUpperTextPart::MyUpperTextPart(QWidget *parent)
    : QWidget{parent}
{
    this->p_layout = new QVBoxLayout(this);
    this->p_stacked = new QStackedWidget(this);
//    QFrame* frame = new QFrame(this);
//    frame->setFrameShape(QFrame::Shape::NoFrame);
//    frame->setLineWidth(0);
    this->p_page = new MyEditorPage(this);
//    this->p_page->setGeometry(10, 10, 200, 100);

    this->p_stacked->addWidget(p_page);

    this->p_layout->addWidget(this->p_stacked);
    this->p_layout->setContentsMargins(0, 0, 0, 1);
    this->p_layout->setSpacing(0);
    this->setLayout(this->p_layout);
    this->setContentsMargins(0, 0, 0, 0);

    // overlay
    // set line
    this->p_line = new MyLine(this);
    this->p_line->setGeometry(0, this->p_stacked->geometry().bottom()-2, this->width(), 4);
//    this->p_line->setGeometry(0, this->geometry().bottom()-3, this->width(), 4);
    this->p_line->connectResizeTargetUp(this->p_stacked);


}

void MyUpperTextPart::resizeEvent(QResizeEvent *event)
{
    this->p_line->setGeometry(0, this->p_stacked->geometry().bottom()-2, this->width(), 4);
}
