#include"EyesLocate.h"

void main()
{
	//CvCapture* pCapture = cvCaptureFromCAM(0);
	CvCapture* pCapture = cvCreateCameraCapture(0);
	IplImage *frame;
	EyesLocated *detect = new EyesLocated();
	while (true)
	{
		double start = (double)getTickCount();
		frame = cvQueryFrame(pCapture);
		cvFlip(frame,0,1);
		if (!frame)
			break;
		detect->eyesLocate(frame,detect->detectData,detect->skinDetectArea);
		double end = (double)getTickCount();
		cout <<"\tTime: " << (end - start)*1000 / (getTickFrequency()) <<"ms"<< endl;
		if (cvWaitKey(1)>0)
			break;
	}
	delete detect;
	cvReleaseCapture(&pCapture);
}