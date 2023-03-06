#include "mainwindow.h"
#include "myminimapwidget.h"
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

    QClipboard *clipboard = QGuiApplication::clipboard();
    this->ui->plainTextEdit->connectClipboard(clipboard);

    this->ui->widgetUpperTextPart->p_line->connectResizeTargetDown(this->ui->tabWidget);
    this->ui->widgetUpperTextPart->p_line->connectLayout(this->ui->verticalLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

