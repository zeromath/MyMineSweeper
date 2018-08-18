#include "mydlg.h"

MyDlg::MyDlg()
{
    button_high=new QPushButton(QString("high"),this);
    button_mid=new QPushButton(QString("mid"),this);
    button_low=new QPushButton(QString("low"),this);

    layout=new QGridLayout(this);
    layout->addWidget(button_high,0,0);
    layout->addWidget(button_mid,1,0);
    layout->addWidget(button_low,2,0);

    connect(button_high,SIGNAL(clicked()),this,SLOT(collectdata_high()));
    connect(button_mid,SIGNAL(clicked()),this,SLOT(collectdata_mid()));
    connect(button_low,SIGNAL(clicked()),this,SLOT(collectdata_low()));
    connect(this,SIGNAL(newdata(int,int,int)),this,SLOT(dlgexe(int,int,int)));
}

MyDlg::~MyDlg(){
    delete button_high;
    delete button_mid;
    delete button_low;
    delete layout;
};


void MyDlg::collectdata_mid(){
    emit newdata(16,16,40);
};

void MyDlg::collectdata_low(){
    emit newdata(9,9,10);
};


void MyDlg::collectdata_high(){
    emit newdata(HEIGHT-2,WIDTH-2,99);
};

void MyDlg::dlgexe(int height,int width,int mine){
    emit setNew(height,width,mine);
    QDialog::accept();
}

int MyDlg::exec(){
    this->setModal(true);
    show();
    return 0;
}
