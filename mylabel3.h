#ifndef MYLABEL3_H
#define MYLABEL3_H
#include <QLabel>

class MyLabel3:public QLabel
{
    Q_OBJECT
public:
    MyLabel3();
    void setType(int type);

signals:
    void Show(int type);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

private:
    int type;
};

#endif // MYLABEL3_H
