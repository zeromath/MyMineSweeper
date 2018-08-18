#include "mylabel3.h"

MyLabel3::MyLabel3()
{
}

void MyLabel3::setType(int type){
    this->type=type;
}

void MyLabel3::mouseDoubleClickEvent(QMouseEvent* event){
    emit Show(type);
}
