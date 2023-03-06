#ifndef MYTEXTEDITWITHSPACE_H
#define MYTEXTEDITWITHSPACE_H

#include <QWidget>
#include <QFrame>
#include <QScrollArea>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QTextFrame>

class MyTextEditWithSpace : public QWidget
{
    Q_OBJECT
    QScrollArea* p_area;
    QWidget* p_contents;
    QVBoxLayout* p_layout;
    QTextEdit* p_textEdit;
    QWidget* p_space;
public:
    explicit MyTextEditWithSpace(QWidget *parent = nullptr);

    virtual void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
    void resizeTextEdit();
};

#endif // MYTEXTEDITWITHSPACE_H
