#include "sidemenubarbutton.h"
#include "qboxlayout.h"
#include "qframe.h"

SideMenubarButton::SideMenubarButton(QWidget *parent)
    : QWidget{parent}
{
    auto layout = new QHBoxLayout(this);
    {
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        this->line = new QFrame(this);
        line->setFixedWidth(1);
//        line->setAutoFillBackground(true);
        setLineColors(QColor{0, 0, 0, 0}, QColor{0, 0, 0, 0}, QColor{0, 0, 0, 0}, QColor{100, 150, 255, 255}, QColor{255, 255, 255, 255});
        icon = QIcon();

        this->label = createPixmapLabel();
        layout->addWidget(line);
        layout->addWidget(label);
    }

    this->setLayout(layout);

    connect(this, &SideMenubarButton::modeChanged, this, &SideMenubarButton::applyMode);
}

QLabel* SideMenubarButton::createPixmapLabel()
{
    QLabel *label = new QLabel(this);
    label->setEnabled(false);
    label->setAlignment(Qt::AlignCenter);
    label->setFrameShape(QFrame::NoFrame);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setBackgroundRole(QPalette::Base);
    label->setAutoFillBackground(true);
    label->setMinimumSize(28, 28);
    return label;
}

void SideMenubarButton::applyMode(SideMenubarButton::Mode newMode)
{
//    if (isPreselected) newMode = Mode::Normal;
    this->mode = newMode;
//    line->setAutoFillBackground(true);
//    auto p = line->palette();
    /* in qicon.h ...
     * enum Mode { Normal, Disabled, Active, Selected }; */
//    p.setColor(line->backgroundRole(), modeLineColors[mode]);
//    line->setPalette(p);
//    QString colorString = modeLineColors[mode].name(QColor::HexArgb); // #00ffffff
    QString colorString = "rgba("
            + QString::number(modeLineColors[mode].red()) + ", "
            + QString::number(modeLineColors[mode].green()) + ", "
            + QString::number(modeLineColors[mode].blue()) + ", "
            + QString::number(modeLineColors[mode].alphaF()/255*100)
            + "%)";
    line->setStyleSheet("background-color: " + colorString + ";");

    QIcon::Mode iconMode;
    switch (this->mode)
    {
    case Mode::Disabled: iconMode = QIcon::Mode::Disabled; break;
    case Mode::Normal: iconMode = QIcon::Mode::Normal; break;
    case Mode::Hovered: iconMode = QIcon::Mode::Active; break;
    case Mode::Pressed: iconMode = QIcon::Mode::Active; break;
    default: iconMode = QIcon::Mode::Selected;
    }
    if (mode == Mode::Selected) {
        if (isPreselected) emit selectChanged(nullptr);
        else emit selectChanged(this);
        isPreselected = true;
    }
    if (mode < Mode::Pressed) isPreselected = false;

    this->pixmap = icon.pixmap(QSize{28, 28}, iconMode);
    this->label->setPixmap(pixmap);

    if (mode == Mode::Disabled) this->setDisabled(true);
    else this->setDisabled(false);
}

void SideMenubarButton::setIcons(QString normalIconPath, QString disabledIconPath, QString activeIconPath, QString selectedIconPath)
{
    icon.addFile(normalIconPath, QSize{28,28}, QIcon::Mode::Normal, QIcon::State::Off);
    icon.addFile(disabledIconPath, QSize{28,28}, QIcon::Mode::Disabled, QIcon::State::Off);
    icon.addFile(activeIconPath, QSize{28,28}, QIcon::Mode::Active, QIcon::State::Off);
    icon.addFile(selectedIconPath, QSize{28,28}, QIcon::Mode::Selected, QIcon::State::Off);

    applyMode(mode);
}

void SideMenubarButton::setLineColors(QColor disabled, QColor normal, QColor hovered, QColor pressed, QColor selected)
{
    this->modeLineColors[0] = disabled;
    this->modeLineColors[1] = normal;
    this->modeLineColors[2] = hovered;
    this->modeLineColors[3] = pressed;
    this->modeLineColors[4] = selected;
}

void SideMenubarButton::setPage(QWidget *page)
{
    this->page = page;
}

void SideMenubarButton::enterEvent(QEnterEvent *event)
{
    if (!this->isEnabled()) return;
    if (mode >= SideMenubarButton::Mode::Pressed) return;
    auto newMode = SideMenubarButton::Mode::Hovered;
    emit modeChanged(newMode);
}

void SideMenubarButton::leaveEvent(QEvent *event)
{
    if (!this->isEnabled()) return;
    if (mode >= SideMenubarButton::Mode::Pressed) return;
    auto newMode = SideMenubarButton::Mode::Normal;
    emit modeChanged(newMode);
}

void SideMenubarButton::mousePressEvent(QMouseEvent *event)
{
    if (!this->isEnabled()) return;
    auto newMode = SideMenubarButton::Mode::Pressed;
    emit modeChanged(newMode);
}

void SideMenubarButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (!this->isEnabled()) return;
    auto newMode = SideMenubarButton::Mode::Selected;
    emit modeChanged(newMode);
}
