#pragma once
#include "DataFormat.h"

class HaarDetectFace
{
public:
	CvHaarClassifierCascade* cascade;	//�����haar������
	char* cascadeName;	//haar�������ļ���
	IplImage *frameYCrCb;	//yCrCb��ʽ��ͼ��3ͨ����
	IplImage *frameSkinFace;	//��ɫ����ͼ��3ͨ����
	IplImage *frameSkinContour;	//��ɫ��ͨͼ��1ͨ����
	Mat frameMatch;		//ģ��ƥ��ȫ��ͼ
	const int Cb ;
	const int Cr;
	const int Y;
	CvMemStorage* memStorage;	//Ѱ�ҷ�ɫ��ͨ�����õ��ڴ�
	CvSize cameraRevolution;	//����ͷ�ֱ���
	//*******//
	HaarDetectFace():Cb(2),Cr(1),Y(0),cameraRevolution(cvSize(640,480))	//haar���Ĺ��캯��			 
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