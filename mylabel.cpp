#include "mylabel.h"

MyLabel::MyLabel(int x,int y)
{
    m_x=x;
    m_y=y;
    this->setFixedSize(18,18);
    this->setFrameStyle(6);
}

MyLabel::~MyLabel(){
}

void MyLabel::setCovered(){
    setPixmap(QPixmap(":/images/covered.png"));
}

void MyLabel::setFlag(){
    setPixmap(QPixmap(":/images/flag.png"));
}

void MyLabel::setValue(int value){
    switch(value){
    case MINE:   setPixmap(QPixmap(":/images/mine1.png")); break;
    case BLANK:  setPixmap(QPixmap(":/images/blank.png")); break;
    case 1:      setPixmap(QPixmap(":/images/1.png")); break;
    case 2:      setPixmap(QPixmap(":/images/2.png")); break;
    case 3:      setPixmap(QPixmap(":/images/3.png")); break;
    case 4:      setPixmap(QPixmap(":/images/4.png")); break;
    case 5:      setPixmap(QPixmap(":/images/5.png")); break;
    case 6:      setPixmap(QPixmap(":/images/6.png")); break;
    case 7:      setPixmap(QPixmap(":/images/7.png")); break;
    case 8:      setPixmap(QPixmap(":/images/8.png")); break;
    }
}

void MyLabel::mouseDoubleClickEvent(QMouseEvent *event){
        emit sDoubleClicked(m_x,m_y);
}

void MyLabel::mouseReleaseEvent(QMouseEvent* event){
    if (event->button()==Qt::LeftButton)
        emit sLeftClicked(m_x,m_y);
    else if (event->button()==Qt::RightButton)
        emit sRightClicked(m_x,m_y);
}
