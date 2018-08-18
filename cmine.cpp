#include "cmine.h"
#include "ui_cmine.h"


void CMine::init(){
    label_timenum->setType(this->getType());

    m_layout->addWidget(label_mine,0,m_width-2,2,2);
    m_layout->addWidget(label_minesum,2,m_width-2,2,2);
    m_layout->addWidget(label_time,0,0,2,2);
    m_layout->addWidget(label_timenum,2,0,2,2);
    m_layout->addWidget(mylabel2,0,2,4,m_width-4);

    for (int i=0;i<m_height;i++)
        for (int j=0;j<m_width;j++){
            mylabel[i][j]->setCovered();
            m_layout->addWidget(mylabel[i][j],i+4,j);
        }

    m_layout->setSpacing(0);

}

CMine::CMine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMine)
{
    ui->setupUi(this);


    m_mine = 10;
    m_height = 9;
    m_width = 9;
    m_k=0;
    nflag=0;
    nopen=0;
    m_time=0;


    m_cmap=new CMap(m_height,m_width,m_mine);
    m_record=new CRecord();

    m_layout=new QGridLayout(this);

   // mbox=new QMessageBox();
    dialog_mydlg=new MyDlg();
    dialog_mydlg2=new MyDlg2();
    dialog_mydlg3=new MyDlg3(m_record);




    //qmtx=new QMutex(QMutex::Recursive);

    m_qft=new QFont("Harrington", 15, QFont::Bold);

    m_name=new QString(QObject::tr("JZ"));
    mylabel2=new MyLabel2(*m_name);
    mylabel2->setFont(*m_qft);

    label_minesum=new QLabel();
    label_minesum->setFixedSize(36,36);
    label_minesum->setAlignment(Qt::AlignLeft);

    label_timenum=new MyLabel3();
    label_timenum->setType(LOW);
    label_timenum->setFixedSize(36,36);
    label_timenum->setAlignment(Qt::AlignRight);

    label_mine=new MyLabelEx();
    label_mine->setAlignment(Qt::AlignRight);
    label_mine->setPixmap(QPixmap(":/images/label_mine.png"));

    label_time=new MyLabelEx();
    label_time->setAlignment(Qt::AlignLeft);
    label_time->setPixmap(QPixmap(":/images/label_time1.png"));


    label_minesum->setFont(*m_qft);
    label_minesum->setText(QString("%1").arg(m_mine));
    label_timenum->setFont(*m_qft);
    label_timenum->setText(QString("%1").arg(m_time));

    qtimer = new QTimer();
    //qsound = new QSound(":/sounds/explosion.wav");

    for (int i=0; i<HEIGHT-2; i++)
        for (int j=0; j<WIDTH-2; j++)
        {
            mylabel[i][j]=new MyLabel(i,j);
            connect(mylabel[i][j],SIGNAL(sLeftClicked(int,int)),this,SLOT(SearchLeft(int,int)));
            connect(mylabel[i][j],SIGNAL(sRightClicked(int,int)),this,SLOT(SearchRight(int,int)));
            connect(mylabel[i][j],SIGNAL(sDoubleClicked(int,int)),this,SLOT(SearchDouble(int,int)));
        }

    connect(this,SIGNAL(Failed()),this,SLOT(failed()));
    connect(this,SIGNAL(Successed()),this,SLOT(success()));
    connect(qtimer,SIGNAL(timeout()),this,SLOT(addtime()));
    connect(label_mine,SIGNAL(sClicked()),dialog_mydlg,SLOT(exec()));
    connect(label_time,SIGNAL(sClicked()),this,SLOT(restart()));
    connect(dialog_mydlg,SIGNAL(setNew(int,int,int)),this,SLOT(setNew(int,int,int)));
    connect(mylabel2,SIGNAL(getName()),dialog_mydlg2,SLOT(exec()));
    connect(dialog_mydlg2,SIGNAL(getName(QString)),mylabel2,SLOT(ChangeName(QString)));
    connect(label_timenum,SIGNAL(Show(int)),dialog_mydlg3,SLOT(Show(int)));

    init();

    ui->centralWidget->setLayout(m_layout);
    ui->centralWidget->setFixedSize(m_width*18,m_height*18+72);
    setFixedSize(m_width*18,m_height*18+90);
    ui->centralWidget->show();

}

CMine::~CMine()
{
    delete m_layout;
    delete m_qft;
    delete label_mine;
    delete label_time;
    delete dialog_mydlg;
    delete dialog_mydlg2;
    delete dialog_mydlg3;
    delete label_minesum;
    delete label_timenum;
    delete qtimer;
    delete mylabel2;
    delete m_record;
    delete m_cmap;
    delete m_name;
    //delete qsound;

    for (int i=0; i<HEIGHT-2; i++)
        for (int j=0; j<WIDTH-2; j++)
            delete mylabel[i][j];

    delete ui;
}

void CMine::failed(){
    qtimer->stop();
    //qsound->play();
    label_time->clear();
    label_time->setPixmap(QPixmap(":/images/label_time1.png"));
    mylabel2->Failed();
    for (int i=0;i<this->m_height;i++)
        for (int j=0;j<this->m_width;j++)
            if (m_cmap->getValue(i,j)==MINE && m_cmap->getCovered(i,j)==COVERED) unCover(i,j);
            else m_cmap->setCovered(i,j,WRONG);
    //clear();
}

void CMine::restart(){
    mylabel2->Refresh();
    qtimer->stop();
    clear();
}

void CMine::setNew(int height,int width,int mine){

    m_layout->removeWidget(label_mine);
    m_layout->removeWidget(label_minesum);
    m_layout->removeWidget(label_time);
    m_layout->removeWidget(label_timenum);
    m_layout->removeWidget(mylabel2);

    for (int i=0;i<m_height;i++)
        for (int j=0;j<m_width;j++)
            m_layout->removeWidget(mylabel[i][j]);


    m_height=height;
    m_width=width;
    m_mine=mine;

    init();

    ui->centralWidget->setFixedSize(m_width*18,m_height*18+72);
    setFixedSize(m_width*18,m_height*18+90);

    ui->centralWidget->update();
    ui->centralWidget->repaint();

    qtimer->stop();
    clear();
}

void CMine::success(){
    qtimer->stop();
    label_time->clear();
    label_time->setPixmap(QPixmap(":/images/label_time1.png"));
    for (int i=0;i<this->m_height;i++)
        for (int j=0;j<this->m_width;j++)
            m_cmap->setCovered(i,j,WRONG);

    m_record->addNewScore(m_time,getType(),mylabel2->Name());
    mylabel2->Successed();
}
//no change size
void CMine::clear(){
    m_cmap->getNew(m_height,m_width,m_mine);
    for (int i=0; i<m_height; i++)
        for (int j=0; j<m_width; j++)
            mylabel[i][j]->setCovered();
    nflag=0;
    nopen=0;
    label_minesum->setText(QString("%1").arg(m_mine));

    m_time=0;
    label_timenum->setText(QString("%1").arg(m_time));
    update();

}

void CMine::unCover(const int x,const int y){
    if (m_cmap->getCovered(x,y)==OPEN) return;
    nopen++;
    mylabel[x][y]->setValue(m_cmap->getValue(x,y));
    m_cmap->setCovered(x,y,OPEN);
}

void CMine::SearchLeft(int x, int y){
    //qmtx->tryLock();
    //qmtx->lock();
    if (m_cmap->getCovered(x,y)==FLAG || m_cmap->getCovered(x,y)==WRONG) return;
    if (m_cmap->getValue(x,y)==MINE){
        unCover(x,y);
        //qmtx->unlock();
        emit Failed();
        return;
    }
    if (m_time==0) initTime();
    unCover(x,y);
    if (getSuccess()){
        emit Successed();
        return;
    }
    Search(x,y);
    //qmtx->unlock();
}

void CMine::Search(int x, int y)
{
    if (m_cmap->getCovered(x,y)==FLAG || m_cmap->getCovered(x,y)==WRONG) return;
    int m[]={0,-1,1,0,0,-1,-1,1,1};
    int n[]={0,0,0,-1,1,-1,1,-1,1};
    int h=0,t=1,i,xx;
    int a[MAXLENGTH],b[MAXLENGTH];

    a[t]=x;
    b[t]=y;
    while (h<t)
    {
        h=h+1;
        xx=m_cmap->getValue(a[h],b[h]);
        //雷数
            if ((xx>=1)&&(xx<=8))
            {
                //unCover(a[h],b[h]);
            }
             else
             //无内容
             if (xx==BLANK)
             {
                //unCover(a[h],b[h]);
                for (i=1;i<=8;i++)
                    if (m_cmap->getCovered(a[h]+m[i],b[h]+n[i])==COVERED)
                    {
                        xx=m_cmap->getValue(a[h]+m[i],b[h]+n[i]);
                        //无内容or雷数
                        if ((xx==BLANK)||((xx>=1)&&(xx<=8)))
                            {
                                t=t+1;
                                a[t]=a[h]+m[i];
                                b[t]=b[h]+n[i];
                                unCover(a[t],b[t]);
                                if (getSuccess()){
                                    emit Successed();
                                    return;
                                }
                            }
                    }
                }
       }
}

void CMine::SearchRight(int x, int y)
{
    //qmtx->tryLock();
    //qmtx->lock();
    if (m_cmap->getCovered(x,y)==OPEN || m_cmap->getCovered(x,y)==WRONG) return;
    if (m_cmap->getCovered(x,y)==FLAG){
        mylabel[x][y]->setCovered();
        m_cmap->setCovered(x,y,COVERED);
        nflag--;
        label_minesum->setText(QString("%1").arg(m_mine-nflag));

    }else{
        if (nflag >= m_mine) return;
        mylabel[x][y]->setFlag();
        m_cmap->setCovered(x,y,FLAG);
        nflag++;
        label_minesum->setText(QString("%1").arg(m_mine-nflag));
        if (getSuccess()){
            emit Successed();
            return;
        }
    }
    //qmtx->unlock();
}

void CMine::SearchDouble(int x, int y)
{
    //qmtx->tryLock();
    //qmtx->lock();
    if (m_cmap->getCovered(x,y)==FLAG || m_cmap->getCovered(x,y)==WRONG) return;
    int m[]={0,-1,1,0,0,-1,-1,1,1};
    int n[]={0,0,0,-1,1,-1,1,-1,1};
    int i,g;
    g=0;
    for (i=1;i<=8;i++)
    {
        if (m_cmap->getCovered(x+m[i],y+n[i])==FLAG)
            g=g+1;
    }
    if (g==m_cmap->getValue(x,y))
        for (i=1;i<=8;i++)
        if (m_cmap->getCovered(x+m[i],y+n[i])!=FLAG && m_cmap->getValue(x+m[i],y+n[i])!=BOUNDARY){
                if (m_cmap->getValue(x+m[i],y+n[i])==MINE){
                    unCover(x+m[i],y+n[i]);
                    emit Failed();
                    //qmtx->unlock();
                    return;
                }
                else{
                    unCover(x+m[i],y+n[i]);
                    if (getSuccess()){
                        emit Successed();
                        return;
                    }
                    Search(x+m[i],y+n[i]);
                }
            }
    //qmtx->lock();
}

bool CMine::getSuccess(){
    return (nflag+nopen == m_height*m_width);
}

void CMine::initTime(){
    qtimer->start(1000);
}

void CMine::addtime(){
    m_time++;
    label_time->clear();
    switch(m_time%5){
    case 0: label_time->setPixmap(QPixmap(":/images/label_time1.png")); break;
    case 1: label_time->setPixmap(QPixmap(":/images/label_time2.png")); break;
    case 2: label_time->setPixmap(QPixmap(":/images/label_time3.png")); break;
    case 3: label_time->setPixmap(QPixmap(":/images/label_time4.png")); break;
    case 4: label_time->setPixmap(QPixmap(":/images/label_time5.png")); break;
}
    label_timenum->setText(QString("%1").arg(m_time));
}

int CMine::getType(){
    if (m_width==9) return LOW;
    if (m_width==16) return MIDDLE;
    return HIGH;
}

void CMine::keyPressEvent ( QKeyEvent * event ){
    switch(event->key()){
    case Qt::Key_R:  m_k=0; break;
    case Qt::Key_S: if (m_k==0) m_k++; break;
    case Qt::Key_H: if (m_k==1) m_k++; break;
    case Qt::Key_U: if (m_k==2) m_k++;
                    if (m_k==4) m_k++; break;
    case Qt::Key_X: if (m_k==3) m_k++; break;

    case Qt::Key_E: if (m_k==5){
            m_k=0;
            for (int i=0;i<m_height;i++)
                for (int j=0;j<m_width;j++)
                    if (m_cmap->getValue(i,j)==MINE && m_cmap->getCovered(i,j)!=FLAG)
                        this->SearchRight(i,j);
        }break;
    }
}
