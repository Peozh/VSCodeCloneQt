#ifndef MENUACTIONPROXYSTYLE_H
#define MENUACTIONPROXYSTYLE_H

#include <QProxyStyle>
#include <QStyleOption>

class MenuActionProxyStyle : public QProxyStyle
{
public:
//    int styleHint(StyleHint hint, const QStyleOption *option = nullptr, const QWidget *widget = nullptr, QStyleHintReturn *returnData = nullptr) const override;

    virtual void drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
//    virtual void drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
};

#endif // MENUACTIONPROXYSTYLE_H
