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
	int faceSquare;	//人脸面积
	CvRect faceArea;	//人脸位置区域 （ASM区域）
	bool faceDetectFlag;	//人脸检测到的标志位，true代表检测到人脸，false代表没有检测到人脸
	CvPoint lEyeLocation, rEyeLocation;	//左右眼的位置
	int skinFlag;  //肤色标志位，skinFlag<6代表摄像区域有人，skinFlag>=6代表摄像区域没有人
	CvRect trackArea;	//下一帧跟踪位置区域
	Mat trackModel;	//跟踪模板
	//CvSize cameraRevolution;	//摄像头分辨率

	DataStruct()
	{
		faceSquare = 0;	 //人脸面积初始化为0
		faceArea = 	cvRect(100,100,50,50);	//人脸区域初始化为(100,100,50,50)
		faceDetectFlag =  false;	 //人脸检测到标志位初始化为false
		lEyeLocation = cvPoint(320,240);	//左眼位置初始化
		rEyeLocation = cvPoint(320,240);	//右眼位置初始化
		skinFlag = 0;						
		trackArea = cvRect(100,100,50,50);	//跟踪区域初始化
		//cameraRevolution = cvSize(640,480);
	}
};