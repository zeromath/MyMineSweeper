#include "crecord.h"

using namespace std;

CRecord::CRecord()
{
    file=new QFile("record");
    if (!file->exists()){
        for (int i=0;i<3;i++)
            for (int j=0;j<5;j++){
                grade[i][j]=999;
                names[i][j]=QString("NULL");
            }
    }else{
      int i,j;
      file->open(QFile::ReadOnly);
      QTextStream stream(file);
      QString line;
      for (i=0;i<3;i++){
          line = stream.readLine();
          type = line.toInt();
          for (j=0;j<=4;j++)
          {
              line = stream.readLine();
              grade[type][j]=line.toInt();
              names[type][j] = stream.readLine();
          }
      }
      file->close();
      file->remove();
  }
}
CRecord::~CRecord()
{
      int i,j;
      file->open(QFile::WriteOnly);
      QTextStream stream(file);
      for (i=0;i<=2;i++)
      {
          stream<<i<<ENDL;
          for (j=0;j<=4;j++)
          {
            stream<<grade[i][j]<<ENDL;
            stream<<names[i][j]<<ENDL;
          }
      }
      file->close();
      delete file;
}
void CRecord::addNewScore(int time,int type,QString name)
{
     //string name=string(pname.toStdString());
     int t,i;
     QString n;
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
    return (index<=4)?(names[type][index]):(QString("NULL"));
}
