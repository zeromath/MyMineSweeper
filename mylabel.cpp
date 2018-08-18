#include "mylabel.h"

MyLabel::MyLabel(int x,int y)
{
    m_x=x;
    m_y=y;
    this->setAlignment(Qt::AlignCenter);
    this->setFixedSize(18,18);
    this->setFrameStyle(6);

    pixmap = new QPixmap*[12];
    pixmap[0] = new QPixmap(":/images/blank.png");
    pixmap[1] = new QPixmap(":/images/1.png");
    pixmap[2] = new QPixmap(":/images/2.png");
    pixmap[3] = new QPixmap(":/images/3.png");
    pixmap[4] = new QPixmap(":/images/4.png");
    pixmap[5] = new QPixmap(":/images/5.png");
    pixmap[6] = new QPixmap(":/images/6.png");
    pixmap[7] = new QPixmap(":/images/7.png");
    pixmap[8] = new QPixmap(":/images/8.png");
    pixmap[9] = new QPixmap(":/images/mine.png");
    pixmap[10] = new QPixmap(":/images/covered.png");
    pixmap[11] = new QPixmap(":/images/flag.png");
}

MyLabel::~MyLabel(){
    delete [] pixmap;
}

void MyLabel::setCovered(){
    setPixmap(*pixmap[10]);
}

void MyLabel::setFlag(){
    setPixmap(*pixmap[11]);
}

void MyLabel::setValue(int value){
    switch(value){
    case MINE:   setPixmap(*pixmap[9]); break;
    case BLANK:  setPixmap(*pixmap[0]); break;
    case 1:      setPixmap(*pixmap[1]); break;
    case 2:      setPixmap(*pixmap[2]); break;
    case 3:      setPixmap(*pixmap[3]); break;
    case 4:      setPixmap(*pixmap[4]); break;
    case 5:      setPixmap(*pixmap[5]); break;
    case 6:      setPixmap(*pixmap[6]); break;
    case 7:      setPixmap(*pixmap[7]); break;
    case 8:      setPixmap(*pixmap[8]); break;
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
