#include "linehandle.h"

#include <QStyleOption>
#include <QPainter>
#include <thread>
#include <QEnterEvent>
#include <QEvent>

LineHandle::LineHandle(QWidget* parent) : QFrame(parent)
{
    QString stylesheetBackground { "background-color : rgba(0, 0, 0, 0%);" };
    this->setStyleSheet(stylesheetBackground);

    // set baseLine design
    baseLine = new QFrame(this);
    baseLine->setContentsMargins(0, 0, 0, 0);
    QString stylesheetPassive { R"(
        QFrame {
            margin-top: 0px;
            margin-bottom: 0px;
            border: 0px;
            background-color: rgb(70, 70, 70);
        }
    )" };
    baseLine->setStyleSheet(stylesheetPassive);

    // set activeLine design
    activeLine = new QFrame(this);
    activeLine->setGeometry(0, 0, this->geometry().width(), 5);
    activeLine->setMouseTracking(true);
    activeLine->setContentsMargins(0, 0, 0, 0);
    QString stylesheetActive { R"(
        QFrame {
            margin-top: 0px;
            margin-bottom: 0px;
            border: 0px;
            background-color: rgba(0, 0, 0, 0%);
        }
    )" };
    activeLine->setStyleSheet(stylesheetActive);
    activeLine->raise();

    // generate animation thread
    animationThread = std::thread([this]() {
        qDebug() << "animation thread generated";
        while(this->needTerminate == false)
        {
            std::unique_lock<std::mutex> cvUniqueLock(this->mtxCV);
            this->cvAnimationIdleWait.wait(cvUniqueLock , [this]{ return this->needIncreaseStep || this->needDecreaseStep || this->needTerminate; }); // 애니메이션이 필요한 경우 또는 종료되어야 하는 경우 깨어남을 허용

            if (this->needTerminate) break;
            int dt = 1000.0 / 50.0;
            while (true)
            {
                {
                    std::lock_guard<std::mutex> lg(this->mtxAnimationStates);
                    qDebug() << "while looping... current step : " << this->step;
                    if (this->needIncreaseStep && this->step < max_step) ++this->step;
                    if (this->needDecreaseStep && this->step > 0) { --this->step; if (this->step < max_step/2) this->step = 0; }
                    emit this->colorStepChanged(this->step);
                    if (this->step <= 0 || this->step >= this->max_step) { this->needIncreaseStep = false; this->needDecreaseStep = false; break; }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(dt));
            }
        }
        qDebug() << "animation thread terminated";
    });

    // connect signal & slot
    connect(this, SIGNAL(colorStepChanged(int)), this, SLOT(setColor(int)));
}

LineHandle::~LineHandle()
{
    {
        std::unique_lock<std::mutex> cvUniqueLock(this->mtxCV);
        this->needTerminate = true;
        this->cvAnimationIdleWait.notify_one();
    }
    this->animationThread.join();
}

void LineHandle::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

void LineHandle::enterEvent(QEnterEvent *event)
{
    event->accept();
    std::unique_lock<std::mutex> cvUniqueLock(this->mtxCV);
    {
        std::lock_guard<std::mutex> lg(this->mtxAnimationStates);
        this->needIncreaseStep = true;
        this->needDecreaseStep = false;
        qDebug() << "[enter event]";
    }
    this->cvAnimationIdleWait.notify_one();
}

void LineHandle::leaveEvent(QEvent *event)
{
    event->accept();
    {
        std::lock_guard<std::mutex> lg(this->mtxAnimationStates);
        this->needIncreaseStep = false;
        this->needDecreaseStep = true;
        qDebug() << "[leave event]";
    }
    std::unique_lock<std::mutex> cvUniqueLock(this->mtxCV);
    this->cvAnimationIdleWait.notify_one();
}

void LineHandle::mouseMoveEvent(QMouseEvent* event)
{
}

void LineHandle::mouseReleaseEvent(QMouseEvent *event)
{
}

void LineHandle::connectTargetLayout(QLayout* layout)
{
    targetLayout = layout;
}

void LineHandle::setBaseColor(int r, int g, int b, int a)
{
    QString stylesheetPassive =
        "QFrame {"
        "   margin-top: 0px;"
        "   margin-bottom: 0px;"
        "   border: 0px;"
        "   background-color: rgba("+QString::number(r)+", "+QString::number(g)+", "+QString::number(b)+", "+QString::number(a)+");"
        "}";
    baseLine->setStyleSheet(stylesheetPassive);
}


void LineHandle::setColor(int new_step)
{
    int r = float(max_step - new_step)/max_step * start.red() + float(new_step)/max_step * end.red(); if(r < 0) r = 0;
    int g = float(max_step - new_step)/max_step * start.green() + float(new_step)/max_step * end.green(); if(g < 0) g = 0;
    int b = float(max_step - new_step)/max_step * start.blue() + float(new_step)/max_step * end.blue(); if(b < 0) b = 0;
    int a = float(new_step - max_step/2)/(max_step/2) * 100; if(a < 0) a = 0;

    int margin_top = new_step > 0 ? 0 : 2;
    int margin_bottom = new_step > 0 ? 0 : 1;
    QString stylesheet { ""
                         "QFrame {"
                         "  margin-top: "+QString::number(margin_top)+"px;"
                         "  margin-bottom: "+QString::number(margin_bottom)+"px;"
                         "  border: 0px;"
                         "  background-color: rgba("+QString::number(r)+", "+QString::number(g)+", "+QString::number(b)+", "+QString::number(a)+"%);"
                         "}" };
    activeLine->setStyleSheet(stylesheet);
}

void LineHandle::toggleFixedWidget()
{
}
