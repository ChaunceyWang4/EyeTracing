#include"SkinPortion.h"

void SkinP::SkinPortion(IplImage *frame,DataStruct *detectData) //计算人脸区域的肤色与非肤色比例，大于1置0，小于1加1
{
	IplImage *frameSrc =  cvCreateImage(cvSize(detectData->faceArea.width,detectData->faceArea.height),8,3);
	IplImage *frameYcrcb =  cvCreateImage(cvSize(detectData->faceArea.width,detectData->faceArea.height),8,3);
	IplImage *frameSkin =  cvCreateImage(cvSize(detectData->faceArea.width,detectData->faceArea.height),8,3);
	IplImage *frameConture =  cvCreateImage(cvSize(detectData->faceArea.width,detectData->faceArea.height),8,1);

	cvSetImageROI(frame, detectData->faceArea);
	cvCopyImage(frame, frameSrc);  //将ROI区域图像复制到img
	cvResetImageROI(frame);  //释放ROI区域

	cvCvtColor(frameSrc, frameYcrcb, CV_BGR2YCrCb);         //BGR空间转换到ycrcb空间
	cvZero(frameSkin);
	for (int h = 0; h < frameSrc->height; ++h)
	{
		unsigned char* psrc = (unsigned char*)frameSrc->imageData + h*frameSrc->widthStep;
		unsigned char* pycrcb = (unsigned char*)frameYcrcb->imageData + h*frameYcrcb->widthStep;
		unsigned char* pdst = (unsigned char*)frameSkin->imageData + h*frameSkin->widthStep;
		for (int w = 0; w < frameSrc->width; ++w)
		{
			if (pycrcb[Cr] >= 140 && pycrcb[Cr] <= 160 && pycrcb[Cb] >= 77 && pycrcb[Cb] <= 127)
			{
				memcpy(pdst, psrc, 3);  //将肤色像素拷贝到_dst
			}
			pycrcb += 3;
			psrc += 3;
			pdst += 3;
		}
	}
	cvCvtColor(frameSkin, frameConture, CV_BGR2GRAY);  //将肤色区域由BGR转化到gray
	cvThreshold(frameConture, frameConture, 1, 255, CV_THRESH_BINARY);  //阈值分割
	cvSmooth(frameConture, frameConture, CV_MEDIAN);  //中值滤波
	cvDilate(frameConture, frameConture, NULL, 5);  //膨胀函数

	float portion, skin = 0, nonskin = 0;
	for (int j = 0; j < frameSrc->width; j++)
	{
		for (int i = 0; i < frameSrc->height; i++)
		{
			if (((uchar *)(frameConture->imageData + i*frameConture->widthStep))[j] > 200)
				skin = skin + 1;
			else
				nonskin = nonskin + 1;
		}
	}
	portion = skin / nonskin;

	if (portion < 1)
		detectData->skinFlag = detectData->skinFlag + 1;
	else
		detectData->skinFlag = 0;
	
	cvReleaseImage(&frameSrc);	
	cvReleaseImage(&frameYcrcb);	
	cvReleaseImage(&frameSkin);	
	cvReleaseImage(&frameConture);	
}