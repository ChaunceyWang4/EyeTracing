#pragma once
#include "asmfitting.h"
#include "asmlibrary.h"
#include"DataFormat.h"

class AsmLocateEyes
{
public:
	asm_shape detshape;	//ASMƥ������� 
	asm_shape shape;	//ASMƥ�������������
	asmfitting asmModel;	//ASMƥ��ģ��

	AsmLocateEyes()	  //���캯��
	{
		if (asmModel.Read("my68-1d.amf") == false)
		{
			std::cout << "ASM������ģ������ʧ��,�˳�!" << std::endl;
		}
		detshape.Resize(2);
		shape.Resize(2);
	}
	void asmFit(IplImage *,CvRect,DataStruct *);
};