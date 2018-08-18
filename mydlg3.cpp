#include "mydlg3.h"
#define NAME(x) (x==LOW)?(QObject::tr("初级版")):((x==HIGH)?(QObject::tr("高级版")):(QObject::tr("中级版")))

MyDlg3::MyDlg3(CRecord* crd)
{
    this->crd=crd;
    yes=new QPushButton(QObject::tr("膜拜之"));
    layout=new QGridLayout(this);

    title=new QLabel("");
    number=new QLabel(QObject::tr("名次"));
    name=new QLabel(QObject::tr("名字"));
    score=new QLabel(QObject::tr("时间"));

    layout->addWidget(title,0,0,1,3);
    layout->addWidget(number,1,0);
    layout->addWidget(name,1,1);
    layout->addWidget(score,1,2);

    for (int i=0;i<5;i++)
        for (int j=0;j<3;j++){
            data[i][j]=new QLabel();
            layout->addWidget(data[i][j],2+i,j);
        }

    layout->addWidget(yes,7,0,1,3);
    this->setLayout(layout);

    connect(yes,SIGNAL(clicked()),this,SLOT(accept()));

}

void MyDlg3::Show(int type){
    title->setText(QString(QObject::tr("扫雷英雄榜 %1")).arg(NAME(type)));
    for (int i=0;i<5;i++){
        data[i][0]->setText(QString("%1").arg(i));
        data[i][1]->setText(QString("%1").arg(crd->getScore(i,type)));
        data[i][2]->setText(crd->getName(i,type));
    }
    this->setModal(true);
    this->show();
}
