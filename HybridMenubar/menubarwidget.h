#ifndef MENUBARWIDGET_H
#define MENUBARWIDGET_H

#include <QWidget>
#include <QMenuBar>

#include "customeffectedmenu.h"
#include "custommenubarextension.h"

class MenuBarWidget : public QWidget
{
    Q_OBJECT

private:
    QList<CustomEffectedMenu*> extension_contents;
    CustomMenuBarExtension* menuBarExt = nullptr;
    int lastActionIdx_old = -2;
public:
    explicit MenuBarWidget(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
public:
    QMenuBar* p_menuBar;
signals:

};

#endif // MENUBARWIDGET_H
