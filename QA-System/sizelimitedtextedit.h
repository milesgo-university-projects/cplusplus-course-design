#ifndef SIZELIMITEDTEXTEDIT
#define SIZELIMITEDTEXTEDIT
#include <QWidget>
#include <QTextEdit>

class SizeLimitedTextEdit:public QTextEdit
{
    Q_OBJECT
    public:
        SizeLimitedTextEdit(int limitedSize=50,QWidget *parent=0);
        ~SizeLimitedTextEdit();
    private:
        int limitedSize;
    private slots:
        void onTextChanged();
};


#endif // SIZELIMITEDTEXTEDIT

