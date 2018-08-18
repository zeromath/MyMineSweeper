#include "mylabel2.h"

MyLabel2::~MyLabel2(){
    delete name;
}

MyLabel2::MyLabel2(QString name)
{
    this->name=new QString(name);
    this->setAlignment(Qt::AlignCenter);
    this->setText(QString(QObject::tr("��ӭ��\n%1")).arg(name));
}

void MyLabel2::ChangeName(QString name){
    if (name.isEmpty()) return;
    delete this->name;
    this->name=new QString(name);
    this->setText(QString(QObject::tr("��ӭ��\n%1")).arg(name));
}

void MyLabel2::Refresh(){
    setText(QString(QObject::tr("����Ŭ��\n%1")).arg(*name));
}

void MyLabel2::Failed(){
    setText(QString(QObject::tr("������..\n%1")).arg(*name));
}

void MyLabel2::Successed(){
    setText(QString(QObject::tr("��Ӯ����\n%1")).arg(*name));
}

void MyLabel2::mouseDoubleClickEvent(QMouseEvent *event){
    emit getName();
}

QString MyLabel2::Name(){
    return *name;
};
