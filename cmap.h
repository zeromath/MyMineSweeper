#ifndef CMAP_H
#define CMAP_H

#include "const.h"
#include <time.h>
#include <stdlib.h>

class CMap{
private:
        int m_nData[HEIGHT][WIDTH];
        int m_bData[HEIGHT][WIDTH];
        int m_nMineSum;
        int m_nWidth;
        int m_nHeight;
        void fillZero();
        void setBomb(const int,const int);
        void init(const int,const int,const int);

public:
        CMap();
        CMap(const int,const int,const int);
        ~CMap();

        //get function
        int getValue(const int x,const int y);
        int getCovered(const int x,const int y);

        //set function
        bool setValue(const int x,const int y,const int value);
        bool setCovered(const int x,const int y,const int covered);

        //set new
        void getNew(int,int,int);
};

#endif // CMAP_H
