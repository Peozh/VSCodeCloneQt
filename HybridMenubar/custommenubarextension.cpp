#include "custommenubarextension.h"


CustomMenuBarExtension::CustomMenuBarExtension(QWidget *parent)
    : QToolButton(parent)
{
    setObjectName("qt_menubar_ext_button");
    setAutoRaise(true);
#if QT_CONFIG(menu)
    setPopupMode(QToolButton::InstantPopup);
#endif
    setIcon(QIcon(":/icons/vscode_icon.ico"));
}

void CustomMenuBarExtension::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    // We do not need to draw both extension arrows
    opt.features &= ~QStyleOptionToolButton::HasMenu;
    p.drawComplexControl(QStyle::CC_ToolButton, opt);
}


QSize CustomMenuBarExtension::sizeHint() const
{
    int ext = style()->pixelMetric(QStyle::PM_ToolBarExtensionExtent, nullptr, parentWidget());
    return QSize(ext, ext);
}
