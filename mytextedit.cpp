#include "mytextedit.h"

void MyTextEdit::updateMinimap()
{
    if (this->p_minimap_ == nullptr) return;
    auto old_value = p_minimap_->verticalScrollBar()->value();
    p_minimap_->setText(this->toPlainText());
    auto ff = p_minimap_->document()->rootFrame()->frameFormat();
    ff.setBottomMargin(this->minimapBottomMargin);
    p_minimap_->document()->rootFrame()->setFrameFormat(ff);
    p_minimap_->verticalScrollBar()->setValue(old_value);
}

MyTextEdit::MyTextEdit(QWidget *parent) : QTextEdit(parent)
{
    connect(this, &QTextEdit::textChanged, this, &MyTextEdit::updateMinimap);
    this->setStyleSheet(R"(
        QTextEdit {
            border: 0px;
            background-color: #222222;
            color: #eeeeee;
            font-family: "Consolas";
        })"
    );
    auto blockFmt = QTextBlockFormat();
    blockFmt.setLineHeight(100, QTextBlockFormat::ProportionalHeight);
    auto cursor_text = this->textCursor(); cursor_text.mergeBlockFormat(blockFmt); this->setTextCursor(cursor_text);
    QFontMetricsF metric(this->font());
    this->lineHeight = qCeil(qMax(metric.lineSpacing(), metric.boundingRect("a").height()));
    this->setAcceptRichText(false);
    //    qDebug() << "QFontMetricsF line height : " << lineHeight;

//    this->setViewportMargins(0, 0, 30, 200);
}


void MyTextEdit::connectMinimap(QTextEdit *p_minimap)
{
    this->p_minimap_ = p_minimap;
}

void MyTextEdit::setMinimapBottomMargin(int margin)
{
    this->minimapBottomMargin = margin;
}
