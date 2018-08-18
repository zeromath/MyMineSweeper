#include <QtGui/QApplication>
#include "cmine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMine w;
    w.show();

    return a.exec();
}
