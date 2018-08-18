#ifndef CMINE_H
#define CMINE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include "mylabel.h"
#include "mylabelex.h"
#include "const.h"
#include "cmap.h"
#include "mydlg.h"


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
    void unCover(int x,int y);
    void start();
    void clear();
    void Search(int x, int y);
    bool getSuccess();
    void initTime();
    void init();

    Ui::CMine *ui;
    MyLabel* mylabel[HEIGHT-2][WIDTH-2];
    QMessageBox* mbox;
    QGridLayout* m_layout;
    QFont* m_qft;
    MyLabelEx *label_mine;
    MyLabelEx *label_time;
    MyDlg* dialog_mydlg;
    QLabel *label_minesum;
    QLabel *label_timenum;
    QPixmap* pixmap_mine;
    QPixmap* pixmap_time;
    QTimer* qtimer;
    //QMutex* qmtx;


    CMap* m_cmap;

    bool m_start;
    int m_height;
    int m_width;
    int m_mine;
    int m_time;
    int nflag;
    int nopen;
};

#endif // CMINE_H
