#ifndef MYPLAINTEXTEDIT_H
#define MYPLAINTEXTEDIT_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QPainter>
#include <QClipboard>
#include <QProcess>
#include <QTextCursor>
#include <iostream>
#include <QString>
#include <mutex>

class MyPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT

    QClipboard* p_clipboard = nullptr;
    QList<QString> commandCache;
    int cacheIdx = -1;
    QProcess* p_process;
    int startPosition = 0;
    bool isDoneCout = false;
    bool isDoneError = false;
    bool isClear = false;
    std::mutex mtx_qtInput;

public:
    explicit MyPlainTextEdit(QWidget *parent = nullptr);
    virtual ~MyPlainTextEdit();

    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void keyPressEvent(QKeyEvent *e) override;
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

    bool openPowershell();
    void clearCurrentQtInput();
    QString getCurrentQtInput();
    void clearAllQtInput();

    void connectClipboard(QClipboard* clipboard);
signals:

public slots:
//    void redo();
//    void undo();

};

#endif // MYPLAINTEXTEDIT_H
