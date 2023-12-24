#include "hybridmenubar.h"
#include "titlepartwidget.h"
#include "flatbutton.h"
#include "titlerightbuttons.h"

#include <QLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>

HybridMenuBar::HybridMenuBar(QWidget* parent) : QWidget(parent)
{
    constexpr int fixedHeight = 30;

    auto* icon = new QLabel();
    {
        QImage image(":/icons/vscode_icon.ico");
        image = image.scaled({16, 16});
        icon->setPixmap(QPixmap::fromImage(image));

        icon->setContentsMargins(8, 0, 8, 0);

        auto policy = icon->sizePolicy();
        policy.setHorizontalPolicy(QSizePolicy::Fixed);
        policy.setVerticalPolicy(QSizePolicy::Fixed);
        icon->setSizePolicy(policy);
        icon->setFixedWidth(32);
        icon->setFixedHeight(fixedHeight);
    }

    this->p_menuBarWidget = new MenuBarWidget(this); // menu bar
    {
        auto policy = p_menuBarWidget->sizePolicy();
        policy.setHorizontalPolicy(QSizePolicy::Minimum);
        policy.setVerticalPolicy(QSizePolicy::Fixed);
        p_menuBarWidget->setSizePolicy(policy);
        p_menuBarWidget->setMinimumWidth(43);
        p_menuBarWidget->setFixedHeight(fixedHeight);
    }

    //////////// title ~ ////////////
    auto* titlePartWidget = new TitlePartWidget(this);
    {
        auto policy = titlePartWidget->sizePolicy();
        policy.setHorizontalPolicy(QSizePolicy::Expanding);
        policy.setVerticalPolicy(QSizePolicy::Fixed);
        titlePartWidget->setSizePolicy(policy);
        titlePartWidget->setTitle(" ο .gitignore - Untitled (Workspace) - Visual Studio Code");
        titlePartWidget->setMinimumWidth(60+10);
        qDebug() << "maximum width : " << titlePartWidget->maximumWidth;
        titlePartWidget->setFixedHeight(fixedHeight);

        connect(titlePartWidget, SIGNAL(windowDraggedTo(QPointF)), this, SLOT(moveWindowTo(QPointF)));
    }
    //////////// ~ title ////////////

    // other buttons + minimize + maximize/restore buttons
    auto* rightSpace_and_buttons = new TitleRightButtons(this);
    {
        connect(rightSpace_and_buttons, SIGNAL(minimizePressed()), this->window(), SLOT(showMinimized()));
        connect(rightSpace_and_buttons, SIGNAL(maximizePressed()), this->window(), SLOT(showMaximized()));
        connect(rightSpace_and_buttons, SIGNAL(restorePressed()), this->window(), SLOT(showNormal()));
    }

    auto* x_button = new FlatButton(this);
    {
        x_button->setColors(QColor{45, 45, 45}, QColor{255, 0, 0}, QColor{200, 0, 0});
        x_button->setIcon(QIcon(":/icons/close-white-128.png"));
        x_button->setIconSize(QSize{14, 14});

        connect(x_button, SIGNAL(clicked(bool)), this->window(), SLOT(close()));
    }

//    p_menuBarWidget->raise();

    auto* layout = new QHBoxLayout(this);
    {
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        layout->addWidget(icon);
        layout->addWidget(p_menuBarWidget);
        layout->addWidget(titlePartWidget);
        layout->addWidget(rightSpace_and_buttons);
        layout->addWidget(x_button);

        layout->setStretch(0, 0); // icon
        layout->setStretch(1, 1); // menu bar
        layout->setStretch(2, 1000); // title
        layout->setStretch(3, 1); // right space 1:1 with menu bar, + layout buttons + window other buttons
        layout->setStretch(4, 0); // x_button
    }

    this->setLayout(layout);
    this->setStyleSheet(R"(HybridMenuBar { background-color: rgba(45, 45, 45, 100%); })");
}

void HybridMenuBar::moveWindowTo(QPointF dest)
{
    qDebug() << dest;
    if (this->window() == nullptr) return;
    this->window()->move(dest.x(), dest.y());
}

void HybridMenuBar::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

// 1단계 : 제목 양쪽이 1:1로 감소함
// 2단계 : 제목 오른쪽이 0로 변하고, 왼쪽만 감소하기 시작
// 3단계 : 제목의 200 px(... 미포함) 이상 오른쪽 부분이 왼쪽과 1:3 으로 감소하기 시작
// 4단계 : 제목이 200 px 까지 줄어들고, 왼쪽의 여유공간이 모두 소진됨, ...을 제외한 제목이 50 px 까지 감소함
