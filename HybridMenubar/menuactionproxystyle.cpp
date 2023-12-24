#include "menuactionproxystyle.h"

//int MenuActionProxyStyle::styleHint(StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
//{
//    qDebug() << "styleHint()";
//    switch (hint) {
//    case SH_DitherDisabledText:
//        return int(false);
//    case SH_EtchDisabledText:
//        return int(true);
//    default:
//        return QProxyStyle::styleHint(hint, option, widget, returnData);
//    }
//}

void MenuActionProxyStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    qDebug() << "drawControl";
    QString text = "";
    QString shortcut = "";
    if (element == QStyle::CE_MenuItem)
    {
//        option->direction = Qt::LayoutDirection::RightToLeft;
//        QStyleOptionButton option();
        const QStyleOptionMenuItem* labelOption = reinterpret_cast<const QStyleOptionMenuItem*>(option);
        auto vals = labelOption->text.split("\t");
        qDebug() << labelOption->text;
        if (vals.length() == 2)
        {
            text = vals.at(0);
            shortcut = vals.at(1);
            qDebug() << option->styleObject-> children();//text=setObjectName("a");
            int margin = 10;
            this->proxy()->drawItemText(painter, option->rect.adjusted(margin, 0, -margin, 0),
                                        Qt::AlignLeft | Qt::AlignVCenter,
                                        option->palette, option->state & QStyle::State_Enabled,
                                        text, QPalette::Text);
        }
//        QProxyStyle::drawControl(element, option, painter, widget);
        if (!shortcut.isEmpty())
        {
            int margin = 10;
            this->proxy()->drawItemText(painter, option->rect.adjusted(margin, 0, -margin, 0),
                                        Qt::AlignRight | Qt::AlignVCenter,
                                        option->palette, option->state & QStyle::State_Enabled,
                                        shortcut, QPalette::Text);
        }
        return;
    }
    QProxyStyle::drawControl(element, option, painter, widget);
//    this->proxy()->drawItemText(painter, option->rect.adjusted(margin, 0, -margin, 0),
//                                Qt::AlignRight | Qt::AlignVCenter,
//                                option->palette, option->state & QStyle::State_Enabled,
//                                option->styleObject->objectName(), QPalette::Text);

}

//void MenuActionProxyStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
//{
//    qDebug() << "drawPrimitive()";
//    QProxyStyle::drawPrimitive(element, option, painter, widget);
//}
