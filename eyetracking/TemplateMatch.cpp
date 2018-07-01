#include"TemplateMatch.h"
#include"HaarDetectFace.h"

void TemplateMatch::temMatch(IplImage *frameP,Mat Model,DataStruct *detectData)
{
	Mat frame(frameP);
	cvtColor(frame, frameGray, CV_RGB2GRAY);
	//imshow("ģ��ƥ��ʱȫ��ͼ",frameGray);
	//ѡȡ��������
	Rect searchWindow;
	searchWindow.width = detectData->trackArea.width * 1.5;
	searchWindow.height =detectData->trackArea.height * 1.5;
	searchWindow.x = detectData->trackArea.x + detectData->trackArea.width * 0.5 - searchWindow.width * 0.5;
	searchWindow.y = detectData->trackArea.y + detectData->trackArea.height * 0.5 - searchWindow.height * 0.5;
	searchWindow &= Rect(0, 0, frame.cols, frame.rows);

	//ģ��ƥ��
	Mat similarity;
	matchTemplate(frameGray(searchWindow), Model, similarity, CV_TM_CCOEFF_NORMED); 
	//�ҳ����ƥ���λ��
	double maxVal;
	Point maxLoc;
	minMaxLoc(similarity, 0, &maxVal, 0, &maxLoc);
	//imshow("ģ��ƥ��ʱ��ģ��",detectData->trackModel);

	//����ģ����ο�
	detectData->trackArea.x = maxLoc.x + searchWindow.x;
	detectData->trackArea.y = maxLoc.y + searchWindow.y;
	
	//������������
	detectData->faceArea.x = detectData->trackArea.x;
	detectData->faceArea.y = detectData->trackArea.y;
	detectData->faceArea.width = detectData->trackArea.width;
	detectData->faceArea.height = detectData->trackArea.height;
	
	//����ģ��
	Model = frameGray(Rect(detectData->trackArea));
	//imshow("ģ��ƥ����ģ��",detectData->trackModel);
}