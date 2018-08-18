#include "mylabelex.h"

MyLabelEx::MyLabelEx()
{
    setFixedSize(26,26);
}

void MyLabelEx::mouseDoubleClickEvent(QMouseEvent *event){
        emit sClicked();
}
