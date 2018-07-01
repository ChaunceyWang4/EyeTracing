#include"EyesLocate.h"

void EyesLocated::eyesLocate(IplImage *frame,DataStruct *detectData,vector<CvRect> *skinDetectArea)
{
    if(frameCount < 0)
	{
		haarDetectFace->SkinPart(frame,skinDetectArea);
		haarDetectFace->HaarDetect(frame,skinDetectArea,detectData);
		if(detectData->faceDetectFlag == false)
		{
			cvShowImage("Face",frame);
			return;
		}
		else
			frameCount++;
	}
	else if(frameCount >= 0 && frameCount < 8)
	{
		templateMatch->temMatch(frame,detectData->trackModel,detectData);
		frameCount++;
	}
	else 
	{
		frameCount = 0;
		haarDetectFace->SkinPart(frame,skinDetectArea);
		haarDetectFace->HaarDetect(frame,skinDetectArea,detectData);
		if(detectData->faceDetectFlag == false)
		{
			templateMatch->temMatch(frame,detectData->trackModel,detectData);
			frameCount++;
		}	
	}
		
	asmLocateEyes->asmFit(frame,detectData->faceArea,detectData);
	SkinPortion->SkinPortion(frame,detectData);

	if(detectData->skinFlag < 6)
	{
		//在摄像头画面上画人脸框、人眼
		cvRectangle(frame, cvPoint(detectData->faceArea.x, detectData->faceArea.y), cvPoint(detectData->faceArea.x + detectData->faceArea.width, detectData->faceArea.y + detectData->faceArea.height),
		cvScalar(255, 0, 0), 3);
		cvCircle(frame, detectData->lEyeLocation, 5, cvScalar(0, 0, 255), 1, 8, 0);
		cvCircle(frame, detectData->rEyeLocation, 5, cvScalar(0, 0, 255), 1, 8, 0);
		cvShowImage("Face",frame);
	}
	else
	{
		frameCount = -6;
		//直接显示摄像头画面
		cvShowImage("Face",frame);
	}

	detectData->faceSquare = 0;
	detectData->faceDetectFlag = false;
}
bool getEyesLoction(DataStruct *detectData,CvPoint &Qt_L_eye, CvPoint &Qt_R_eye)
{
	if(detectData->skinFlag < 6)
	{
		Qt_L_eye.x = detectData->lEyeLocation.x;
		Qt_L_eye.y = detectData->lEyeLocation.y;
		Qt_R_eye.x = detectData->rEyeLocation.x;
		Qt_R_eye.y = detectData->rEyeLocation.y;
		return true;
	}
	else 
		return false;
}	
bool getFaceLoction(DataStruct *detectData,Rect &Qt_ASM_box)
{
	if(detectData->skinFlag < 6)
	{
		Qt_ASM_box.x = detectData->faceArea.x;
		Qt_ASM_box.y = detectData->faceArea.y;
		Qt_ASM_box.width = detectData->faceArea.width;
		Qt_ASM_box.height = detectData->faceArea.height;
		return true;
	}
	else 
		return false;
}
