#ifndef MYUPPERTEXTPART_H
#define MYUPPERTEXTPART_H

#include <QWidget>
#include <QStackedWidget>
#include <QScrollBar>
#include <QFrame>

#include "myline.h"
#include "myeditorpage.h"

class MyUpperTextPart : public QWidget
{
    Q_OBJECT
    QVBoxLayout* p_layout;
    QStackedWidget* p_stacked;
    MyEditorPage* p_page;

public:
    explicit MyUpperTextPart(QWidget *parent = nullptr);

    virtual void resizeEvent(QResizeEvent *event) override;

    MyLine* p_line;

signals:

};

#endif // MYUPPERTEXTPART_H
