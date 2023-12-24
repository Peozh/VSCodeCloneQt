#include "sidemenuplane.h"
#include "qevent.h"

SideMenuPlane::SideMenuPlane(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedWidth(160);
    this->setContentsMargins(0, 0, 0, 0);
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    this->setLayout(layout);
}

void SideMenuPlane::resizeEvent(QResizeEvent *event)
{
    auto width = this->width();
    if (width > 50) {
        widthMemory = width;
        if (event->oldSize().width() < 50) { qDebug() << "menuUnfoldedByDrag()"; emit menuUnfoldedByDrag(); }
    }
    else
    {
        qDebug() << "menuFoldedByDrag()";
        emit menuFoldedByDrag();
    }
    emit geometryChnaged();
}

void SideMenuPlane::setMenuPage(SideMenubarButton *newButton)
{
    if (newButton != nullptr) buttonMemory = newButton;
    auto* oldItem = layout->itemAt(0);
    if (oldItem != nullptr) { layout->removeItem(oldItem); oldItem->widget()->setVisible(false); } //
    if (newButton == nullptr) { foldPage(); return; }
    auto newPage = newButton->page;
    if (newPage == nullptr) { foldPage(); return; }
    layout->addWidget(newPage);
    newPage->setVisible(true);
    unfoldPage();
}

void SideMenuPlane::foldPage()
{
    this->setFixedWidth(0);
    this->setVisible(false);
}

void SideMenuPlane::unfoldPage()
{
    this->setFixedWidth(widthMemory);
    this->updateGeometry();
    this->setVisible(true);
}
