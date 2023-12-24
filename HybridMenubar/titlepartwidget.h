#ifndef TITLEPARTWIDGET_H
#define TITLEPARTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>

#include <vector>

class TitlePartWidget : public QWidget
{
    Q_OBJECT

    QString title;
    int titleTotalLength;
    QLabel* label;
    std::vector<float> cumulativeLength;

    QWidget* leftSpace;
    QWidget* title_head;
    QWidget* title_tail;

    QPoint dragStartWindowPos;
    QPointF dragStartPoint;

public:
    int maximumWidth;
public:
    explicit TitlePartWidget(QWidget *parent = nullptr);
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

    int getTitleTotalLength();

signals:
    void windowDraggedTo(QPointF);

public slots:
    void setTitle(QString str);

private:
    void makeCumulativeLength(QString str);
    QString getShortenTitle(QString str);
    size_t binarySearch(size_t stIdx, size_t enIdx, float val);
};

#endif // TITLEPARTWIDGET_H
