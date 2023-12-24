#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ResizableLayout/resizableqhboxlayout.h"
#include "ResizableLayout/resizableqvboxlayout.h"
#include "SideMenubar/sidemenubar.h"
#include "SideMenubar/sidemenuplane.h"

#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    {
        SideMenubar* sideMenuBar = new SideMenubar(this); sideMenuBar->setStyleSheet("background-color: rgb(45, 45, 45);");
        {
            auto policy = sideMenuBar->sizePolicy();
            policy.setHorizontalPolicy(QSizePolicy::Fixed);
            policy.setVerticalPolicy(QSizePolicy::Expanding);
            sideMenuBar->setSizePolicy(policy);
            sideMenuBar->setFixedWidth(50);
        }

        ResizableQHBoxLayout* sideMenu_and_mainPlane = new ResizableQHBoxLayout(this);
        {
            SideMenuPlane* sideMenu = new SideMenuPlane(this); sideMenu->setStyleSheet("background-color: rgb(35, 35, 35);");
            {
                auto policy = sideMenu->sizePolicy();
                policy.setHorizontalPolicy(QSizePolicy::Fixed);
                policy.setVerticalPolicy(QSizePolicy::Expanding);
                sideMenu->setSizePolicy(policy);
                sideMenu->setFixedWidth(200);

                connect(sideMenuBar, &SideMenubar::pageChanged, sideMenu, &SideMenuPlane::setMenuPage);
                connect(sideMenu, &SideMenuPlane::geometryChnaged, sideMenu_and_mainPlane, &ResizableQHBoxLayout::updateLineGeometry);
                connect(sideMenu, &SideMenuPlane::menuFoldedByDrag, sideMenuBar, &SideMenubar::unselectAll);
                connect(sideMenu, &SideMenuPlane::menuUnfoldedByDrag, sideMenuBar, &SideMenubar::restorePreselection);
            }
            ResizableQVBoxLayout* mainPlane = new ResizableQVBoxLayout(this);
            {
                QWidget* upper = new QWidget(this); upper->setStyleSheet("background-color: rgb(30, 30, 30);");
                {
                    auto policy = upper->sizePolicy();
                    policy.setHorizontalPolicy(QSizePolicy::Expanding);
                    policy.setVerticalPolicy(QSizePolicy::Fixed);
                    upper->setSizePolicy(policy);
                    upper->setMaximumHeight(200);
                }
                QWidget* lower = new QWidget(this); lower->setStyleSheet("background-color: rgb(30, 30, 30);");
                {
                    auto policy = upper->sizePolicy();
                    policy.setHorizontalPolicy(QSizePolicy::Expanding);
                    policy.setVerticalPolicy(QSizePolicy::Expanding);
                    lower->setSizePolicy(policy);
                }

                mainPlane->layout->setContentsMargins(0, 0, 0, 0);
                mainPlane->addWidget(upper);
                mainPlane->addWidget(lower);
                mainPlane->layout->setStretch(0, 1);
                mainPlane->layout->setStretch(1, 1);
            }
            sideMenu_and_mainPlane->layout->setContentsMargins(0, 0, 0, 0);
            sideMenu_and_mainPlane->addWidget(sideMenu);
            sideMenu_and_mainPlane->addWidget(mainPlane);
            sideMenu_and_mainPlane->layout->setStretch(0, 1);
            sideMenu_and_mainPlane->layout->setStretch(1, 1);
            sideMenu_and_mainPlane->setBaseLineColor(0, 0, 0, 0);
        }
        ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ui->horizontalLayout->addWidget(sideMenuBar);
        ui->horizontalLayout->addWidget(sideMenu_and_mainPlane);
        ui->horizontalLayout->setStretch(0, 1);
        ui->horizontalLayout->setStretch(1, 1);
    }

    this->setContentsMargins(0, 0, 0, 0);
    this->layout()->setContentsMargins(0, 0, 0, 0);
    this->layout()->setSpacing(0);
    this->ui->centralwidget->setContentsMargins(0, 0, 0, 0);
    this->ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);
    this->ui->centralwidget->layout()->setSpacing(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    ev->ignore();
//    this->centralWidget()->setGeometry(0, -10, ev->size().width(), ev->size().height());
}

