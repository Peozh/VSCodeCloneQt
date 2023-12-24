#ifndef SIDEMENUBAR_H
#define SIDEMENUBAR_H

#include "sidemenubarbutton.h"

#include <QObject>
#include <QWidget>

class SideMenubar : public QWidget
{
    Q_OBJECT
    SideMenubarButton* buttonMemory = nullptr;

private:
    std::vector<SideMenubarButton*> buttons;
public:
    explicit SideMenubar(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
signals:
    void pageChanged(SideMenubarButton* newSelection);
public slots:
    void unselectPreselection(SideMenubarButton* newSelection);
    void unselectAll();
    void restorePreselection();
//    void selectDefaultButton();
};

#endif // SIDEMENUBAR_H
