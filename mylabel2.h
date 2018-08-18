#ifndef MYLABEL2_H
#define MYLABEL2_H

#include <QLabel>
#include <QString>

class MyLabel2:public QLabel
{
    Q_OBJECT

public:
    MyLabel2(QString name);
    ~MyLabel2();

    void Failed();
    void Successed();
    void Refresh();
    QString Name();

signals:
    void getName();

public slots:
    void ChangeName(QString name);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QString* name;

};

#endif // MYLABEL2_H
