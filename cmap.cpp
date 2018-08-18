#include "cmap.h"

void CMap::fillZero(){
        for (int i=0;i<HEIGHT;i++)
                for (int j=0;j<WIDTH;j++){
                        m_nData[i][j]=0;
                        m_bData[i][j]=0;
                }
}

void CMap::getNew(int height,int width,int minesum){
    fillZero();
    init(height+2,width+2,minesum);
};

CMap::CMap(int height=HEIGHT-2,int width=WIDTH-2,int minesum=99){getNew(height,width,minesum);}

CMap::~CMap(){};

int CMap::getValue(int x,int y){
    if(x<-1 || x>=m_nHeight || y<-1 || y>=m_nWidth) return WRONG;
        return m_nData[x+1][y+1];
}

int CMap::getCovered(int x,int y){
    if(x<-1 || x>=m_nHeight || y<-1 || y>=m_nWidth) return WRONG;
        return m_bData[x+1][y+1];
}

bool CMap::setValue(int x,int y,int value){
    m_nData[x+1][y+1]=value;
    return true;
}

bool CMap::setCovered(int x,int y,int covered){
        m_bData[x+1][y+1]=covered;
        return true;
}

void CMap::setBomb(int orderh, int orderw){
     m_nData[orderh][orderw] = MINE;
     for (int height = orderh - 1; height <= orderh + 1; height ++){
         for (int width = orderw - 1; width <= orderw + 1; width ++){
             if ((m_nData[height][width] != BOUNDARY) && (m_nData[height][width] != MINE))
             m_nData[height][width] ++;
         }
     }
     return ;
}

void CMap::init(int Height, int Width, int MineSum){
    this->m_nHeight = Height;
    this->m_nWidth = Width;
     srand(time(NULL));
     for (int i = 0; i < Height; i ++){
         m_nData[i][0] = BOUNDARY;
         m_nData[i][Width - 1] = BOUNDARY;
     }
     for (int j = 0; j < Width; j ++){
         m_nData[0][j] = BOUNDARY;
         m_nData[Height - 1][j] = BOUNDARY;
     }
     int area = (Height - 2) * (Width - 2);
     for (int bomb = 0; bomb < MineSum; bomb ++){
         int order = rand() % area;
         int orderh = order / (Width - 2) + 1;
         int orderw = order % (Width - 2) + 1;
         while (m_nData[orderh][orderw] == -1){
               order = (order + 1) % area;
               orderh = order / (Width - 2) + 1;
               orderw = order % (Width - 2) + 1;
         }
         setBomb(orderh, orderw);
     }
     return ;
}
