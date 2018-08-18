#ifndef CMINE_H
#define CMINE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include "mybutton.h"
#include "mylabel.h"
#include "const.h"
#include "cmap.h"

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

   // void DoubleClicked(int x,int y);


private:
    void unCover(int x,int y);
//    void setFlag(int x,int y);
    void init(int height,int width,int mine,QGridLayout* layout);
    void start();
    void failed();
    void clear();

    Ui::CMine *ui;
    MyButton* mybutton[HEIGHT][WIDTH];
    MyLabel* mylabel[HEIGHT][WIDTH];
    QMessageBox* mbox;
    QGridLayout* m_layout;

    CMap* m_cmap;

    bool m_start;
    int m_height;
    int m_width;
    int m_mine;
};

#endif // CMINE_H
