#ifndef RESIZABLEQVBOXLAYOUT_H
#define RESIZABLEQVBOXLAYOUT_H

#include "ResizableLayout/horizontallinehandle.h"

#include <QVBoxLayout>

class ResizableQVBoxLayout : public QWidget
{
    Q_OBJECT
    HorizontalLineHandle* line;

public:
    ResizableQVBoxLayout(QWidget* parent = nullptr);
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent* event) override;

    void addWidget(QWidget* child);
    void setBaseLineColor(int r, int g, int b, int a);

public:
    QVBoxLayout* layout;

private slots:
    void updateLineGeometry();
};

#endif // RESIZABLEQVBOXLAYOUT_H
