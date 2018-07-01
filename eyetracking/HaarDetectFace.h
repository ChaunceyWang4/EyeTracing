#pragma once
#include "DataFormat.h"

class HaarDetectFace
{
public:
	CvHaarClassifierCascade* cascade;	//导入的haar分类器
	char* cascadeName;	//haar分类器文件名
	IplImage *frameYCrCb;	//yCrCb格式的图（3通道）
	IplImage *frameSkinFace;	//肤色检测的图（3通道）
	IplImage *frameSkinContour;	//肤色连通图（1通道）
	Mat frameMatch;		//模板匹配全幅图
	const int Cb ;
	const int Cr;
	const int Y;
	CvMemStorage* memStorage;	//寻找肤色连通域所用的内存
	CvSize cameraRevolution;	//摄像头分辨率
	//*******//
	HaarDetectFace():Cb(2),Cr(1),Y(0),cameraRevolution(cvSize(640,480))	//haar检测的构造函数			 
	{
		cascadeName = "haarcascade_frontalface_alt2.xml";
		cascade = reinterpret_cast<CvHaarClassifierCascade*>(cvLoad(cascadeName, 0, 0, 0));
		if (!cascade)
		{
			fprintf(stderr, "ERROR: Could not load classifier cascade\n");
			fprintf(stderr, "Usage: facedetect --cascade=\"<cascade_path>\" [filename|camera_index]\n");
		}
		frameYCrCb = cvCreateImage(cameraRevolution,8,3);
		frameSkinFace = cvCreateImage(cameraRevolution,8,3);
		frameSkinContour = 	cvCreateImage(cameraRevolution,8,1);
		memStorage =  cvCreateMemStorage(0);
	}

	~HaarDetectFace()
	{
		cvReleaseImage(&frameYCrCb);
		cvReleaseImage(&frameSkinFace);
		cvReleaseImage(&frameSkinContour);
		cvReleaseMemStorage(&memStorage);
	}
	void SkinPart(const IplImage *,vector<CvRect> *);
	void HaarDetect(IplImage *,vector<CvRect> *,DataStruct *);
	float bbOverlap(const CvRect,const CvRect);
};