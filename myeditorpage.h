#ifndef MYEDITORPAGE_H
#define MYEDITORPAGE_H

#include <QWidget>
#include <QScrollBar>

#include "mytextedit.h"
#include "myminimapwidget.h"
#include "myshadowgradient.h"

class MyEditorPage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int lineCount READ getLineCount WRITE setLineCount NOTIFY lineCountChanged)

    int lineCount;
    QHBoxLayout* p_layout;
    MyTextEdit* p_textEdit;
    MyMinimapWidget* p_minimap;
    QScrollBar* p_scroll_vertical;
    MyShadowGradient* p_shadow;

public:
    explicit MyEditorPage(QWidget *parent = nullptr);
    virtual void resizeEvent(QResizeEvent *event) override;

    int getLineCount() const;
    void setLineCount(int newValue);

signals:
    void lineCountChanged();

public slots:
    void printLog() const;
    void updateLineCount();
//    void modifyScrollBars();
    void moveScrollBars(int value);
    void applyLineCountToScrollBars();
    void applyVisibleHeightToScrollBars();
    void scrollMinimap();

    void updateShadowVisibility();
    void resizeShadow();

};

#endif // MYEDITORPAGE_H
