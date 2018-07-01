#pragma once
#include"DataFormat.h"

class SkinP
{
public:
	const int Cb;
	const int Cr;
	const int Y;

	SkinP():Cb(2),Cr(1),Y(1)
	{}
	void SkinPortion(IplImage *,DataStruct *);
};
