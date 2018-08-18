#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QPushButton>
#include <QMouseEvent>

class MyButton : public QPushButton
{
    Q_OBJECT

public:
    MyButton(int x=0,int y=0,QWidget* parent=0);
    void SetPosition(int x,int y);
signals:
    void sLeftClicked(int x,int y);
    void sRightClicked(int x,int y);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
private:
    int m_x;
    int m_y;
};

#endif // MYBUTTON_H
