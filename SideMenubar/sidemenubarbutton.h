#ifndef SIDEMENUBARBUTTON_H
#define SIDEMENUBARBUTTON_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class SideMenubarButton : public QWidget
{
    Q_OBJECT
public:
    enum Mode { Disabled, Normal, Hovered, Pressed, Selected };
    SideMenubarButton::Mode mode = Normal;
private:
    QIcon icon;
    QFrame* line;
    QLabel* label;
    QColor modeLineColors[5];
    QPixmap pixmap;
    bool isPreselected = false;
public:
    QWidget* page = nullptr;

public:
    explicit SideMenubarButton(QWidget *parent = nullptr);
    void setIcons(QString normalIconPath, QString disabledIconPath, QString activeIconPath, QString selectedIconPath);
    void setLineColors(QColor disabled, QColor normal, QColor hovered, QColor pressed, QColor selected);
    void setPage(QWidget* page);

    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QLabel* createPixmapLabel();

signals:
    void modeChanged(SideMenubarButton::Mode newMode);
    void selectChanged(SideMenubarButton* pButton);
public slots:
    void applyMode(SideMenubarButton::Mode newMode);
};

#endif // SIDEMENUBARBUTTON_H
