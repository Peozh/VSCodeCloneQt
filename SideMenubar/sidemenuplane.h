#ifndef SIDEMENUPLANE_H
#define SIDEMENUPLANE_H

#include <SideMenubar/sidemenubarbutton.h>

#include <QWidget>
#include <QVBoxLayout>

class SideMenuPlane : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* layout;
    int widthMemory = 200;
    SideMenubarButton* buttonMemory;

public:
    explicit SideMenuPlane(QWidget *parent = nullptr);
    virtual void resizeEvent(QResizeEvent *event) override;
signals:
    void geometryChnaged();
    void menuFoldedByDrag();
    void menuUnfoldedByDrag();

public slots:
    void setMenuPage(SideMenubarButton *newButton);
    void foldPage();
    void unfoldPage();
};

#endif // SIDEMENUPLANE_H
