#include "crecord.h"
#include<fstream>
#include<iostream>
#include <stdlib.h>
#include<string>

using namespace std;
CRecord::CRecord()
{
      int i,j;
      ifstream fin;
      fin.open("record");
      for (i=0;i<=2;i++)
      {
          fin>>type;
          for (j=0;j<=4;j++)
          {
             fin>>grade[type][j]>>names[type][j];
          }
      }
      fin.close();
      QFile::remove("record");
}
CRecord::~CRecord()
{
      int i,j;
      //system("del /q  C:\\Qt\\2010.05\\qt\\MyMineSweeper-build-desktop\\debug\\record");//DOS
      ofstream fout;
      fout.open("record");
      for (i=0;i<=2;i++)
      {
          fout<<i<<endl;
          for (j=0;j<=4;j++)
          {
            fout<<grade[i][j]<<endl;
            fout<<names[i][j]<<endl;
          }
      }
      fout.close();
}
void CRecord::addNewScore(int time,int type,QString pname)
{
     string name=string(pname.toStdString());
     int t,i;
     string n;
     grade[type][5]=time;
     names[type][5]=name;
     for (i=4;i>=0;i--)
      if (grade[type][i]>grade[type][i+1])
      {
          t=grade[type][i];
          grade[type][i]=grade[type][i+1];
          grade[type][i+1]=t;
          n=names[type][i];
          names[type][i]=names[type][i+1];
          names[type][i+1]=n;
      }

}
int CRecord::getScore(int index,int type)
{
    int i=999;
    if (index<=4)
    {
        return grade[type][index];
    }
    else return i;
}

QString CRecord::getName(int index,int type){
    QString* s;
    if (index<=4) s=new QString(names[type][index].c_str());
    else s=new QString("NULL");
    return *s;
}
