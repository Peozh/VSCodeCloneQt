#include "menubarwidget.h"
#include "customeffectedmenu.h"
#include "custommenubarextension.h"

#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QWidgetAction>
#include <QResizeEvent>

MenuBarWidget::MenuBarWidget(QWidget *parent)
    : QWidget{parent}
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    p_menuBar = new QMenuBar(this);
    p_menuBar->setStyleSheet(
        "QMenuBar { "
        "    min-width: 0px;"
        "    padding: 4px 1px;"
        "    background-color: rgba(0, 0, 0, 0);"
        "    font: 10pt 'Segoe UI Semibold';"
        "}"
        "QMenuBar::item {"
        "    padding: 2px 7px;"
        "    color: rgba(255, 255, 255, 60%);"
        "    background: transparent;"
        "    border-radius: 4px;"
        "}"
        "QMenuBar::item:selected { /* when selected using mouse or keyboard */"
        "    color: rgba(255, 255, 255, 90%);"
        "    background: rgba(255, 255, 255, 10%);"
        "}"
        "QMenu {"
        "   margin: 6px;"
        "   padding: 4px 0px;"
        "   background-color: rgba(35, 35, 35, 100%);"
        "   border: solid;"
        "   border-radius: 8px;"
        "   border-color: rgb(70, 70, 70);"
        "   border-width: 1px;"
        "   color: rgba(255, 255, 255, 70%);"
        "   font: 10pt 'Segoe UI Semibold';"
        "}"
        "QMenu::separator {"
        "   margin: 4px 0px;"
        "   height: 1px;"
        "   background: rgb(70, 70, 70);"
        "}"

        "QMenu::item {"
        "   margin: 0px 4px;"
        "   background: transparent;"
        "   border-radius: 4px;"
        "   padding: 5px 10px 4px 10px;"
        "}"
        "QMenu::item:selected {"
        "   background-color: rgba(0, 60, 100, 90%);"
        "   color: rgba(255, 255, 255, 100%);"
        "}"
        "QToolButton {"
        "    max-width: 0px;"
        "    padding: 0px 0px;"
        "    margin-left: -10px;"
        "    min-width: 0px;"
        "    color: rgba(255, 255, 255, 60%);"
        "    background: transparent;"
        "    qproperty-icon: url(':/icons/more-19-1024-white-30%.png');"
        "    border-radius: 4px;"
        "}"
        "QToolButton::hover {"
        "    background: rgba(255, 255, 255, 10%);"
        "}"
    );
    {
        auto* menu_file = new CustomEffectedMenu(this);
        menu_file->setTitle("File");
        p_menuBar->addMenu(menu_file);
        auto* action_1 = new QAction("Action 1", menu_file);
        action_1->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_1));
//        action_1->setShortcutVisibleInContextMenu(false);
        auto* action_2 = new QAction("Action 2", menu_file);
        action_2->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_2));
        action_2->setShortcutVisibleInContextMenu(true);
        auto* action_3 = new QAction("Action 3333333333333333", menu_file);
        auto* action_3_submenu = new CustomEffectedMenu(this);
        auto* action_3_1 = new QAction("Action 3_1", action_3_submenu);
        action_3_submenu->addAction(action_3_1);
        action_3->setMenu(action_3_submenu);
        menu_file->addAction(action_1);
        menu_file->addSeparator();
        menu_file->addAction(action_2);
        menu_file->addAction(action_3);

        QStyleOptionMenuItem menuOption;
        menuOption.initFrom(menu_file);

        auto* menu_edit = new CustomEffectedMenu(this);
        menu_edit->setTitle("Edit");
        p_menuBar->addMenu(menu_edit);
        menu_edit->addAction("Action 1");
        menu_edit->addAction("Action 2");

        auto* menu_selection = new CustomEffectedMenu(this);
        menu_selection->setTitle("Selection");
        p_menuBar->addMenu(menu_selection);

        auto* menu_view = new CustomEffectedMenu(this);
        menu_view->setTitle("View");
        p_menuBar->addMenu(menu_view);

        auto* menu_go = new CustomEffectedMenu(this);
        menu_go->setTitle("Go");
        p_menuBar->addMenu(menu_go);

        auto* menu_run = new CustomEffectedMenu(this);
        menu_run->setTitle("Run");
        p_menuBar->addMenu(menu_run);

        auto* menu_terminal = new CustomEffectedMenu(this);
        menu_terminal->setTitle("Terminal");
        p_menuBar->addMenu(menu_terminal);

        auto* menu_help = new CustomEffectedMenu(this);
        menu_help->setTitle("Help");
        p_menuBar->addMenu(menu_help);

//        auto* cornerWidget = new QWidget(this);
//        p_menuBar->setWindowIcon(QIcon(":/icons/vscode_icon.ico"));


    }

    // custom extension button
    {
        this->menuBarExt = new CustomMenuBarExtension(this);
        menuBarExt->setStyleSheet(
            "QToolButton {"
            "    max-width: 40px;"
            "    min-width: 40px;"
            "    max-height: 22px;"
            "    min-height: 22px;"
            "    margin-top: 0px;"
            "    margin-bottom: 3px;"
            "    color: rgba(255, 255, 255, 60%);"
            "    background: transparent;"
            "    qproperty-icon: url(':/icons/more-19-1024-white-30%.png');"
            "    border-radius: 4px;"
            "}"
            "QToolButton::hover {"
            "    background: rgba(255, 255, 255, 10%);"
            "}"
        );
        menuBarExt->raise();
        auto actions = p_menuBar->actions();
        for (int idx = 0; idx < actions.size(); ++idx)
        {
            // make extension button contents
            auto* menu_extension = new CustomEffectedMenu(this);
            this->extension_contents.push_back(menu_extension);
            menu_extension->addActions(actions.mid(idx, actions.size()-idx));
        }
    }

    layout->addWidget(p_menuBar);
    auto emptySpace = new QWidget(this);
    emptySpace->lower();
    emptySpace->setStyleSheet("background: transparent; background-color: rgba(255,255,255,15%);");
    emptySpace->setFixedWidth(43);
    layout->addWidget(emptySpace);
    layout->setStretch(0, 1);
    layout->setStretch(1, 0);
    this->setLayout(layout);
    this->setStyleSheet("MenuBarWidget { background-color: rgba(0, 0, 0, 0); }");
}

void MenuBarWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

void MenuBarWidget::resizeEvent(QResizeEvent *event)
{
    int lastActionIdx = -1;
    auto actions = p_menuBar->actions();
    if (actions.size() == 0) return;
    for (int idx = 0; idx < this->extension_contents.size(); ++idx)
    {
        auto rect = p_menuBar->actionGeometry(actions.at(idx));
        auto availableSpace = this->p_menuBar->contentsRect().width();
        if (idx != this->extension_contents.size()-1) availableSpace -= 12;
        if (rect.right() < availableSpace)
        {
            qDebug() << "rect.right() = " << rect.right() << " ||||| " << event->size().width() - 43;
            lastActionIdx = idx;
        }
    }
    qDebug() << "lastActionIdx = " << lastActionIdx;
    if (lastActionIdx == lastActionIdx_old) { return; } // do nothing
    lastActionIdx_old = lastActionIdx;
    if (lastActionIdx == this->extension_contents.size()-1) { this->menuBarExt->setVisible(false); return; } // case all menu visible : remove extension button
    this->menuBarExt->setVisible(true);
    if (lastActionIdx != -1) { auto rect = p_menuBar->actionGeometry(actions.at(lastActionIdx)); this->menuBarExt->move(rect.topRight()); } // case, some menu hidden : update extension button geometry
    if (lastActionIdx == -1) { auto rect = p_menuBar->actionGeometry(actions.at(0)); this->menuBarExt->move(rect.topLeft()); } // case, all menu hidden : update extension button geometry
    this->menuBarExt->setMenu(extension_contents.at(lastActionIdx+1)); // update extension button's contents

}
