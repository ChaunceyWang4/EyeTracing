#pragma once
#include <vector>
#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace std;
using namespace cv;

class DataStruct
{
public:
	int faceSquare;	//�������
	CvRect faceArea;	//����λ������ ��ASM����
	bool faceDetectFlag;	//������⵽�ı�־λ��true�����⵽������false����û�м�⵽����
	CvPoint lEyeLocation, rEyeLocation;	//�����۵�λ��
	int skinFlag;  //��ɫ��־λ��skinFlag<6���������������ˣ�skinFlag>=6������������û����
	CvRect trackArea;	//��һ֡����λ������
	Mat trackModel;	//����ģ��
	//CvSize cameraRevolution;	//����ͷ�ֱ���

	DataStruct()
	{
		faceSquare = 0;	 //���������ʼ��Ϊ0
		faceArea = 	cvRect(100,100,50,50);	//���������ʼ��Ϊ(100,100,50,50)
		faceDetectFlag =  false;	 //������⵽��־λ��ʼ��Ϊfalse
		lEyeLocation = cvPoint(320,240);	//����λ�ó�ʼ��
		rEyeLocation = cvPoint(320,240);	//����λ�ó�ʼ��
		skinFlag = 0;						
		trackArea = cvRect(100,100,50,50);	//���������ʼ��
		//cameraRevolution = cvSize(640,480);
	}
};