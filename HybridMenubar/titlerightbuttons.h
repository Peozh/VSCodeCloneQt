#ifndef TITLERIGHTBUTTONS_H
#define TITLERIGHTBUTTONS_H

#include "flatbutton.h"

#include <QWidget>

class TitleRightButtons : public QWidget
{
    Q_OBJECT
public:
    bool shouldMaximize = false;
    FlatButton* minimize_button;
    FlatButton* maximize_button;

public:
    explicit TitleRightButtons(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent* event) override;

signals:
    void minimizePressed();
    void maximizePressed();
    void restorePressed();

private slots:
    void emitMinimizeSignal();
    void emitProperMaximizeSignals();

};

#endif // TITLERIGHTBUTTONS_H
