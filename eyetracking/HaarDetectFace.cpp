#include"HaarDetectFace.h"

void HaarDetectFace::SkinPart(const IplImage *frame,vector<CvRect> *skinDetectArea)
{
	skinDetectArea->clear();
	cvCvtColor(frame, frameYCrCb, CV_BGR2YCrCb);         //BGR空间转换到ycrcb空间
	cvZero(frameSkinFace);
	for (int h = 0; h < frame->height; ++h)
	{
		unsigned char* psrc = (unsigned char*)frame->imageData + h*frame->widthStep;
		unsigned char* pycrcb = (unsigned char*)frameYCrCb->imageData + h*frameYCrCb->widthStep;
		unsigned char* pdst = (unsigned char*)frameSkinFace->imageData + h*frameSkinFace->widthStep;
		for (int w = 0; w < frame->width; ++w)
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
	cvCvtColor(frameSkinFace, frameSkinContour, CV_BGR2GRAY);  //将肤色区域由BGR转化到gray
	cvThreshold(frameSkinContour, frameSkinContour, 1, 255, CV_THRESH_BINARY);  //阈值分割
	cvSmooth(frameSkinContour, frameSkinContour, CV_MEDIAN);  //中值滤波
	cvDilate(frameSkinContour, frameSkinContour, NULL, 5);  //膨胀函数

	CvSeq *firstContour = NULL;
	cvFindContours(   //找连通区域      cvFindContours从二值图像中检索轮廓，并返回检测到的轮廓的个数
		frameSkinContour,
		memStorage,
		&firstContour,
		sizeof(CvContour),
		CV_RETR_TREE
		);
	cvClearMemStorage(memStorage);
	for (; firstContour; firstContour = firstContour->h_next) 
	{
		CvRect r = ((CvContour*)firstContour)->rect;
		skinDetectArea->push_back(r);
	}
}
void HaarDetectFace::HaarDetect(IplImage *frame,vector<CvRect> *skinDetectArea,DataStruct *detectData)
{
   for(vector<CvRect>::iterator iter=skinDetectArea->begin();iter!=skinDetectArea->end();iter++)  //寻找最大人脸框
	{
		CvRect r = *iter;
		if (r.height >= 60 && r.width >= 60 && (double)r.height / cameraRevolution.height >= 1.0 / 10 && (double)r.width / cameraRevolution.width >= 1.0 / 8
			&& ((r.height >= r.width && (double)r.height / r.width <= 2.0) || (r.height <= r.width && (double)r.width / r.height <= 2.0)))
			//图片大小(注意数据类型转换)
		{
			if (r.x - r.width / 10 >= 5)    //适当将人脸框扩大，提高检测精度
				r.x = r.x - r.width / 10;
			if (r.y - r.height / 10 >= 5)
				r.y = r.y - r.height / 10;
			if (r.x + r.width + r.width / 5 <= cameraRevolution.width - 5)
				r.width = r.width + r.width / 5;
			if (r.y + r.height + r.height / 5 <= cameraRevolution.height - 5)
				r.height = r.height + r.height / 5;
			cvSetImageROI(frame, r);  //设定ROI区域

			IplImage *frameHaar =  cvCreateImage(cvSize(r.width,r.height),8,3);
			IplImage *frameHaarGray =  cvCreateImage(cvSize(r.width,r.height),8,1);

			cvCopyImage(frame, frameHaar);  //将ROI区域图像复制到img
			cvResetImageROI(frame);  //释放ROI区域

			cvCvtColor(frameHaar, frameHaarGray, CV_BGR2GRAY);
			cvEqualizeHist(frameHaarGray, frameHaarGray);
			cvClearMemStorage(memStorage);
			if (cascade)
			{
				CvSeq* faces = cvHaarDetectObjects(frameHaarGray, cascade, memStorage, 1.1, 3, 1, cvSize(30, 30));
				if (faces->total != 0)  //如果检测到人脸
				{
					CvRect* r1 = (CvRect*)cvGetSeqElem(faces, 0);  //获取人脸框信息
					int S1 = r1->height*r1->width;  //人脸大小
					if (S1 >= detectData->faceSquare && (double)S1 / (r.height*r.width) >= 1.0 / 4)
						//将检测到的人脸框大小与最大人脸框相比较，如果面积大，则更新人脸框结构体
					{
						detectData->faceDetectFlag = true;
						detectData->faceSquare = S1;
						detectData->faceArea.height = r1->height;
						detectData->faceArea.width = r1->width;
						detectData->faceArea.x = r1->x + r.x;
						detectData->faceArea.y = r1->y + r.y;
					}
				}
			}
			cvReleaseImage(&frameHaar);
			cvReleaseImage(&frameHaarGray);
		}
	}
	float portion = bbOverlap(detectData->faceArea,detectData->trackArea);
	//cout<<portion<<endl;
	if (portion > 0.8)
	{
		detectData->faceArea.x = detectData->trackArea.x;  //将检测到的最大人脸框位置传给ASM搜索框
		detectData->faceArea.y = detectData->trackArea.y;
		detectData->faceArea.width = detectData->trackArea.width;
		detectData->faceArea.height = detectData->trackArea.height;
	}
	if(detectData->faceDetectFlag == true)
	{
		detectData->skinFlag = 0;
		detectData->trackArea.x = detectData->faceArea.x;
		detectData->trackArea.y = detectData->faceArea.y;
		detectData->trackArea.height = detectData->faceArea.height;
		detectData->trackArea.width = detectData->faceArea.width;
		Mat gray(frame);
		cvtColor(gray, frameMatch, CV_RGB2GRAY);
		detectData->trackModel =  frameMatch(detectData->trackArea);
		//imshow("人脸检测到的跟踪模板",detectData->trackModel);
	}
}
float HaarDetectFace::bbOverlap(const CvRect box1,const CvRect box2)
{
    if (box1.x > box2.x+box2.width) { return 0.0; }  
	if (box1.y > box2.y+box2.height) { return 0.0; }  
	if (box1.x+box1.width < box2.x) { return 0.0; }  
	if (box1.y+box1.height < box2.y) { return 0.0; }  
	float colInt =  min(box1.x+box1.width,box2.x+box2.width) - max(box1.x, box2.x);  
	float rowInt =  min(box1.y+box1.height,box2.y+box2.height) - max(box1.y,box2.y);  
	float intersection = colInt * rowInt;  
	float area1 = box1.width*box1.height;  
	float area2 = box2.width*box2.height;  
	return intersection / (area1 + area2 - intersection);  
}