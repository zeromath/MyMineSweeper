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
    ~MyLabel();
    void setValue(int value);
    void setCovered();
    void setFlag();

signals:
    void sDoubleClicked(int x,int y);
    void sLeftClicked(int x,int y);
    void sRightClicked(int x,int y);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

private:
    int m_x;
    int m_y;
    QPixmap **pixmap;

};

#endif // MYLABEL_H
