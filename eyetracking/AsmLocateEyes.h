#pragma once
#include "asmfitting.h"
#include "asmlibrary.h"
#include"DataFormat.h"

class AsmLocateEyes
{
public:
	asm_shape detshape;	//ASM匹配的区域 
	asm_shape shape;	//ASM匹配的人脸特征点
	asmfitting asmModel;	//ASM匹配模板

	AsmLocateEyes()	  //构造函数
	{
		if (asmModel.Read("my68-1d.amf") == false)
		{
			std::cout << "ASM特征点模版载入失败,退出!" << std::endl;
		}
		detshape.Resize(2);
		shape.Resize(2);
	}
	void asmFit(IplImage *,CvRect,DataStruct *);
};