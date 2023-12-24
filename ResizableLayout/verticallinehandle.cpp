#include "verticallinehandle.h"
#include <QMouseEvent>
#include <QHBoxLayout>

VerticalLineHandle::VerticalLineHandle(QWidget* parent)
    : LineHandle(parent)
{
    this->setMaximumWidth(4);
    baseLine->setGeometry(2, 0, 1, this->geometry().height());

    // set mouse cursor shape
    auto cursor = this->cursor();
    cursor.setShape(Qt::CursorShape::SizeHorCursor);
    this->setCursor(cursor);
}

void VerticalLineHandle::mousePressEvent(QMouseEvent *event)
{
    if (targetLayout == nullptr) return;
    if (targetLayout->itemAt(0) == nullptr) return;
    if (targetLayout->itemAt(1) == nullptr) return;

    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->globalPosition();
        dragStartGeometry[0] = targetLayout->itemAt(0)->geometry();
        dragStartGeometry[1] = targetLayout->itemAt(1)->geometry();

        fixedWidgetIndex = -1; // default both resizeable
        if (this->targetLayout->itemAt(0)->widget()->sizePolicy().horizontalPolicy() == QSizePolicy::Fixed) fixedWidgetIndex = 0;
        if (this->targetLayout->itemAt(1)->widget()->sizePolicy().horizontalPolicy() == QSizePolicy::Fixed) fixedWidgetIndex = 1;
    }
}

void VerticalLineHandle::resizeEvent(QResizeEvent *event)
{
    baseLine->setGeometry(2, 0, 1, this->geometry().height());
    activeLine->setGeometry(0, 0, 4, this->geometry().height());
}

void VerticalLineHandle::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    if (this->targetLayout == nullptr) return;
    if (this->targetLayout->itemAt(0) == nullptr) return;
    if (this->targetLayout->itemAt(1) == nullptr) return;

    // User is moving cursor.
    // See if the user is pressing down the left mouse button.
    if ( event->buttons() & Qt::LeftButton )
    {
        float dx = event->globalPosition().x() - dragStartPosition.x();
        if (fixedWidgetIndex == -1) // set layout stretch
        {
            reinterpret_cast<QHBoxLayout*>(targetLayout)->setStretch(0, dragStartGeometry[0].width() + dx);
            reinterpret_cast<QHBoxLayout*>(targetLayout)->setStretch(1, dragStartGeometry[1].width() - dx);
        }
        else // fixed, toggled when dragging at minimumWidgetWidth/2 point
        {
            if (fixedWidgetIndex != 0) dx *= -1;
            int new_width = dragStartGeometry[fixedWidgetIndex].width() + dx;
            int max_width = targetLayout->geometry().width() - (targetLayout->contentsMargins().left() + targetLayout->contentsMargins().right()) - 1;
            int min_width = minimumWidgetWidth;
            auto* fixedWidget = targetLayout->itemAt(fixedWidgetIndex)->widget();
            if (new_width < min_width/2) { // toggle (minimize)
                if (fixedWidget->isVisible()) {
                    fixedWidget->setFixedWidth(0);
                    fixedWidget->setVisible(false);
                }
            } else { // change fixed width
                if (!fixedWidget->isVisible()) {
                    fixedWidget->setVisible(true);
                    fixedWidget->setFixedWidth(minimumWidgetWidth);
                }
                if (new_width > max_width) new_width = max_width;
                if (new_width < min_width) new_width = min_width;
                fixedWidget->setFixedWidth(new_width);
            }
        }
        emit lineDragged();
    }
}

void VerticalLineHandle::toggleFixedWidget()
{
    if (fixedWidgetIndex == -1) return;
    auto* fixedWidget = targetLayout->itemAt(fixedWidgetIndex)->widget();
    if (fixedWidget->isVisible()) {
        fixedWidget->setVisible(false);
        fixedWidget->setFixedWidth(0);
    } else {
        fixedWidget->setVisible(true);
        fixedWidget->setFixedWidth(minimumWidgetWidth);
    }
}
