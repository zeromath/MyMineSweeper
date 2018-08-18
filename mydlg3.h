#ifndef MYDLG3_H
#define MYDLG3_H
#include "crecord.h"
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class MyDlg3:public QDialog
{
    Q_OBJECT

public:
    MyDlg3(CRecord* crd);

public slots:
    void Show(int type);

private:
    QGridLayout* layout;
    QLabel* data[5][3];
    QLabel *title;
    QLabel* number,*name,*score;
    QPushButton* yes;
    CRecord* crd;


};

#endif // MYDLG3_H
