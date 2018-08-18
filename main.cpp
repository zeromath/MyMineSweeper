#include <QtGui/QApplication>
#include "cmine.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    CMine w;
    w.show();

    return a.exec();
}
