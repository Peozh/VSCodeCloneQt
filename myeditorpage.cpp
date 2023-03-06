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
//    p_layout->
    this->setLayout(this->p_layout);

    // log & line count update
    connect(this->p_textEdit, &QTextEdit::textChanged, this, &MyEditorPage::printLog);
    connect(this->p_textEdit, SIGNAL(textChanged()), this, SLOT(updateLineCount()));
    // scroll value changed
    connect(this->p_textEdit->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(moveScrollBars(int)));
    // line count changed
//    connect(this, SIGNAL(lineCountChanged()), this, SLOT(applyLineCountToScrollBars()));
    // sync vertical scrollbars with textEdit
    this->setLineCount(p_textEdit->document()->lineCount());
    this->applyLineCountToScrollBars();
}

void MyEditorPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    // resize occurred
    this->applyVisibleHeightToScrollBars();
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
    qDebug() << "p_textEdit->verticalScrollBar()->maximum() before : " << p_textEdit->verticalScrollBar()->maximum();
    this->setLineCount(newLineCount);
    applyLineCountToScrollBars();
    qDebug() << "p_textEdit->verticalScrollBar()->maximum() after  : " << p_textEdit->verticalScrollBar()->maximum();
}

/*
 * update scrollBars when main text editor scrolled by wheel or arrows.
 */
void MyEditorPage::moveScrollBars(int value)
{
    // set value
    int lineHeight = this->p_textEdit->lineHeight;
    int documentHeight = this->p_textEdit->document()->size().height()-8;
    float ratio = 1.0;
    if (documentHeight-lineHeight != 0) ratio = 1.0 * value/(documentHeight-lineHeight);
    int minimapDocumentHeight = this->p_minimap->p_textEdit->document()->size().height();
    QFontMetricsF metric(this->p_minimap->p_textEdit->font());
    int minimapLineHeight = ceil(metric.lineSpacing());
    this->p_scroll_vertical->setValue(value);
    this->p_minimap->p_scrollBar->setValue(ratio * (minimapDocumentHeight-minimapLineHeight));
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
    this->p_textEdit->verticalScrollBar()->setMaximum((lineCount-1)*lineHeight);
    this->p_scroll_vertical->setMaximum((lineCount-1)*lineHeight);
    this->p_minimap->p_scrollBar->setMaximum(minimapDocumentHeight-minimapLineHeight);
//    qDebug() << "p_minimap setMaximum : " << minimapDocumentHeight-minimapLineHeight;
//    qDebug() << "   minimapDocumentHeight   : " << minimapDocumentHeight;
//    qDebug() << "   minimapLineHeight       : " << minimapLineHeight;

    // set page step
    int documentHeight = this->p_textEdit->document()->size().height()-8;
    int visibleHeight = qMax(this->p_textEdit->height()-8, 0);
    float visibleLineCount = 1.0*visibleHeight/lineHeight;
    int minimapVisibleHeight = qMax(this->p_minimap->p_textEdit->size().height(), 0);
    float factor = 1.0;
    if ((minimapVisibleHeight != 0) && (minimapDocumentHeight > minimapVisibleHeight)) factor = 1.0 * (minimapDocumentHeight) / minimapVisibleHeight;
    this->p_minimap->p_scrollBar->setPageStep(factor * visibleHeight/documentHeight*minimapDocumentHeight);
//    qDebug() << "p_minimap setPageStep : " << factor * visibleHeight/documentHeight*minimapDocumentHeight;
//    qDebug() << "   visibleHeight           : " << visibleHeight;
//    qDebug() << "   documentHeight          : " << documentHeight;
//    qDebug() << "   minimapDocumentHeight   : " << minimapDocumentHeight;

    // height of minimap scrollbar
    int minimapHeight = this->p_minimap->height();
    int minimapScrollBarHeight = minimapDocumentHeight + (visibleLineCount-1)*minimapLineHeight;
    minimapScrollBarHeight = std::min(minimapScrollBarHeight, minimapHeight);
    this->p_minimap->setScrollBarHeight(minimapScrollBarHeight);
//    qDebug() << "p_minimap setScrollBarHeight : " << minimapScrollBarHeight;
//    qDebug() << "   minimapDocumentHeight   : " << minimapDocumentHeight;
//    qDebug() << "   visibleLineCount        : " << visibleLineCount;
//    qDebug() << "   minimapLineHeight       : " << minimapLineHeight;
}

/*
 * update scrollBars when resize event.
 */
void MyEditorPage::applyVisibleHeightToScrollBars()
{
    int lineHeight = this->p_textEdit->lineHeight;
    int visibleHeight = qMax(this->p_textEdit->height()-8, 0);
    float  visibleLineCount = 1.0*visibleHeight/lineHeight;

    // page steps
    int documentHeight = this->p_textEdit->document()->size().height()-8;
    int minimapDocumentHeight = this->p_minimap->p_textEdit->document()->size().height();
    int minimapVisibleHeight = qMax(this->p_minimap->p_textEdit->size().height(), 0);
    float factor = 1.0;
    if ((minimapVisibleHeight != 0) && (minimapDocumentHeight > minimapVisibleHeight)) factor = 1.0 * (minimapDocumentHeight) / minimapVisibleHeight;
    this->p_scroll_vertical->setPageStep(visibleHeight);
    this->p_minimap->p_scrollBar->setPageStep(factor * visibleHeight/documentHeight*minimapDocumentHeight);

    // height of minimap scrollbar
    QFontMetricsF metric(this->p_minimap->p_textEdit->font());
    float miniLineHeight = ceil(metric.lineSpacing());
    int minimapHeight = this->p_minimap->height();
    int minimapScrollBarHeight = minimapDocumentHeight + (visibleLineCount-1)*miniLineHeight;
    minimapScrollBarHeight = qMin(minimapScrollBarHeight, minimapHeight);
    this->p_minimap->setScrollBarHeight(minimapScrollBarHeight);
}

/*
 *  update minimap's actual(hidden) vertical scrollBar.
 *  according to minimap's visible scrollBar.
 */
void MyEditorPage::scrollMinimap()
{

}
