#include"AsmLocateEyes.h"

void AsmLocateEyes::asmFit(IplImage *frame,CvRect faceArea,DataStruct *detectData)   //ASMº¯Êý
{
	detshape[0].x = (float)faceArea.x;
	detshape[0].y = (float)faceArea.y;
	detshape[1].x = (float)(faceArea.x + faceArea.width);
	detshape[1].y = (float)(faceArea.y + faceArea.height);
		
	InitShapeFromDetBox(shape, detshape, asmModel.GetMappingDetShape(), asmModel.GetMeanFaceWidth());
		
	asmModel.Fitting(shape, frame, 30);
	
	if (sqrt((double)(detectData->lEyeLocation.x - shape[31].x)*(detectData->lEyeLocation.x - shape[31].x) + (detectData->lEyeLocation.y - shape[31].y)*(detectData->lEyeLocation.y - shape[31].y)) > 5) //ÈËÑÛÂË²¨
	{
		detectData->lEyeLocation.x = shape[31].x;
		detectData->lEyeLocation.y = shape[31].y;
	}
	if (sqrt((double)(detectData->rEyeLocation.x - shape[36].x)*(detectData->rEyeLocation.x - shape[36].x) + (detectData->rEyeLocation.y - shape[36].y)*(detectData->rEyeLocation.y - shape[36].y)) > 5) //ÈËÑÛÂË²¨
	{
		detectData->rEyeLocation.x = shape[36].x;
		detectData->rEyeLocation.y = shape[36].y;
	}	
}