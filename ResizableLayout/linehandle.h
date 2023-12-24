#ifndef LINEHANDLE_H
#define LINEHANDLE_H

#include <QFrame>
#include <QLayout>
#include <condition_variable>
#include <mutex>
#include <thread>

class LineHandle : public QFrame
{
    Q_OBJECT

    int max_step = 10;
    QColor start { -35, -130, -255 };
    QColor end { 35, 130, 255 };

    bool needTerminate = false;
    bool needIncreaseStep = false;
    bool needDecreaseStep = false;
    int step = 0;
    std::thread animationThread;
    std::condition_variable cvAnimationIdleWait;
    std::mutex mtxAnimationStates;
    std::mutex mtxCV;

protected:
    QFrame* baseLine;
    QFrame* activeLine;

    QLayout* targetLayout = nullptr;

    QPointF dragStartPosition;
    QRect dragStartGeometry[2];
    int fixedWidgetIndex;

public:
    LineHandle(QWidget* parent = nullptr);
    ~LineHandle();
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
//    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    void connectTargetLayout(QLayout* layout);

    void setBaseColor(int r, int g, int b, int a);

signals:
    void colorStepChanged(int new_step);
    void lineDragged();
private slots:
    void setColor(int new_step);

public slots:
    virtual void toggleFixedWidget();
};

#endif // LINEHANDLE_H
