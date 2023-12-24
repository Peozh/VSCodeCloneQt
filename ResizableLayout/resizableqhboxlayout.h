#ifndef RESIZABLEQHBOXLAYOUT_H
#define RESIZABLEQHBOXLAYOUT_H

#include "ResizableLayout/verticallinehandle.h"

#include <QVBoxLayout>

class ResizableQHBoxLayout : public QWidget
{
    Q_OBJECT
    VerticalLineHandle* line;

public:
    ResizableQHBoxLayout(QWidget* parent = nullptr);
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent* event) override;

    void addWidget(QWidget* child);
    void setBaseLineColor(int r, int g, int b, int a);

public:
    QHBoxLayout* layout;

public slots:
    void updateLineGeometry();
};

#endif // RESIZABLEQHBOXLAYOUT_H
