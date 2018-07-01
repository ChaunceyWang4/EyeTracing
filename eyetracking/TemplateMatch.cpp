#include"TemplateMatch.h"
#include"HaarDetectFace.h"

void TemplateMatch::temMatch(IplImage *frameP,Mat Model,DataStruct *detectData)
{
	Mat frame(frameP);
	cvtColor(frame, frameGray, CV_RGB2GRAY);
	//imshow("模板匹配时全幅图",frameGray);
	//选取搜索窗口
	Rect searchWindow;
	searchWindow.width = detectData->trackArea.width * 1.5;
	searchWindow.height =detectData->trackArea.height * 1.5;
	searchWindow.x = detectData->trackArea.x + detectData->trackArea.width * 0.5 - searchWindow.width * 0.5;
	searchWindow.y = detectData->trackArea.y + detectData->trackArea.height * 0.5 - searchWindow.height * 0.5;
	searchWindow &= Rect(0, 0, frame.cols, frame.rows);

	//模板匹配
	Mat similarity;
	matchTemplate(frameGray(searchWindow), Model, similarity, CV_TM_CCOEFF_NORMED); 
	//找出最佳匹配的位置
	double maxVal;
	Point maxLoc;
	minMaxLoc(similarity, 0, &maxVal, 0, &maxLoc);
	//imshow("模板匹配时的模板",detectData->trackModel);

	//更新模板矩形框
	detectData->trackArea.x = maxLoc.x + searchWindow.x;
	detectData->trackArea.y = maxLoc.y + searchWindow.y;
	
	//更新人脸区域
	detectData->faceArea.x = detectData->trackArea.x;
	detectData->faceArea.y = detectData->trackArea.y;
	detectData->faceArea.width = detectData->trackArea.width;
	detectData->faceArea.height = detectData->trackArea.height;
	
	//更新模板
	Model = frameGray(Rect(detectData->trackArea));
	//imshow("模板匹配后的模板",detectData->trackModel);
}