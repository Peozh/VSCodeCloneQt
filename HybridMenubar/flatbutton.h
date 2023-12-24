#ifndef FLATBUTTON_H
#define FLATBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>

class FlatButton : public QPushButton
{
    Q_OBJECT
    QPropertyAnimation* animation;
public:
    FlatButton(QWidget* parent = nullptr);
//    virtual void mouseMoveEvent(QMouseEvent *e) override;
    void setColors(QColor base, QColor hover, QColor pressed);
};

#endif // FLATBUTTON_H
