#include "cmine.h"
#include "ui_cmine.h"


void CMine::init(){

    m_layout->addWidget(label_mine,0,0,2,2);
    m_layout->addWidget(label_minesum,0,2,2,2);
    m_layout->addWidget(label_time,0,m_width-2,2,2);
    m_layout->addWidget(label_timenum,0,m_width-4,2,2);

    for (int i=0;i<m_height;i++)
        for (int j=0;j<m_width;j++){
            mylabel[i][j]->setCovered();
            m_layout->addWidget(mylabel[i][j],i+2,j);
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
    nflag=0;
    nopen=0;
    m_time=0;


    m_layout=new QGridLayout(this);

    mbox=new QMessageBox();
    dialog_mydlg=new MyDlg();
    m_cmap=new CMap(m_height,m_width,m_mine);

    //qmtx=new QMutex(QMutex::Recursive);

    label_mine=new MyLabelEx();
    label_minesum=new QLabel(); label_minesum->setFixedSize(26,26);
    label_time=new MyLabelEx();
    label_timenum=new QLabel(); label_timenum->setFixedSize(26,26);

    pixmap_mine=new QPixmap(":/images/label_mine.png");
    label_mine->setPixmap(*pixmap_mine);
    pixmap_time=new QPixmap(":/images/label_time.png");
    label_time->setPixmap(*pixmap_time);

    m_qft=new QFont("Harrington", 15, QFont::Bold);
    label_minesum->setFont(*m_qft);
    label_minesum->setText(QString("%1").arg(m_mine));
    label_timenum->setFont(*m_qft);
    label_timenum->setText(QString("%1").arg(m_time));

    qtimer = new QTimer();

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

    init();

    ui->centralWidget->setLayout(m_layout);
    ui->centralWidget->setFixedSize(m_width*18,m_height*18+26);
    setFixedSize(m_width*18,m_height*18+26);
    ui->centralWidget->show();

}

CMine::~CMine()
{
    for (int i=m_height-1; i>=0; i--)
        for (int j=m_width-1; j>=0; j--)
            delete mylabel[i][j];
    delete m_cmap;
    delete m_layout;
    delete mbox;
    delete ui;
}

void CMine::failed(){
    qtimer->stop();
    mbox->setText("you falied");
    mbox->exec();
    clear();
}

void CMine::restart(){
    qtimer->stop();
    clear();
}

void CMine::setNew(int height,int width,int mine){
    m_layout->removeWidget(label_mine);
    m_layout->removeWidget(label_minesum);
    m_layout->removeWidget(label_time);
    m_layout->removeWidget(label_timenum);

    for (int i=0;i<m_height;i++)
        for (int j=0;j<m_width;j++)
            m_layout->removeWidget(mylabel[i][j]);


    m_height=height;
    m_width=width;
    m_mine=mine;

    init();

    ui->centralWidget->setFixedSize(m_width*18,m_height*18+26);
    setFixedSize(m_width*18,m_height*18+26);

    ui->centralWidget->update();
    ui->centralWidget->repaint();

    qtimer->stop();
    clear();
}

void CMine::success(){
    qtimer->stop();
    mbox->setText("you win!!!");
    mbox->exec();
    clear();
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
    if (m_cmap->getCovered(x,y)==FLAG) return;
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
    if (m_cmap->getCovered(x,y)==FLAG) return;
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
    if (m_cmap->getCovered(x,y)==OPEN) return;
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
    label_timenum->setText(QString("%1").arg(m_time));
}
