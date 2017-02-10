/*
//ÅªMat¤¤ªºdata
{
Mat img;
	for (int j=0;j<result.rows;++j)
	{
		uchar * ori =img.data+j*img.step;
		for(int i=0;i<result.cols;++i)
		{
			(ori+i)[0]=128;
		}
	}

}
*/