#include "sizelimitedtextedit.h"

SizeLimitedTextEdit::SizeLimitedTextEdit(int limitedSize,QWidget *parent):QTextEdit(parent)
{
    this->limitedSize=limitedSize;
    connect(this,SIGNAL(textChanged()),this,SLOT(onTextChanged()));
}

SizeLimitedTextEdit::~SizeLimitedTextEdit()
{

}

void SizeLimitedTextEdit::onTextChanged()
{
    QString str=this->toPlainText();
    if(str.size()>limitedSize)
    {
        str.resize(limitedSize);
        this->setText(str);
        this->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
    }
}
