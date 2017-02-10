/*

#include <string>
#include <opencv2\opencv.hpp>
//#include <iostream>

using namespace cv;
using namespace std;

const  int ConnectedNumber=10000;
int BoxNumber;
int CharSize;
 
struct box { int left;
             int right;
             int top;
             int bottom;
             float XCenter;
             float YCenter;
             int area;
             int IsPunctuation;
} Box[ConnectedNumber];
 
struct NODE{ int px;
             int py;
                struct NODE *link;
}*p,*q,*queue=NULL,*tail=NULL, *Connected[ConnectedNumber];
 
    int nHeight=pBin->GetHeight();//二值图高，宽
    int nWidth=pBin->GetWidth();
    enum{BLACK=0,WHITE=1};
     
    BYTE (*tempImage)[2000]=new BYTE[nHeight][2000];//二值图
 
         int i,j,k,cx,cy,currentX,currentY;
 
    for(k=0;k<ConnectedNumber;k++) Connected[k]=NULL;
     
    //扫描文档tempImage
       k=0;
       for(cy=0;cy<nHeight;cy++)
        for(cx=0;cx<nWidth;cx++) 
            if(tempImage[cy][cx]==BLACK)//若遇到一个前景像点p(x,y)
            { //把该点链接到Connected[k]
              p=(NODE *)malloc(sizeof(NODE));
              p->py=cy;  p->px=cx;
              p->link=Connected[k];//这个链表是后进的在前面
              Connected[k]=p;
              //把该点从tempImage文档中消去
              tempImage[cy][cx]=1;
              //把该点进队到队列queue的尾部
              q=(NODE *)malloc(sizeof(NODE));
              q->py=cy; q->px=cx; q->link=NULL;  
              if(queue==NULL){ queue=q; tail=q; }
              else      { tail->link=q; tail=q; }
              while( queue!=NULL )// 队列queue 非空 
              {//取出队首结点作为当前点
               currentY=queue->py;  currentX=queue->px;
               //若当前点与tempImage中的前景像点Pi(x,y)在8邻域相邻接
                for(i=-1;i<=1;i++)
                    for(j=-1;j<=1;j++)//tempImage[currentY+0][currentX+0]已经消去
                                        //图像前景像点加、减1不能越过数组边界
                        if((currentY+i)>=0 && (currentY+i)<nHeight
                            && (currentX+j)>=0 && (currentX+j)<nWidth
                             && tempImage[currentY+i][currentX+j]==BLACK )
                        {//把这些前景像点链接到Connected[k]
                         p=(NODE *)malloc(sizeof(NODE));
                         p->py=currentY+i; p->px=currentX+j; 
                         p->link=Connected[k];//这个链表是后进的在前面
                         Connected[k]=p;
                         //把这些前景像点从tempImage文档中消去
                         tempImage[currentY+i][currentX+j]=1;
                         //把这些前景像点进队到队列queue的尾部
                         q=(NODE *)malloc(sizeof(NODE));
                         q->py=currentY+i; q->px=currentX+j; q->link=NULL;  
                         tail->link=q; tail=q; 
                        }
               //释放队首结点
                q=queue; queue=queue->link; free(q);
              }
             k=k+1;
            }
 
 
    for(i=0;i<k;i++)
    { Box[i].left=nWidth-1;
      Box[i].right=0;
      Box[i].top=nHeight-1;
      Box[i].bottom=0;
      p=Connected[i]; 
      while(p!=NULL)
      { if(Box[i].left>p->px)   Box[i].left=p->px;
        if(Box[i].right<p->px)  Box[i].right=p->px;
        if(Box[i].top>p->py)    Box[i].top=p->py;
        if(Box[i].bottom<p->py) Box[i].bottom=p->py;
        p=p->link;
      }
    }

	*/