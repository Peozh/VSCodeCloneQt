#ifndef MYLINE_H
#define MYLINE_H

#include <QFrame>
#include <QObject>
#include <QMouseEvent>
#include <QVBoxLayout>

class MyLine : public QFrame
{
    Q_OBJECT

    QPointF dragStartPosition;
    QRect dragStartGeometryUp;
    QRect dragStartGeometryDown;
    QWidget* targetUp = nullptr;
    QWidget* targetDown = nullptr;
    QVBoxLayout* layout = nullptr;
public:
    explicit MyLine(QWidget* parents = nullptr);
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

    void connectResizeTargetUp(QWidget* target);
    void connectResizeTargetDown(QWidget* target);
    void connectLayout(QVBoxLayout* target);
};

#endif // MYLINE_H
