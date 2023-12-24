#ifndef VERTICALLINEHANDLE_H
#define VERTICALLINEHANDLE_H

#include "linehandle.h"

class VerticalLineHandle : public LineHandle
{
    Q_OBJECT
public:
    int minimumWidgetWidth = 160;

public:
    VerticalLineHandle(QWidget* parent = nullptr);

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;

public slots:
    virtual void toggleFixedWidget() override;
};

#endif // VERTICALLINEHANDLE_H
