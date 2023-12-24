#include "titlepartwidget.h"

TitlePartWidget::TitlePartWidget(QWidget *parent)
    : QWidget{parent}
{
    constexpr int fixedHeight = 30;
    this->leftSpace = new QWidget(this);
    {
        auto policy = leftSpace->sizePolicy();
        policy.setHorizontalPolicy(QSizePolicy::Preferred);
        policy.setVerticalPolicy(QSizePolicy::Fixed);
        leftSpace->setSizePolicy(policy);
//        leftSpace->setMaximumWidth((titleTotalLength-200) / 3); // 타이틀 총 길이에 따라 변함
//        if (titleTotalLength < 200) leftSpace->setMaximumWidth(1);
        leftSpace->setFixedHeight(fixedHeight);
        leftSpace->setStyleSheet("QWidget {background-color: rgb(70, 70, 70);}");
    }

    this->title_head = new QWidget(this);
    {
        auto policy = title_head->sizePolicy();
        policy.setHorizontalPolicy(QSizePolicy::Expanding);
        policy.setVerticalPolicy(QSizePolicy::Fixed);
        title_head->setSizePolicy(policy);
        title_head->setMaximumWidth(220);
        title_head->setMinimumWidth(60);
        title_head->setFixedHeight(fixedHeight);
        title_head->setStyleSheet("QWidget {background-color: rgb(45, 45, 45);}");
    }

    this->title_tail = new QWidget(this);
    {
        auto policy = title_tail->sizePolicy();
        policy.setHorizontalPolicy(QSizePolicy::Preferred);
        policy.setVerticalPolicy(QSizePolicy::Fixed);
        title_tail->setSizePolicy(policy);
        title_tail->setMinimumWidth(10);
//        title_tail->setMaximumWidth(titleTotalLength - 200); // 총 길이에 따라 변함
//        if (titleTotalLength < 200) title_tail->setMaximumWidth(1);
        title_tail->setFixedHeight(fixedHeight);
        title_tail->setStyleSheet("QWidget {background-color: rgb(70, 70, 70);}");
    }

    auto* layout = new QHBoxLayout(this);
    {
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        layout->addWidget(leftSpace);
        layout->addWidget(title_head);
        layout->addWidget(title_tail);

        layout->setStretch(0, 1); // left space 1 of 1:3
        layout->setStretch(1, 3000); // title_head
        layout->setStretch(2, 3); // title_tail, right length 3 of 1:3
    }
    this->setLayout(layout);

    this->label = new QLabel(this);
    {
        this->label->raise();
        this->title = "Visual Studio Code";
        this->setTitle(title);
        //.linux:lang(ko){font-family:system-ui,Ubuntu,Droid Sans,Source Han Sans K,Source Han Sans JR,Source Han Sans,UnDotum,FBaekmuk Gulim,sans-serif}
        //.mac{--monaco-monospace-font:"SF Mono",Monaco,Menlo,Courier,monospace}
        //.windows{--monaco-monospace-font:Consolas,"Courier New",monospace}
        //.linux{--monaco-monospace-font:"Ubuntu Mono","Liberation Mono","DejaVu Sans Mono","Courier New",monospace}
        this->label->setStyleSheet(
            "QLabel { "
            "   color: rgb(230, 230, 230);"
            "   font: 9pt 'Segoe UI';"
            "}");
        auto policy = label->sizePolicy();
        policy.setHorizontalPolicy(QSizePolicy::Expanding);
        this->label->setSizePolicy(policy);
    }

    this->setMaximumWidth(leftSpace->maximumWidth() + title_head->maximumWidth() + title_tail->maximumWidth());
}

void TitlePartWidget::resizeEvent(QResizeEvent *event)
{
    auto newShortenTitle = getShortenTitle(title);
    this->label->setText(newShortenTitle);
    this->label->move(title_head->geometry().left(), 0);
}

void TitlePartWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        emit windowDraggedTo(dragStartWindowPos + event->globalPosition() - dragStartPoint);
    }
}

void TitlePartWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragStartPoint = event->globalPosition();
        dragStartWindowPos = window()->pos();
    }
}

int TitlePartWidget::getTitleTotalLength()
{
    return this->titleTotalLength;
}

void TitlePartWidget::setTitle(QString str)
{
    this->title = str;
    makeCumulativeLength(title);
    auto newShortenTitle = getShortenTitle(title);
    this->label->setText(newShortenTitle);
    this->label->setMinimumWidth(titleTotalLength);

    leftSpace->setMaximumWidth((titleTotalLength-200) / 3); // 타이틀 총 길이에 따라 변함
    if (titleTotalLength < 200) leftSpace->setMaximumWidth(1);
    title_tail->setMaximumWidth(titleTotalLength - 200); // 총 길이에 따라 변함
    if (titleTotalLength < 200) title_tail->setMaximumWidth(1);
    maximumWidth = leftSpace->maximumWidth() + title_head->maximumWidth() + title_tail->maximumWidth();
//    qDebug() << "inner maximum width : " << maximumWidth;
//    qDebug() << "inner leftSpace->maximumWidth() : " << leftSpace->maximumWidth();
//    qDebug() << "inner title_head->maximumWidth() : " << title_head->maximumWidth();
//    qDebug() << "inner title_tail->maximumWidth() : " << title_tail->maximumWidth();
    this->setMaximumWidth(maximumWidth);
}

void TitlePartWidget::makeCumulativeLength(QString str)
{

    QFontMetricsF metric(this->label->font());
    this->cumulativeLength = std::vector<float>{};
    float sumStrWidth = 0;
    QString sumStr = "";
    for (QChar c : str) {
        sumStr += c;
        sumStrWidth = metric.boundingRect(sumStr).width();
        cumulativeLength.push_back(sumStrWidth);
        qDebug() << sumStrWidth;
    }

    this->titleTotalLength = qCeil(metric.boundingRect(title).width());
    qDebug() << "titleTotalLength = " << titleTotalLength;
}

QString TitlePartWidget::getShortenTitle(QString str)
{
    if (str.length() == 0) return "";
    int availableWidth = this->title_head->width() + this->title_tail->width() - this->title_tail->minimumWidth();
    if (this->title_head->width() + this->title_tail->width() >= titleTotalLength) availableWidth = this->title_head->width() + this->title_tail->width();
    qDebug() << "availableWidth = " << availableWidth;
    const auto idx = binarySearch(0, cumulativeLength.size()-1, availableWidth);
    qDebug() << "idx = " << idx;
    auto newTitle = str.mid(0, idx+1);
    if (idx+1 == cumulativeLength.size()) return newTitle;
    return newTitle + "...";
}

size_t TitlePartWidget::binarySearch(size_t stIdx, size_t enIdx, float val) // return closest cumulativeLength[idx] <= val
{
    if (stIdx == enIdx) return stIdx;
    size_t pivot = (stIdx + enIdx + 1) / 2;
    if (cumulativeLength[pivot] > val) return binarySearch(stIdx, pivot-1, val);
    else return binarySearch(pivot, enIdx, val);
}
