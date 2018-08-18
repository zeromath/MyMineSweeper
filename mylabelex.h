#ifndef MYLABELEX_H
#define MYLABELEX_H

#include <QLabel>

class MyLabelEx : public QLabel
{
    Q_OBJECT

public:
    MyLabelEx();
signals:
    void sClicked();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);


};

#endif // MYLABELEX_H
