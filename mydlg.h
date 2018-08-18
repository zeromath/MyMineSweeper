#ifndef MYDLG_H
#define MYDLG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include "const.h"

class MyDlg:public QDialog
{
    Q_OBJECT

public:
    MyDlg();

signals:
    void setNew(int height,int width,int sum);
    void newdata(int height,int width,int sum);

public slots:
    void dlgexe(int,int,int);
    int exec();
    void collectdata_low();
    void collectdata_mid();
    void collectdata_high();

private:
    QPushButton* button_high;
    QPushButton* button_mid;
    QPushButton* button_low;
    QGridLayout* layout;
};

#endif // MYDLG_H
