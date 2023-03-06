#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>
#include <QWidget>
#include <QTextFrame>
#include <QScrollBar>

class MyTextEdit : public QTextEdit
{
    Q_OBJECT

    QTextEdit* p_minimap_ = nullptr;
    int minimapBottomMargin;
public:
    explicit MyTextEdit(QWidget *parent = nullptr);

//    virtual void scrollContentsBy(int dx, int dy) override;

    void connectMinimap(QTextEdit* p_minimap);
    void setMinimapBottomMargin(int margin);
    int lineHeight;

private slots:
    void updateMinimap();
};

#endif // MYTEXTEDIT_H
