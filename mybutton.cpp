#include "mybutton.h"

MyButton::MyButton(int x,int y,QWidget* parent):QPushButton(parent){
        m_x=x;
        m_y=y;
        setFixedSize(22,22);
}

void MyButton::SetPosition(int x,int y){
    m_x=x;
    m_y=y;
}

void MyButton::mouseReleaseEvent(QMouseEvent *event){
    if (event->button()==Qt::LeftButton)
        emit sLeftClicked(m_x,m_y);
    else if (event->button()==Qt::RightButton)
        emit sRightClicked(m_x,m_y);
}
