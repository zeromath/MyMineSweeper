#include "cmine.h"
#include "ui_cmine.h"


CMine::CMine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMine)
{
    ui->setupUi(this);

    m_cmap=new CMap(HEIGHT-2,WIDTH-2,99);

    m_layout=new QGridLayout();
    m_layout->setSpacing(0);

    mbox=new QMessageBox();

    init(16,30,99,m_layout);

}


void CMine::init(int height,int width,int mine,QGridLayout* layout){
    m_mine = mine;
    m_height = height;
    m_width = width;
    for (int i=0; i<m_height; i++)
        for (int j=0; j<m_width; j++)
        {
            mylabel[i][j]=new MyLabel(i,j);
            mybutton[i][j]=new MyButton(i,j,this);
            connect(mybutton[i][j],SIGNAL(sLeftClicked(int,int)),this,SLOT(SearchLeft(int,int)));
            connect(mybutton[i][j],SIGNAL(sRightClicked(int,int)),this,SLOT(SearchRight(int,int)));
            connect(mylabel[i][j],SIGNAL(sDoubleClicked(int,int)),this,SLOT(SearchDouble(int,int)));
            layout->addWidget(mylabel[i][j],i+1,j);
            layout->addWidget(mybutton[i][j],i+1,j);
        }
    start();

    ui->centralWidget->setLayout(m_layout);
    ui->centralWidget->show();
}

void CMine::start(){
    m_cmap->getNew(m_height,m_width,m_mine);

    for (int i=0;i<m_height;i++)
        for (int j=0;j<m_width;j++)
            mylabel[i][j]->setValue(m_cmap->getValue(i,j));
}

CMine::~CMine()
{
    delete ui;
}

void CMine::failed(){
    mbox->setText("you falied");
    mbox->exec();
    clear();
}

//no change size
void CMine::clear(){
    for (int i=0; i<m_height; i++)
        for (int j=0; j<m_width; j++)
        {
            if (mybutton[i][j]->text()!="") mybutton[i][j]->setText("");
            if (!mybutton[i][j]->isVisible()){
                mybutton[i][j]->setVisible(true);
                mybutton[i][j]->setEnabled(true);
            }
        }
    update();
    start();

}

void CMine::unCover(int x,int y){
    mybutton[x][y]->setVisible(false);
    mybutton[x][y]->setEnabled(false);
    m_cmap->setCovered(x,y,OPEN);
    if (m_cmap->getValue(x,y)==MINE) failed();
}

void CMine::SearchLeft(int x, int y)
{
    if (m_cmap->getCovered(x,y)==FLAG) return;
    int m[]={0,-1,1,0,0,-1,-1,1,1};
    int n[]={0,0,0,-1,1,-1,1,-1,1};
    int h=0,t=1,i,xx;
    int a[MAXLENGTH],b[MAXLENGTH];

    a[t]=x;
    b[t]=y;
    while (h!=t)
    {
        h=h+1;
        xx=m_cmap->getValue(a[h],b[h]);
        //雷
        if (xx==MINE)
        {
            unCover(a[h],b[h]);
        }
        else
            //雷数
            if ((xx>=1)&&(xx<=8))
            {
                unCover(a[h],b[h]);
            }
             else
             //无内容
             if (xx==BLANK)
             {
                unCover(a[h],b[h]);
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
                            }
                    }
                }
       }
}


void CMine::SearchRight(int x, int y)
{
    if (m_cmap->getCovered(x,y)==FLAG){
        mybutton[x][y]->setText("");
        m_cmap->setCovered(x,y,COVERED);
    }else{
        mybutton[x][y]->setText("F");
        m_cmap->setCovered(x,y,FLAG);
    }
}

void CMine::SearchDouble(int x, int y)
{
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
            if (m_cmap->getCovered(x+m[i],y+n[i])!=FLAG)
            SearchLeft(x+m[i],y+n[i]);
}
