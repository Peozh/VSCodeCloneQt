#ifndef MYMINIMAPWIDGET_H
#define MYMINIMAPWIDGET_H

#include <QWidget>
#include <QScrollBar>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QEnterEvent>

class MyMinimapWidget : public QWidget
{
    Q_OBJECT
    QString styleSheet_scrollbar = "";
    QString styleSheet_textEdit = "";
    int scrollbarHeight = 0;

public:
    explicit MyMinimapWidget(QWidget *parent = nullptr);

    virtual void resizeEvent(QResizeEvent *event) override;

    void setScrollBarHeight(int height);

    QScrollBar* p_scrollBar = nullptr;
    QTextEdit* p_textEdit = nullptr;
protected:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
signals:

};

#endif // MYMINIMAPWIDGET_H
