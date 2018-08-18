#include "mylabel2.h"

MyLabel2::~MyLabel2(){
    delete name;
}

MyLabel2::MyLabel2(QString name)
{
    this->name=new QString(name);
    this->setAlignment(Qt::AlignCenter);
    this->setText(QString(QObject::tr("»¶Ó­Äã\n%1")).arg(name));
}

void MyLabel2::ChangeName(QString name){
    if (name.isEmpty()) return;
    delete this->name;
    this->name=new QString(name);
    this->setText(QString(QObject::tr("»¶Ó­Äã\n%1")).arg(name));
}

void MyLabel2::Refresh(){
    setText(QString(QObject::tr("¼ÌĞøÅ¬Á¦\n%1")).arg(*name));
}

void MyLabel2::Failed(){
    setText(QString(QObject::tr("ÄãÊäÁË..\n%1")).arg(*name));
}

void MyLabel2::Successed(){
    setText(QString(QObject::tr("ÄãÓ®À²£¡\n%1")).arg(*name));
}

void MyLabel2::mouseDoubleClickEvent(QMouseEvent *event){
    emit getName();
}

QString MyLabel2::Name(){
    return *name;
};
