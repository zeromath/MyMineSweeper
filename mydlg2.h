#ifndef MYDLG2_H
#define MYDLG2_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

class MyDlg2:public QDialog
{
    Q_OBJECT
public:
    MyDlg2();
    ~MyDlg2();

signals:
    void getName(QString name);

public slots:
    void getName();
    int exec();

private:

    QLineEdit* name;
    QPushButton* yes;
    QLabel* tips;
    QGridLayout* layout;
};

#endif // MYDLG2_H
