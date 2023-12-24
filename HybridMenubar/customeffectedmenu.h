#ifndef CUSTOMEFFECTEDMENU_H
#define CUSTOMEFFECTEDMENU_H

#include <QMenu>
#include <QFrame>

class CustomEffectedMenu : public QMenu
{
    Q_OBJECT
private:
    int x_origin = 0;
    int y_origin = 0;
    QFrame* frame;
    QPixmap* brush_pixmap;
    QBrush* shadow_brush;
    bool adjusted = false;
public:
    explicit CustomEffectedMenu(QWidget* parent = nullptr);
    virtual void paintEvent(QPaintEvent *e) override;
    virtual void moveEvent(QMoveEvent *event) override;

protected slots:
    virtual void adjustLocation();
};

#endif // CUSTOMEFFECTEDMENU_H
