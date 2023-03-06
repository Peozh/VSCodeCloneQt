#include "myminimapwidget.h"

MyMinimapWidget::MyMinimapWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setMouseTracking(true);

    this->styleSheet_textEdit = R"(
        QTextEdit {
            border: none;
            background-color: #222222;
            color: #eeeeee;
            font-family: "Consolas";
            font: 1px;
    })";
    this->p_textEdit = new QTextEdit(this);
    auto blockFmt = QTextBlockFormat();
    blockFmt.setLineHeight(80, QTextBlockFormat::ProportionalHeight);
    auto cursor_map = this->p_textEdit->textCursor();
    cursor_map.mergeBlockFormat(blockFmt);
    this->p_textEdit->setTextCursor(cursor_map);
    this->p_textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->p_textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->p_textEdit->setStyleSheet(styleSheet_textEdit);
    this->p_textEdit->setDisabled(true);
    this->p_textEdit->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);

    this->styleSheet_scrollbar = R"(
        QScrollBar:vertical {
            left: -10px;

            border: 0px solid #888888;
            background-color: rgba(0, 0, 0, 0%);
            width: 14px;
            margin: 0;
            border-radius: 0px;
        }
        QScrollBar::handle:vertical {
            background-color: rgba(255, 255, 255, 0%);
            min-height: 0px;
        }
        QScrollBar::handle:vertical:hover {
            background-color: rgba(255, 255, 255, 15%);
        }
        QScrollBar::handle:vertical:pressed {
            background-color: rgba(255, 255, 255, 20%);
        }

        /*reset arrows*/
        QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {
            background: none;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: none;
        }

        /*ignores*/
        QScrollBar::sub-line:vertical {
            border: none;
            height: 0px;
        }
        QScrollBar::add-line:vertical {
            border: none;
            height: 0px;
    })";
    this->p_scrollBar = new QScrollBar(this);
    this->p_scrollBar->setStyleSheet(styleSheet_scrollbar);


    auto p_layout = new QHBoxLayout(this);
    p_layout->setContentsMargins(0, 0, 0, 0);
    p_layout->addWidget(this->p_textEdit);
    this->setContentsMargins(0, 0, 0, 0);
    this->setLayout(p_layout);

    this->p_scrollBar->move(0, 0);
    this->p_scrollBar->resize(this->p_textEdit->width(), this->p_textEdit->height());
}

//void MyMinimapWidget::resizeEvent(QResizeEvent *event)
//{
//    QWidget::resizeEvent(event);
//    if (this->scrollbarHeight == 0) this->p_scrollBar->resize(this->p_textEdit->width(), this->p_textEdit->height());
//    else this->p_scrollBar->resize(this->p_textEdit->width(), this->scrollbarHeight);
//}

void MyMinimapWidget::setScrollBarHeight(int height)
{
    this->scrollbarHeight = height;
    this->p_scrollBar->resize(this->p_textEdit->width(), this->scrollbarHeight);
}

void MyMinimapWidget::enterEvent(QEnterEvent *event)
{
    if (event->type() == QEnterEvent::Enter)
    {
        QString temporary = R"(
            QScrollBar::handle:vertical {
                background-color: rgba(255, 255, 255, 10%);
        })";
        this->p_scrollBar->setStyleSheet(this->styleSheet_scrollbar + temporary);
    }
    QWidget::enterEvent(event);
}

void MyMinimapWidget::leaveEvent(QEvent *event)
{
    if (event->type() == QEvent::Leave)
    {
        QString temporary = R"(
            QScrollBar::handle:vertical {
                background-color: rgba(255, 255, 255, 0%);
        })";
        this->p_scrollBar->setStyleSheet(this->styleSheet_scrollbar + temporary);
    }
    QWidget::leaveEvent(event);
}
