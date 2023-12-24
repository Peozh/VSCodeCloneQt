#ifndef CUSTOMMENUBAREXTENSION_H
#define CUSTOMMENUBAREXTENSION_H

#include <QToolButton>
#include <QStyle>
#include <QStylePainter>
#include <QStyleOptionToolButton>

class CustomMenuBarExtension : public QToolButton
{
public:
    explicit CustomMenuBarExtension(QWidget *parent);

    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *) override;
};

#endif // CUSTOMMENUBAREXTENSION_H
