#include "sidemenubar.h"
#include "SideMenubar/sidemenubarbutton.h"
#include "qpainter.h"
#include "qstyleoption.h"

#include <QVBoxLayout>

SideMenubar::SideMenubar(QWidget *parent)
    : QWidget{parent}
{
    this->setStyleSheet("background-color: rgb(45, 45, 45);");
    {
        auto policy = this->sizePolicy();
        policy.setHorizontalPolicy(QSizePolicy::Fixed);
        policy.setVerticalPolicy(QSizePolicy::Expanding);
        this->setSizePolicy(policy);
        this->setFixedWidth(50);
    }

    auto layout = new QVBoxLayout(this);
    {
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(1);

        auto button1 = new SideMenubarButton(this);
        button1->setStyleSheet("background-color: rgb(45, 45, 45);");
        button1->setIcons(":/icons/files2-gray-512.png", ":/icons/files2-gray-512.png", ":/icons/files2-white-512.png", ":/icons/files2-white-512.png");
        button1->setFixedHeight(48);
        buttons.push_back(button1);
        connect(button1, &SideMenubarButton::selectChanged, this, &SideMenubar::unselectPreselection);
        auto page1 = new QLabel("Menu 1\nPage");
        {
            page1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            page1->setStyleSheet("QLabel { font: 20pt 'Segoe UI Semibold'; background-color: rgb(35, 35, 35); color: rgba(255,255,255,50%); }");
            page1->setVisible(false);
        }
        button1->setPage(page1);

        auto button2 = new SideMenubarButton(this);
        button2->setStyleSheet("background-color: rgb(45, 45, 45);");
        button2->setIcons(":/icons/files2-gray-512.png", ":/icons/files2-gray-512.png", ":/icons/files2-white-512.png", ":/icons/files2-white-512.png");
        button2->setFixedHeight(48);
        buttons.push_back(button2);
        connect(button2, &SideMenubarButton::selectChanged, this, &SideMenubar::unselectPreselection);
        auto page2 = new QLabel("Menu 2\nPage");
        {
            page2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            page2->setStyleSheet("QLabel { font: 20pt 'Segoe UI Semibold'; background-color: rgb(35, 35, 35); color: rgba(255,255,255,50%); }");
            page2->setVisible(false);
        }
        button2->setPage(page2);


        auto button3 = new SideMenubarButton(this);
        button3->setStyleSheet("background-color: rgb(45, 45, 45);");
        button3->setIcons(":/icons/files2-gray-512.png", ":/icons/files2-gray-512.png", ":/icons/files2-white-512.png", ":/icons/files2-white-512.png");
        button3->setFixedHeight(48);
        buttons.push_back(button3);
        connect(button3, &SideMenubarButton::selectChanged, this, &SideMenubar::unselectPreselection);
        auto page3 = new QLabel("Menu 3\nPage");
        {
            page3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            page3->setStyleSheet("QLabel { font: 20pt 'Segoe UI Semibold'; background-color: rgb(35, 35, 35); color: rgba(255,255,255,50%); }");
            page3->setVisible(false);
        }
        button3->setPage(page3);

        auto spacer = new QWidget(this);
        spacer->setStyleSheet("background-color: rgb(45, 45, 45);");
//        button->setColors({0, 0, 0}, {50, 50, 50}, {250, 0, 0});
        layout->addWidget(button1);
        layout->addWidget(button2);
        layout->addWidget(button3);
        layout->addWidget(spacer);

        buttonMemory = button1;
    }
    this->setLayout(layout);
}

void SideMenubar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

void SideMenubar::unselectPreselection(SideMenubarButton *newSelection)
{
    for (auto* button : buttons) {
        if (button->mode != SideMenubarButton::Mode::Selected) continue;
        if (button == newSelection) continue;
        button->applyMode(SideMenubarButton::Mode::Normal);
    }
    if (newSelection != nullptr) { buttonMemory = newSelection; emit pageChanged(newSelection); }
    else emit pageChanged(nullptr);
}

void SideMenubar::unselectAll()
{
    qDebug() << "unselectAll()";
    for (auto* button : buttons) {
        if (button->mode != SideMenubarButton::Mode::Selected) continue;
        button->applyMode(SideMenubarButton::Mode::Normal);
    }
}

void SideMenubar::restorePreselection()
{
    qDebug() << "restorePreselection()";
    if(buttonMemory == nullptr) return;
    buttonMemory->applyMode(SideMenubarButton::Mode::Selected);
}

//void SideMenubar::selectDefaultButton()
//{
//    if (buttons.empty()) return;
//    if (buttons.front() == nullptr) return;

//    qDebug() << "selectDefaultButton()";
//    buttonMemory = buttons.front();
//    buttonMemory->applyMode(SideMenubarButton::Mode::Selected);
//    emit pageChanged(buttonMemory);
//}
