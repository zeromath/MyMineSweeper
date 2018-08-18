#ifndef CMINE_H
#define CMINE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include "mylabel.h"
#include "mylabel2.h"
#include "mylabel3.h"
#include "mylabelex.h"
#include "const.h"
#include "crecord.h"
#include "cmap.h"
#include "mydlg.h"
#include "mydlg2.h"
#include "mydlg3.h"


namespace Ui {
    class CMine;
}

class CMine : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMine(QWidget *parent = 0);
    ~CMine();

public slots:
    void SearchLeft(int x, int y);
    void SearchRight(int x, int y);
    void SearchDouble(int x, int y);
    void failed();
    void success();
    void addtime();
    void restart();
    void setNew(int height,int width,int mine);

   // void DoubleClicked(int x,int y);
signals:
    void Failed();
    void Successed();

private:
    int getType();
    void unCover(int x,int y);
    void start();
    void clear();
    void Search(int x, int y);
    bool getSuccess();
    void initTime();
    void init();

    Ui::CMine *ui;
    MyLabel* mylabel[HEIGHT-2][WIDTH-2];
    //QMessageBox* mbox;
    QGridLayout* m_layout;
    QFont* m_qft;
    MyLabelEx *label_mine;
    MyLabelEx *label_time;
    MyDlg* dialog_mydlg;
    MyDlg2* dialog_mydlg2;
    MyDlg3* dialog_mydlg3;
    QLabel *label_minesum;
    MyLabel3 *label_timenum;
    QTimer* qtimer;
    //QMutex* qmtx;
    MyLabel2* mylabel2;


    CRecord* m_record;
    CMap* m_cmap;

    QString* m_name;
    bool m_start;
    int m_height;
    int m_width;
    int m_mine;
    int m_time;
    int nflag;
    int nopen;
};

#endif // CMINE_H
