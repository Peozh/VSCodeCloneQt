#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myplaintextedit.h"

#include <iostream>
#include <unistd.h>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    p_process->

    QClipboard *clipboard = QGuiApplication::clipboard();
    this->ui->plainTextEdit->connectClipboard(clipboard);
//    this->ui->verticalLayout->setStretch();
    this->ui->line->connectResizeTargetUp(this->ui->stackedWidget);
    this->ui->line->connectResizeTargetDown(this->ui->tabWidget);
    this->ui->line->connectLayout(this->ui->verticalLayout);

//    QMargins margins = this->ui->textEdit->setContentsMargins(1,);
    auto blockFmt = QTextBlockFormat();
    blockFmt.setLineHeight(80, QTextBlockFormat::ProportionalHeight);
    auto cursor_text = this->ui->textEdit->textCursor(); cursor_text.mergeBlockFormat(blockFmt); this->ui->textEdit->setTextCursor(cursor_text);
    auto cursor_map = this->ui->minimap->textCursor(); cursor_map.mergeBlockFormat(blockFmt); this->ui->minimap->setTextCursor(cursor_text);

    this->ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->minimap->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->minimap->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QTextEdit* p_minimap = this->ui->minimap;
    this->ui->textEdit->connectMinimap(p_minimap);


}

MainWindow::~MainWindow()
{
    delete ui;
}

