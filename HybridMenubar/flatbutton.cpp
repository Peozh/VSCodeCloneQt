#include "flatbutton.h"

FlatButton::FlatButton(QWidget* parent) : QPushButton(parent)
{
    constexpr int fixedHeight = 30;
    auto policy = this->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Fixed);
    policy.setVerticalPolicy(QSizePolicy::Fixed);
    this->setSizePolicy(policy);
    this->setFixedWidth(45);
    this->setFixedHeight(fixedHeight);
    this->setStyleSheet(
        "QPushButton:flat "
            "{ "
            "   background-color: rgba(45, 45, 45, 0%);"
            "   border: 0px;"
            "}"
        "QPushButton::hover { background-color: rgba(250, 0, 0, 100%); }"
        "QPushButton::pressed { background-color: rgba(200, 0, 0, 100%); }"
    );
    this->setFlat(true);
    this->setIconSize(QSize{12, 12});
//    this->setIcon(QIcon(":/icons/close-pop-up-window-16-white_128.png"));
    //    this->setIconSize(QSize{16, 16});
}

void FlatButton::setColors(QColor base, QColor hover, QColor pressed)
{
    QString baseRGBA = "rgba("+QString::number(base.red())+", "+QString::number(base.green())+", "+QString::number(base.blue())+", 0%)";
    QString hoverRGBA = "rgba("+QString::number(hover.red())+", "+QString::number(hover.green())+", "+QString::number(hover.blue())+", 100%)";
    QString pressedRGBA = "rgba("+QString::number(pressed.red())+", "+QString::number(pressed.green())+", "+QString::number(pressed.blue())+", 100%)";
    this->setStyleSheet("QPushButton:flat "
                            "{ "
                            "   background-color:" + baseRGBA + ";"
                            "   border: 0px;"
                            "}"
                            "QPushButton::hover { background-color: " + hoverRGBA + "; }"
                            "QPushButton::pressed { background-color: " + pressedRGBA + "; }"
                        );
}
