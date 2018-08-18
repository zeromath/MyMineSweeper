#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>
#include "const.h"
#include <QString>
#include <QMouseEvent>

class MyLabel:public QLabel
{
    Q_OBJECT

public:
    MyLabel(int x=0,int y=0);
    void setValue(int value);

signals:
    void sDoubleClicked(int x,int y);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    int m_x;
    int m_y;

};

#endif // MYLABEL_H
