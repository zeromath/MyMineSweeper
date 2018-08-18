#include "mylabelex.h"

MyLabelEx::MyLabelEx()
{
    setFixedSize(36,36);
}

void MyLabelEx::mouseDoubleClickEvent(QMouseEvent *event){
        emit sClicked();
}
