#include "myeditorpage.h"

MyEditorPage::MyEditorPage(QWidget *parent)
    : QWidget{parent}
{
    this->p_layout = new QHBoxLayout(this);
    this->p_textEdit = new MyTextEdit(this);
    this->p_minimap = new MyMinimapWidget(this);
    this->p_scroll_vertical = new QScrollBar(this);

    // set MyTextEdit
    p_textEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    p_textEdit->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
    p_textEdit->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
    p_textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    p_textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    p_textEdit->connectMinimap(this->p_minimap->p_textEdit);

    // set minimap
    p_minimap->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    p_minimap->p_scrollBar->setSingleStep(1);
    p_minimap->p_textEdit->document()->setDocumentMargin(0);

    // set vertical scrollbar
    p_scroll_vertical->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    QString style_scroll_vertical { R"(
        QScrollBar:vertical {
            left: -10px;

            border: 1px solid #444444;
            border-right: 0px;
            background-color: #222222;
            width: 16px;
            margin: 0;
            border-radius: 0px;
            padding-left: -1px;
            margin-left: 1px;
            padding-right: -1px;
        }
        QScrollBar::handle:vertical {
            background-color: rgba(255, 255, 255, 20%);
            min-height: 20px;
        }
        QScrollBar::handle:vertical:hover {
            background-color: rgba(255, 255, 255, 25%);
        }
        QScrollBar::handle:vertical:pressed {
            background-color: rgba(255, 255, 255, 30%);
        }

        /*reset arrows*/
        QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {
            background: none;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: none;
        }

        /*ignore*/
        QScrollBar::sub-line:vertical {
            border: none;
            background-color: #ff0000;
            height: 0px;
            border-top-left-radius: 0px;
            border-top-right-radius: 0px;
            subcontrol-position: top;
            subcontrol-origin: margin;
        }
        QScrollBar::sub-line:vertical:hover {
        }
        QScrollBar::sub-line:vertical:pressed {
        }
        QScrollBar::add-line:vertical {
            border: none;
            background-color: #ff0000;
            height: 0px;
            border-bottom-left-radius: 0px;
            border-bottom-right-radius: 0px;
            subcontrol-position: bottom;
            subcontrol-origin: margin;
        }
        QScrollBar::add-line:vertical:hover {
        }
        QScrollBar::add-line:vertical:pressed {
        })"
    };
    p_scroll_vertical->setStyleSheet(style_scroll_vertical);

    // inside layout
    p_layout->addWidget(p_textEdit);
    p_layout->addWidget(p_minimap);
    p_layout->addWidget(p_scroll_vertical);
    p_layout->setStretch(0, 9);
    p_layout->setStretch(1, 1);
    p_layout->setStretch(2, 0);
    p_layout->setContentsMargins(0, 0, 0, 0);
    p_layout->setSpacing(0);
    this->setLayout(this->p_layout);




    // log & line count update
//    connect(this->p_textEdit, &QTextEdit::textChanged, this, &MyEditorPage::printLog);
    connect(this->p_textEdit, SIGNAL(textChanged()), this, SLOT(updateLineCount()));
    // scroll value changed
    connect(this->p_textEdit->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(moveScrollBars(int)));
    // line count changed
    connect(this, SIGNAL(lineCountChanged()), this, SLOT(applyLineCountToScrollBars()));
    // sync vertical scrollbars with textEdit
    this->setLineCount(p_textEdit->document()->lineCount());
//    this->applyLineCountToScrollBars();
//    this->applyVisibleHeightToScrollBars();
}

void MyEditorPage::resizeEvent(QResizeEvent *event)
{
    qDebug() << "resize event";
    QWidget::resizeEvent(event);
    // resize occurred
    this->applyVisibleHeightToScrollBars();


    // document margines
    int lineHeight = this->p_textEdit->lineHeight;
    QFontMetricsF metric(this->p_minimap->p_textEdit->font());
    float minimapLineHeight = ceil(metric.lineSpacing());
    auto frameFormat = this->p_minimap->p_textEdit->document()->rootFrame()->frameFormat();
    frameFormat.setBottomMargin((float)(this->height() - this->p_textEdit->lineHeight - 4)*minimapLineHeight/lineHeight);
    this->p_minimap->p_textEdit->document()->rootFrame()->setFrameFormat(frameFormat);

    // scroll hidden
    int value = this->p_textEdit->verticalScrollBar()->value();
    auto hiddenMaximum = this->p_minimap->p_textEdit->verticalScrollBar()->maximum();
    if (hiddenMaximum == 0) return;
    auto maximum = this->p_textEdit->verticalScrollBar()->maximum();
    float ratio = 0.0;
    if (maximum != 0) ratio = (float)value/maximum;
    this->p_minimap->p_textEdit->verticalScrollBar()->setValue(round(ratio*hiddenMaximum));
}

int MyEditorPage::getLineCount() const
{
    return this->lineCount;
}
void MyEditorPage::setLineCount(int newValue)
{
    if (this->lineCount == newValue) return;
    this->lineCount = newValue;
    emit lineCountChanged();
}
void MyEditorPage::printLog() const
{
    int lineHeight = this->p_textEdit->lineHeight;

//    qDebug() << "lineCount : " << lineCount;
//    qDebug() << "pageSize : " << this->p_textEdit->document()->pageSize();
//    qDebug() << "size : " << this->p_textEdit->document()->size();
//    qDebug() << "height : " << this->p_textEdit->document()->size().height();

//    qDebug() << "vertical   max : " << this->p_textEdit->verticalScrollBar()->maximum();
//    qDebug() << "horizontal max : " << this->p_textEdit->horizontalScrollBar()->maximum();
//    qDebug() << "vertical   value : " << this->p_textEdit->verticalScrollBar()->value();
//    qDebug() << "horizontal value : " << this->p_textEdit->horizontalScrollBar()->value();
}
void MyEditorPage::updateLineCount()
{
    int newLineCount = this->p_textEdit->document()->lineCount();
    qDebug() << "updateLineCount() : " << lineCount << " -> " << newLineCount;
    this->setLineCount(newLineCount);
}

/*
 * update scrollBars when main text editor scrolled by wheel or arrows.
 */
void MyEditorPage::moveScrollBars(int value)
{
    qDebug() << "documentHeight : " << this->p_textEdit->document()->size().height();
    qDebug() << "scrollbar maximum : " << this->p_textEdit->verticalScrollBar()->maximum();

    this->p_scroll_vertical->setValue(value);
    this->p_minimap->p_scrollBar->setValue(value);

    auto hiddenMaximum = this->p_minimap->p_textEdit->verticalScrollBar()->maximum();
    if (hiddenMaximum == 0) return;
    auto maximum = this->p_textEdit->verticalScrollBar()->maximum();
    float ratio = (float)value/maximum;
    this->p_minimap->p_textEdit->verticalScrollBar()->setValue(round(ratio*hiddenMaximum));

}

/*
 * update scrollBars when line count changed.
 */
void MyEditorPage::applyLineCountToScrollBars()
{

    int lineHeight = this->p_textEdit->lineHeight;
    QFontMetricsF metric(this->p_minimap->p_textEdit->font());
    float minimapLineHeight = ceil(metric.lineSpacing()); // float miniLineHeight = qMax(metric.lineSpacing(), metric.boundingRect("a").height());
    int minimapDocumentHeight = this->p_minimap->p_textEdit->document()->size().height();

    // maximum values
    int maximum = this->p_textEdit->verticalScrollBar()->maximum();
    this->p_scroll_vertical->setMaximum(maximum);
    this->p_minimap->p_scrollBar->setMaximum(maximum);

    // height of minimap scrollbar
    int minimapHeight = this->p_minimap->height();
    int minimapScrollBarHeight = minimapDocumentHeight;
    float minimapBottomMargin = (float)(this->height() - this->p_textEdit->lineHeight - 4)*minimapLineHeight/lineHeight;
    this->p_textEdit->setMinimapBottomMargin(minimapBottomMargin);
    minimapScrollBarHeight = std::min(minimapScrollBarHeight, minimapHeight);
    this->p_minimap->setScrollBarHeight(minimapScrollBarHeight);

    // set page step
    int minimapVisibleHeight = qMax(this->p_minimap->p_textEdit->size().height(), 0);
    int pageStep = this->p_textEdit->verticalScrollBar()->pageStep();
    float factor = 1.0;
    if ((minimapVisibleHeight != 0) && (minimapDocumentHeight + minimapBottomMargin > minimapVisibleHeight)) factor = 1.0 * (minimapDocumentHeight + minimapBottomMargin) / minimapVisibleHeight;
    this->p_minimap->p_scrollBar->setPageStep(factor * pageStep);
}

/*
 * update scrollBars when resize event.
 */
void MyEditorPage::applyVisibleHeightToScrollBars()
{
    int lineHeight = this->p_textEdit->lineHeight;
    QFontMetricsF metric(this->p_minimap->p_textEdit->font());
    float minimapLineHeight = ceil(metric.lineSpacing());

    // document margines
    auto frameFormat = this->p_textEdit->document()->rootFrame()->frameFormat();
    frameFormat.setBottomMargin(this->height() - this->p_textEdit->lineHeight - 4);
    frameFormat.setRightMargin(30);
    this->p_textEdit->document()->rootFrame()->setFrameFormat(frameFormat);

    // height of minimap scrollbar
    int documentHeight = this->p_textEdit->document()->size().height();
    int minimapDocumentHeight = this->p_minimap->p_textEdit->document()->size().height();
//    qDebug() << "old minimapDocumentHeight : " << minimapDocumentHeight;
//    minimapDocumentHeight = (float)documentHeight/lineHeight*minimapLineHeight;
//    qDebug() << "new minimapDocumentHeight : " << minimapDocumentHeight;
//    this->p_minimap->p_textEdit->verticalScrollBar()->setMaximum(minimapDocumentHeight);
    float minimapBottomMargin = (float)(this->height() - this->p_textEdit->lineHeight - 4)*minimapLineHeight/lineHeight;
    int minimapHeight = this->p_minimap->height();
    int minimapScrollBarHeight = this->lineCount*minimapLineHeight + minimapBottomMargin;
    minimapScrollBarHeight = qMin(minimapScrollBarHeight, minimapHeight);
    this->p_minimap->setScrollBarHeight(minimapScrollBarHeight);


    // set page step
    int minimapVisibleHeight = qMax(this->p_minimap->p_textEdit->size().height(), 0);
//    float minimapBottomMargin = (float)(this->height() - this->p_textEdit->lineHeight - 4)*minimapLineHeight/lineHeight;
    this->p_textEdit->setMinimapBottomMargin(minimapBottomMargin);
    int pageStep = this->p_textEdit->verticalScrollBar()->pageStep();
    qDebug() << "page step : " << pageStep;
    float factor = 1.0;
    if ((minimapVisibleHeight != 0) && (minimapDocumentHeight > minimapVisibleHeight)) factor = 1.0 * (minimapDocumentHeight) / minimapVisibleHeight;
    qDebug() << "factor : " << factor;
    this->p_scroll_vertical->setPageStep(pageStep);
    this->p_minimap->p_scrollBar->setPageStep(factor * pageStep);
}

/*
 *  update minimap's actual(hidden) vertical scrollBar.
 *  according to minimap's visible scrollBar.
 */
void MyEditorPage::scrollMinimap()
{

}
