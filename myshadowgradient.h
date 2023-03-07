#ifndef MYSHADOWGRADIENT_H
#define MYSHADOWGRADIENT_H

#include <QWidget>

class MyShadowGradient : public QWidget
{
    Q_OBJECT
public:
    explicit MyShadowGradient(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event) override;

signals:

};

#endif // MYSHADOWGRADIENT_H
