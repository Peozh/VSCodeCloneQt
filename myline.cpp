#include "myline.h"

MyLine::MyLine(QWidget *parents) : QFrame(parents)
{
    setMouseTracking(true);
//    this->setContentsMargins(0, 0, 0, 0);
//    this->setStyleSheet(R"(
//        QFrame {
//            margin-top: 2px;
//            border: 0px;
//            background-color: #888888;
//        }
//        QFrame::hover {
//            margin-top: 0px;
//            background-color: rgb(40, 120, 255);
//        }
//    )");
}

void MyLine::mousePressEvent(QMouseEvent *event)
{
    if (targetDown == nullptr) return;
    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->globalPosition();
        dragStartGeometryUp = targetUp->geometry();
        dragStartGeometryDown = targetDown->geometry();
    }

    if (!(event->buttons() & Qt::LeftButton)) {
    // No drag, just change the cursor and return
        return;
    }
}

void MyLine::mouseMoveEvent(QMouseEvent* event)
{
    if (this->layout == nullptr) return;
    // The user is moving the cursor.
    // See if the user is pressing down the left mouse button.

    if ( event->buttons() & Qt::LeftButton )
    {
//        targetUp->setMaximumHeight(dragStartTargetGeometry.height() + (dragStartPosition.y() - event->pos().y()));
//        target_->setGeometry( dragStartTargetGeometry.x(), dragStartTargetGeometry.y() - (dragStartPosition.y() - event->pos().y()), target_->width(), target_->height() + (dragStartPosition.y() - event->pos().y()));

        targetDown->setFixedHeight(dragStartGeometryDown.height() + (dragStartPosition.y() - event->globalPosition().y()));
//        qDebug() << event->position().y();
        qDebug() << event->pos().y();
//        this->layout->setStretch();

//        int dy = - dragStartPosition.y() + event->globalPosition().y();
//        if (dy > dragStartGeometryDown.height()) dy = dragStartGeometryDown.height();
//        if (dy < -dragStartGeometryUp.height()) dy = -dragStartGeometryUp.height();
//        int upHeight = dragStartGeometryUp.height() + dy;
//        int downHeight = dragStartGeometryDown.height() - dy;
//        this->layout->setStretch(0, 10000 * upHeight /(upHeight+downHeight));
//        this->layout->setStretch(2, 10000 * downHeight /(upHeight+downHeight));
//        qDebug() << "up : " << upHeight << ", down : " << downHeight;
    }
}

void MyLine::mouseReleaseEvent(QMouseEvent *event)
{
    this->setContentsMargins(0, 1, 0, 0);
}


void MyLine::connectResizeTargetUp(QWidget *target)
{
    this->targetUp = target;
}

void MyLine::connectResizeTargetDown(QWidget *target)
{
    this->targetDown = target;
}

void MyLine::connectLayout(QVBoxLayout *target)
{
    this->layout = target;
}
