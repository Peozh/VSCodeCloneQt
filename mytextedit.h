#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>
#include <QWidget>

class MyTextEdit : public QTextEdit
{
    Q_OBJECT

    QTextEdit* p_minimap_ = nullptr;
public:
    explicit MyTextEdit(QWidget *parent = nullptr);

    void connectMinimap(QTextEdit* p_minimap);

private slots:
    void updateMinimap();
};

#endif // MYTEXTEDIT_H
