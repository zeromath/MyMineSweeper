#include "cmine.h"
#include "ui_cmine.h"


CMine::CMine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMine)
{
    ui->setupUi(this);

    m_mine = 99;
    m_height = HEIGHT-2;
    m_width = WIDTH-2;

    m_layout=new QGridLayout();
    m_layout->setSpacing(0);

    mbox=new QMessageBox();
    m_cmap=new CMap(m_height,m_width,m_mine);

    qmtx=new QMutex(QMutex::Recursive);

    label_mine=new QLabel();
    label_mine->setText(QString("the sum of mine is %1").arg(m_mine));

    m_qft=new QFont("Times", 10, QFont::Bold);

    m_layout->addWidget(label_mine,0,0,1,10);

    for (int i=0; i<m_height; i++)
        for (int j=0; j<m_width; j++)
        {
            mylabel[i][j]=new MyLabel(i,j);
            mylabel[i][j]->setCovered();
            mylabel[i][j]->setFont(*m_qft);
            connect(mylabel[i][j],SIGNAL(sLeftClicked(int,int)),this,SLOT(SearchLeft(int,int)));
            connect(mylabel[i][j],SIGNAL(sRightClicked(int,int)),this,SLOT(SearchRight(int,int)));
            connect(mylabel[i][j],SIGNAL(sDoubleClicked(int,int)),this,SLOT(SearchDouble(int,int)));
            m_layout->addWidget(mylabel[i][j],i+1,j);
        }

    connect(this,SIGNAL(Failed()),this,SLOT(failed()));
    ui->centralWidget->setLayout(m_layout);
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
    mbox->setText("you falied");
    mbox->exec();
    clear();
}

//no change size
void CMine::clear(){
    m_cmap->getNew(m_height,m_width,m_mine);
    for (int i=0; i<m_height; i++)
        for (int j=0; j<m_width; j++)
            mylabel[i][j]->setCovered();
    update();

}

void CMine::unCover(const int x,const int y){
    mylabel[x][y]->setValue(m_cmap->getValue(x,y));
    m_cmap->setCovered(x,y,OPEN);
}

void CMine::SearchLeft(int x, int y){
    qmtx->tryLock();
    qmtx->lock();
    if (m_cmap->getValue(x,y)==MINE){
        unCover(x,y);
        qmtx->unlock();
        emit Failed();
        return;
    }
    unCover(x,y);
    Search(x,y);
    qmtx->unlock();
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
                            }
                    }
                }
       }
}


void CMine::SearchRight(int x, int y)
{
    qmtx->tryLock();
    qmtx->lock();
    if (m_cmap->getCovered(x,y)==OPEN) return;
    if (m_cmap->getCovered(x,y)==FLAG){
        mylabel[x][y]->setCovered();
        m_cmap->setCovered(x,y,COVERED);
    }else{
        mylabel[x][y]->setFlag();
        m_cmap->setCovered(x,y,FLAG);
    }
    qmtx->unlock();
}

void CMine::SearchDouble(int x, int y)
{
    qmtx->tryLock();
    qmtx->lock();
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
                    qmtx->unlock();
                    return;
                }
                else{
                    unCover(x+m[i],y+n[i]);
                    Search(x+m[i],y+n[i]);
                }
            }
    qmtx->lock();
}
