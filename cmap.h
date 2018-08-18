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
        int m_nFalg;
        int m_nWidth;
        int m_nHeight;
        void fillZero();
        void setBomb(int,int);
        void init(int,int,int);

public:
        CMap();
        CMap(int,int,int);
        ~CMap();

        //get function
        int getValue(int x,int y);
        int getCovered(int x,int y);
        int getWidth();
        int getHeight();

        //set function
        bool setValue(int x,int y,int value);
        bool setCovered(int x,int y,int covered);

        //set new
        void getNew(int,int,int);
};

#endif // CMAP_H
