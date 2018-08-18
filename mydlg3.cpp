#include "mydlg3.h"
#define NAME(x) (x==LOW)?(QObject::tr("������")):((x==HIGH)?(QObject::tr("�߼���")):(QObject::tr("�м���")))

MyDlg3::MyDlg3(CRecord* crd)
{
    this->crd=crd;
    yes=new QPushButton(QObject::tr("Ĥ��֮"));
    layout=new QGridLayout(this);

    title=new QLabel("");
    number=new QLabel(QObject::tr("����"));
    name=new QLabel(QObject::tr("����"));
    score=new QLabel(QObject::tr("ʱ��"));

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
    title->setText(QString(QObject::tr("ɨ��Ӣ�۰� %1")).arg(NAME(type)));
    for (int i=0;i<5;i++){
        data[i][0]->setText(QString("%1").arg(i));
        data[i][1]->setText(QString("%1").arg(crd->getScore(i,type)));
        data[i][2]->setText(crd->getName(i,type));
    }
    this->setModal(true);
    this->show();
}
