#include <QApplication>
#include "overall.h"
#include <stdexcept>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);//最后一个窗口关闭后自动退出程序
    Function::setStyle("../option/style.qss");
    Overall::init();
    return a.exec();
}
