//cv hw3

#include <string>
#include <opencv2\opencv.hpp>
//#include <iostream>

using namespace cv;
using namespace std;

/*
void swap(char x,char y)
{
	char z;
	z=x ;x=y ;y=z;
}
*/

int main()
{
	string imgname = "D:\\course\\CV\\HW\\hw3\\lena.bmp";
 
	//讀圖
	Mat img = imread(imgname,0); 
	if(img.empty()) //如果讀圖失敗
	{
		return -1;
	}
	int imgSize=img.rows*img.cols;

	//histogram初始化
	int histogram[256];
	memset(histogram,0,sizeof(histogram));
	//for (int i = 0; i <= 255; i++)
	//{
	//	histogram[i]=0;
	//}

	//統計histogram
	Mat_<uchar>::iterator iteHis=img.begin<uchar>(),
						  iteHisEnd=img.end<uchar>();
	while (iteHis!=iteHisEnd)
	{
		histogram[(*iteHis)]++;
		iteHis++;
	}

	//畫histogram
	Mat imgHistogram(300,300,CV_8UC1,Scalar(0));
	Point a,b;
	a.x=20;  a.y=280;
	b.x=275; b.y=280;
	line(imgHistogram,a,b,CV_RGB(255,255,255),1,8,0);
	a.x=20; a.y=280;
	b.x=20; b.y=0;
	line(imgHistogram,a,b,CV_RGB(255,255,255),1,8,0);
	for (int k = 0; k <= 255; k++)
	{
		a.x=20+k; a.y=280;
		b.x=20+k; b.y=280-( histogram[k]/10 );
		line(imgHistogram,a,b,CV_RGB(255,255,255),1,8,0);
	}

	//cumPercentile初始化
	double cumPercentile[256];
	memset(cumPercentile,0,sizeof(cumPercentile));

	//累加比例分佈
	cumPercentile[0]=histogram[0];
	for(int i=1;i<=255;i++)
	{		
		cumPercentile[i]=cumPercentile[i-1]+(double)(histogram[i])/(double)(imgSize);
	}

	//均衡后的圖
	Mat imgEqualization;
	img.copyTo(imgEqualization);
	//替換
	Mat_<uchar>::iterator iteEqu=imgEqualization.begin<uchar>(),
						  iteEquEnd=imgEqualization.end<uchar>();
	while (iteEqu!=iteEquEnd)
	{
		(*iteEqu)=(int)(cumPercentile[(*iteEqu)]*255.0+0.5);
		iteEqu++;
	}

	//histogram初始化
	int hisEqualization[256];
	memset(hisEqualization,0,sizeof(hisEqualization));

	//統計histogram
	Mat_<uchar>::iterator iteHisEqu=imgEqualization.begin<uchar>(),
						  iteHisEquEnd=imgEqualization.end<uchar>();
	while (iteHisEqu!=iteHisEquEnd)
	{
		hisEqualization[(*iteHisEqu)]++;
		iteHisEqu++;
	}

	//畫histogram
	Mat imgHisEqualization(300,300,CV_8UC1,Scalar(0));
	Point aEqu,bEqu;
	aEqu.x=20;  aEqu.y=280;
	bEqu.x=275; bEqu.y=280;
	line(imgHisEqualization,aEqu,bEqu,CV_RGB(255,255,255),1,8,0);
	aEqu.x=20; aEqu.y=280;
	bEqu.x=20; bEqu.y=0;
	line(imgHisEqualization,aEqu,bEqu,CV_RGB(255,255,255),1,8,0);
	for (int k = 0; k <= 255; k++)
	{
		aEqu.x=20+k; aEqu.y=280;
		bEqu.x=20+k; bEqu.y=280-( hisEqualization[k]/10 );
		line(imgHisEqualization,aEqu,bEqu,CV_RGB(255,255,255),1,8,0);
	}


	namedWindow("img",1); //創建窗口
	namedWindow("histogram",1);
	namedWindow("equalization",1);
	namedWindow("hisEqualization",1);

	imshow("img", img); //顯示圖
	imshow("histogram", imgHistogram);
	imshow("equalization", imgEqualization);
	imshow("hisEqualization", imgHisEqualization);
	
	imwrite("D:\\course\\CV\\HW\\hw3\\imgHistogram.bmp",imgHistogram);
	imwrite("D:\\course\\CV\\HW\\hw3\\imgEqualization.bmp",imgEqualization);
	imwrite("D:\\course\\CV\\HW\\hw3\\imgHisEqualization.bmp",imgHisEqualization);

	waitKey();
 
	return 0;
}