#ifndef CRECORD_H
#define CRECORD_H

class CRecord
{
    //record the top 5 of every game;
public:
    CRecord();
    ~CRecord();
    void addNewScore(int time,int type); //time is the number of the sec the user used, the type will be one of the  HIGH,MIDDLE,LOW
    int getScore(int index,int type);//get the index'st grade e.g. getScore(0,LOW) returns the hightest score in the low game;

private:
    //your code
};

#endif // CRECORD_H
