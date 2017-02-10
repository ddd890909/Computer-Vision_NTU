//cv hw4

//#include <string>
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

struct Kernel
{
    int kCols; //结构元素的行宽
    int kRows; //列高
    int anchorX; //结构原点位置水平坐标
    int anchorY; //结构原点位置垂直坐标
	Mat values;
	Kernel(int cols, int rows, int ancx, int ancy, Mat val)
		:kCols(cols), kRows(rows), anchorX(ancx), anchorY(ancy), values(val.clone())
	{
	}
};

void pixelDil( const Mat src, Mat dst, const Kernel ker, int sI, int sJ )
{
	for (int kI = 0; kI < ker.kRows; kI++)
	{
		for (int kJ = 0; kJ < ker.kCols; kJ++)
		{
			int sX=sI-ker.anchorX+kI;
			int sY=sJ-ker.anchorY+kJ;
			if (sX>=0 && sX<=src.rows-1 &&
				sY>=0 && sY<=src.cols-1)
			{
				if (ker.values.at<uchar>(kI,kJ)==255)
				{
					dst.at<uchar>(sX,sY)=255;
				}
			}			
		}
	}
}

void Dilation( const Mat src, Mat dst, const Kernel ker )
{
	if(ker.values.empty())
	{
		printf("error");
		return;
	}

	for (int sI = 0; sI < src.rows; sI++)
	{
		for (int sJ = 0; sJ < src.cols; sJ++)
		{
			if (src.at<uchar>(sI,sJ)==255)
			{
				//dilation
				pixelDil(src, dst, ker, sI, sJ);
			}
		}
	}
}

void pixelEro( const Mat src, Mat dst, const Kernel ker, int sI, int sJ )
{
	int kA=0;
	for (int kI = 0; kI < ker.kRows; kI++)
	{
		for (int kJ = 0; kJ < ker.kCols; kJ++)
		{
			int sX=sI-ker.anchorX+kI;
			int sY=sJ-ker.anchorY+kJ;
			if (sX>=0 && sX<=src.rows-1 &&
				sY>=0 && sY<=src.cols-1)
			{
				if ( ker.values.at<uchar>(kI,kJ)==255 &&
					 src.at<uchar>(sX,sY)==0)
				{
					dst.at<uchar>(sI,sJ)=0;
					kI = ker.kRows;
					kA=-1;
					break;
				}
			}
		}
	}
	if(kA == 0)
		dst.at<uchar>(sI,sJ)=255;
}

void Erosion( const Mat src, Mat dst, const Kernel ker )
{
	if(ker.values.empty())
	{
		printf("error");
		return;
	}

	for (int sI = 0; sI < src.rows; sI++)
	{
		for (int sJ = 0; sJ < src.cols; sJ++)
		{			
			//erosion
			pixelEro(src, dst, ker, sI, sJ);
		}
	}
}

void Contrary( const Mat src, Mat dst )
{
	for (int sI = 0; sI < src.rows; sI++)
	{
		for (int sJ = 0; sJ < src.cols; sJ++)
		{			
			if ( src.at<uchar>(sI,sJ)==255 )
			{
				dst.at<uchar>(sI,sJ)=0;
			}
			else //src.at<uchar>(sI,sJ)==0
			{
				dst.at<uchar>(sI,sJ)=255;
			}
		}
	}
}

void intersection( const Mat src1, const Mat src2, Mat dst )
{
	for (int sI = 0; sI < src1.rows; sI++)
	{
		for (int sJ = 0; sJ < src1.cols; sJ++)
		{			
			if ( src1.at<uchar>(sI,sJ)==255 &&
		         src2.at<uchar>(sI,sJ)==255)
			{
				dst.at<uchar>(sI,sJ)=255;
			}
			else 
			{
				dst.at<uchar>(sI,sJ)=0;
			}
		}
	}
}

int main()
{
	string imgname = "D:\\course\\CV\\HW\\hw4\\lena.bmp";
 
	Mat img = imread(imgname,0); 
	if(img.empty())
	{
		return -1;
	}

	Mat imgBinary;
	img.copyTo(imgBinary);
	for(int i=0;i<=imgBinary.rows-1;i++)
	{
		for(int j=0;j<=imgBinary.cols-1;j++)
		{
			if(imgBinary.at<uchar>(i,j)<=127)
				imgBinary.at<uchar>(i,j)=0;
			else
				imgBinary.at<uchar>(i,j)=255;
		}
	}

	uchar kValArr[]={0,  255,255,255,0,
					 255,255,255,255,255,
					 255,255,255,255,255,
					 255,255,255,255,255,
					 0,  255,255,255,0  };
	Mat kVal=Mat(5,5,CV_8U,kValArr).clone();
	Kernel ker(5, 5, 2, 2, kVal);

	Mat imgDilation( imgBinary.cols, imgBinary.rows, CV_8U, Scalar(0) );
	Dilation( imgBinary, imgDilation, ker );
	
	Mat imgErosion(imgBinary.cols, imgBinary.rows, CV_8U, Scalar(0) );
	Erosion( imgBinary, imgErosion, ker );
	
	Mat imgOpening(imgBinary.cols, imgBinary.rows, CV_8U, Scalar(0) );
	//Erosion( imgBinary, imgErosion, ker );
	Dilation( imgErosion, imgOpening, ker );

	Mat imgClosing(imgBinary.cols, imgBinary.rows, CV_8U, Scalar(0) );
	//Dilation( imgBinary, imgDilation, ker );
	Erosion( imgDilation, imgClosing, ker );
	
	//hit-and-miss	
	uchar kerHitMissValArr[]={255,255,
						      0,  255};
	Mat kerHitMissVal=Mat(2,2,CV_8U,kerHitMissValArr).clone();
	Kernel kerJ(2, 2, 0, 1, kerHitMissVal);
	Kernel kerK(2, 2, 1, 0, kerHitMissVal);
	Mat imgBinContrary(imgBinary.cols, imgBinary.rows, CV_8U, Scalar(0) );
	imgBinary.copyTo(imgBinContrary);
	Contrary( imgBinary, imgBinContrary );
	Mat imgHitMissEroJ(imgBinary.cols, imgBinary.rows, CV_8U, Scalar(0) );
	Erosion( imgBinary, imgHitMissEroJ, kerJ );
	Mat imgHitMissEroK(imgBinary.cols, imgBinary.rows, CV_8U, Scalar(0) );
	Erosion( imgBinContrary, imgHitMissEroK, kerK );
	Mat imgHitMiss(imgBinary.cols, imgBinary.rows, CV_8U);
	intersection( imgHitMissEroJ, imgHitMissEroK, imgHitMiss );

	namedWindow("img",1); //創建窗口
	namedWindow("binary",1);
	namedWindow("dilation",1);
	namedWindow("erosion",1);
	namedWindow("opening",1);
	namedWindow("closing",1);
	namedWindow("hit-and-miss",1);

	imshow("img", img); //顯示圖
	imshow("binary", imgBinary);
	imshow("dilation", imgDilation);
	imshow("erosion", imgErosion);
	imshow("opening", imgOpening);
	imshow("closing", imgClosing);
	imshow("hit-and-miss", imgHitMiss);

	imwrite("D:\\course\\CV\\HW\\hw4\\imgBinary.bmp",imgBinary);
	imwrite("D:\\course\\CV\\HW\\hw4\\imgDilation.bmp",imgDilation);
	imwrite("D:\\course\\CV\\HW\\hw4\\imgErosion.bmp",imgErosion);
	imwrite("D:\\course\\CV\\HW\\hw4\\imgOpening.bmp",imgOpening);
	imwrite("D:\\course\\CV\\HW\\hw4\\imgClosing.bmp",imgClosing);
	imwrite("D:\\course\\CV\\HW\\hw4\\imgHitMiss.bmp",imgHitMiss);

	waitKey();

	return 0;
}