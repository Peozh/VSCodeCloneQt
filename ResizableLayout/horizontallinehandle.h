#ifndef HORIZONTALLINEHANDLE_H
#define HORIZONTALLINEHANDLE_H

#include "linehandle.h"

class HorizontalLineHandle : public LineHandle
{
    Q_OBJECT
public:
    HorizontalLineHandle(QWidget* parent = nullptr);

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // HORIZONTALLINEHANDLE_H
