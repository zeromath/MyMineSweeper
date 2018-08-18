#include "mylabel.h"

MyLabel::MyLabel(int x,int y)
{
    m_x=x;
    m_y=y;
    this->setAlignment(Qt::AlignCenter);
    this->setFixedSize(22,22);
}

void MyLabel::setValue(int value){
    switch(value){
    case MINE:   setText("M");  break;
    case BLANK:  setText(" ");  break;
    case 1:      setText("1");  break;
    case 2:      setText("2");  break;
    case 3:      setText("3");  break;
    case 4:      setText("4");  break;
    case 5:      setText("5");  break;
    case 6:      setText("6");  break;
    case 7:      setText("7");  break;
    case 8:      setText("8");  break;
    }
}
//some problem
void MyLabel::mouseReleaseEvent(QMouseEvent* event){
    if (event->button()==Qt::RightButton)
        emit sDoubleClicked(m_x,m_y);
}
