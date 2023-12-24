#ifndef HYBRIDMENUBAR_H
#define HYBRIDMENUBAR_H

#include "menubarwidget.h"

#include <QMenuBar>

class HybridMenuBar : public QWidget
{
    Q_OBJECT
public:
    HybridMenuBar(QWidget* parent = nullptr);
    virtual void paintEvent(QPaintEvent* event) override;

public:
    MenuBarWidget* p_menuBarWidget;

private slots:
    void moveWindowTo(QPointF);
};

#endif // HYBRIDMENUBAR_H
