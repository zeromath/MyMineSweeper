#include "mydlg2.h"

MyDlg2::MyDlg2()
{
    name= new QLineEdit();
    yes=new QPushButton(QObject::tr("就用这个名字啦"));
    tips=new QLabel(QObject::tr("请输入一个不太长的名字"));

    layout=new  QGridLayout(this);
    layout->addWidget(tips,0,0);
    layout->addWidget(name,1,0);
    layout->addWidget(yes,2,0);

    this->setLayout(layout);

    connect(yes,SIGNAL(clicked()),this,SLOT(getName()));
}



void MyDlg2::getName(){
    emit getName(name->text());
    QDialog::accept();
};


int MyDlg2::exec(){
this->setModal(true);
show();
return 0;
}

MyDlg2::~MyDlg2(){
    delete name;
    delete yes;
    delete tips;
    delete layout;
}
