#pragma once
#include "DataFormat.h"

class TemplateMatch
{
public :
	Mat frameGray;
	
	void temMatch(IplImage *,Mat,DataStruct *);
};