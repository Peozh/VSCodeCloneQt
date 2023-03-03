#include "mytabwidget.h"

MyTabWidget::MyTabWidget(QWidget *parent) :QTabWidget(parent)
{
    mTabBar = new MyTabBar;
    setTabBar(mTabBar);
    for(int i=0; i < 5; i++){
        QString text = QString("Tab %1").arg(i);
        addTab(new MyTab(text, this), text);
    }
    mTabBar->setUnsaved(1);
    mTabBar->setUnsaved(3);
    mTabBar->setUnsaved(4);
    mTabBar->setSaved(3);
    mTabBar->setSaved(10);

//    this->setStyleSheet("")
}
