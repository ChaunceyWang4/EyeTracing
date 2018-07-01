// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 在此处引用程序需要的其他头文件
#ifdef _DEBUG 
#pragma comment(lib,"opencv_core2410d.lib")
#pragma comment(lib,"opencv_highgui2410d.lib")
#pragma comment(lib,"opencv_objdetect2410d.lib")
#pragma comment(lib,"opencv_imgproc2410d.lib")
#pragma comment(lib,"asmlibraryD.lib")
#else
#pragma comment(lib,"opencv_core2410.lib")
#pragma comment(lib,"opencv_highgui2410.lib")
#pragma comment(lib,"opencv_objdetect2410.lib")
#pragma comment(lib,"opencv_imgproc2410.lib")
#pragma comment(lib,"asmlibrary.lib")
#endif
