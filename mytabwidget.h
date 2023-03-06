#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QTabWidget>
#include <QObject>
#include <QTabBar>
#include <QStylePainter>
#include <QStyleOptionTab>
#include <QLabel>

#include <QVBoxLayout>
#include <QFrame>

class MyTab : public QWidget
{
    Q_OBJECT
public:
    MyTab(QString str, QWidget* parent = nullptr)  : QWidget(parent)
    {
        QVBoxLayout *layout = new QVBoxLayout(this); // this keyword is iimportant, we tell the widget the parent withn be showed
        layout->setContentsMargins(0, 0, 0, 0);
        this->setLayout(layout);
        this->resize(150, 80);

        QLabel* label = new QLabel(str, this);
        QString strFont = "font: 75 108pt 'Comic Sans MS',";
        label->setStyleSheet(strFont);
        label->setAlignment(Qt::AlignCenter);
        label->setMargin(0); // to stretch the widget
        layout->addWidget(label);

        auto line = new QFrame;
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        layout->addWidget(line);

        qDebug() << "TheWatch Constructor";
    }
};

class MyTabBar : public QTabBar
{
    QVector<int> mUnSaved;
public:
    void setUnsaved(int index){
        if(index >= count() || index < 0)
            return;
        mUnSaved << index;
        update();
    }
    void setSaved(int index){
        if(!mUnSaved.contains(index))
            return;
        mUnSaved.remove(mUnSaved.indexOf(index));
        update();
    }
protected:
    void paintEvent(QPaintEvent */*event*/){

        QStylePainter painter(this);
        QStyleOptionTab opt;

        for(int i = 0;i < count();i++)
        {
            initStyleOption(&opt,i);
            painter.save();
            if(mUnSaved.contains(i)){
                painter.setFont(QFont("Times", 10, QFont::Bold));
            }
            painter.drawControl(QStyle::CE_TabBarTabShape, opt);
            painter.drawControl(QStyle::CE_TabBarTabLabel,opt);
            painter.restore();
        }
    }
};

class MyTabWidget : public QTabWidget
{
    Q_OBJECT

    MyTabBar *mTabBar;
public:
    MyTabWidget(QWidget* parent = nullptr);

};

#endif // MYTABWIDGET_H
