#include"AsmLocateEyes.h"
#include"HaarDetectFace.h"
#include"SkinPortion.h"
#include"TemplateMatch.h"

class EyesLocated
{
public:
	int frameCount;
	HaarDetectFace *haarDetectFace;
	AsmLocateEyes *asmLocateEyes;
	TemplateMatch *templateMatch;
	SkinP *SkinPortion;
	DataStruct *detectData;
	vector<CvRect> *skinDetectArea;

	EyesLocated()
	{
	   frameCount = -6;
	   haarDetectFace = new HaarDetectFace();
	   asmLocateEyes = new AsmLocateEyes();
	   templateMatch = new TemplateMatch();
	   SkinPortion = new SkinP();
	   detectData = new DataStruct();
	   skinDetectArea = new vector<CvRect>();
	}
	void eyesLocate(IplImage *,DataStruct *,vector<CvRect> *);
	bool getEyesLoction(DataStruct *,CvPoint *, CvPoint *);
	bool getFaceLoction(DataStruct *,Rect *);
};