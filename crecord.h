#ifndef CRECORD_H
#define CRECORD_H
#include <string>
#include <QString>
#include <QFile>
#include "const.h"
using namespace std;

class CRecord
{
    //record the top 5 of every game;
public:
    CRecord();
    ~CRecord();
    void addNewScore(int time,int type,QString pname); //time is the number of the sec the user used, the type will be one of the  HIGH,MIDDLE,LOW
    int getScore(int index,int type);//get the index'st grade e.g. getScore(0,LOW) returns the hightest score in the low game;
    QString getName(int index,int type);

private:
    //your code
    int grade[3][6];
    string names[3][6];
    int type;
};

#endif // CRECORD_H
