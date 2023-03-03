#include "mytextedit.h"

void MyTextEdit::updateMinimap()
{
    if (this->p_minimap_ == nullptr) return;
    p_minimap_->setText(this->toPlainText());
}

MyTextEdit::MyTextEdit(QWidget *parent) : QTextEdit(parent)
{
    connect(this, &QTextEdit::textChanged, this, &MyTextEdit::updateMinimap);
    this->setStyleSheet(R"(
        QTextEdit {
            background-color: #222222;
            color: #eeeeee;
            font-family: "Consolas";
        })"
    );
}

void MyTextEdit::connectMinimap(QTextEdit *p_minimap)
{
    this->p_minimap_ = p_minimap;
}
