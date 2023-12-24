#include "horizontallinehandle.h"
#include <QMouseEvent>
#include <QVBoxLayout>

HorizontalLineHandle::HorizontalLineHandle(QWidget* parent)
    : LineHandle(parent)
{
    this->setMaximumHeight(4);
    baseLine->setGeometry(0, 2, this->geometry().width(), 1);

    // set mouse cursor shape
    auto cursor = this->cursor();
    cursor.setShape(Qt::CursorShape::SizeVerCursor);
    this->setCursor(cursor);
}

void HorizontalLineHandle::mousePressEvent(QMouseEvent *event)
{
    if (targetLayout == nullptr) return;
    if (targetLayout->itemAt(0) == nullptr) return;
    if (targetLayout->itemAt(1) == nullptr) return;

    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->globalPosition();
        dragStartGeometry[0] = targetLayout->itemAt(0)->geometry();
        dragStartGeometry[1] = targetLayout->itemAt(1)->geometry();

        fixedWidgetIndex = -1; // default both resizeable
        if (this->targetLayout->itemAt(0)->widget()->sizePolicy().verticalPolicy() == QSizePolicy::Fixed) fixedWidgetIndex = 0;
        if (this->targetLayout->itemAt(1)->widget()->sizePolicy().verticalPolicy() == QSizePolicy::Fixed) fixedWidgetIndex = 1;
    }
}

void HorizontalLineHandle::resizeEvent(QResizeEvent *event)
{
    baseLine->setGeometry(0, 2, this->geometry().width(), 1);
    activeLine->setGeometry(0, 0, this->geometry().width(), 5);
}

void HorizontalLineHandle::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    if (this->targetLayout == nullptr) return;
    if (this->targetLayout->itemAt(0) == nullptr) return;
    if (this->targetLayout->itemAt(1) == nullptr) return;

    // User is moving cursor.
    // See if the user is pressing down the left mouse button.
    if ( event->buttons() & Qt::LeftButton )
    {
        float dy = dragStartPosition.y() - event->globalPosition().y();
        if (fixedWidgetIndex == -1) // set layout stretch
        {
            reinterpret_cast<QVBoxLayout*>(targetLayout)->setStretch(0, dragStartGeometry[0].height() - dy);
            reinterpret_cast<QVBoxLayout*>(targetLayout)->setStretch(1, dragStartGeometry[1].height() + dy);
        }
        else
        {
            if (fixedWidgetIndex == 0) dy *= -1;
            int new_height = dragStartGeometry[fixedWidgetIndex].height() + dy;
            int max_height = targetLayout->geometry().height() - (targetLayout->contentsMargins().top() + targetLayout->contentsMargins().bottom()) - 1;
            int min_height = 0;
            if (new_height > max_height) new_height = max_height;
            if (new_height < min_height) new_height = min_height;
            targetLayout->itemAt(fixedWidgetIndex)->widget()->setFixedHeight(new_height);
        }
        emit lineDragged();
    }
}

// 가능한 조합 : fixed + fixed -> 둘 모두 fixed 수정(임의의 일시적으로 고정된 값인 경우) or 수정 불가하게 비활성화(값 변경 시 깨지는 영구적인 값인 경우)
//              fixed + expanding == fixed + preferred -> fixed 만 수정
//              fixed + minimumExpanding ->  fixed 수정, minimum 이하는 불가하게 막기
//              fixed + maximum -> fixed 수정, maximum 이상 불가하게 막기
//              minimumExpanding + expanding == minimum + expanding -> minimum 만 수정
//              preferred + preferred, preferred + maximum, preferred + minimum
