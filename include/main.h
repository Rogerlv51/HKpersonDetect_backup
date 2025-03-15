#pragma once
#include<iostream>
#include "HK_camera.h"
#include "yolov8.h"
#include"MyDataTool.h"
//#include"MySqlTools.h"
#include"MyUdpServer.h"
#include "MyTcpServer.h"
#include <Windows.h>
#include <queue>
#include <thread>
#include <mutex>
#include<cmath>
#include <condition_variable>
#include <time.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace mytcp;

#define CamNumber 5 //设置相机的个数，不超过6，这里测试5个

typedef struct Monitor {
	vector<int> dangerous_grade;//0安全	1减速	2停止
	vector <dangerous> dangerous_result;
	vector<warning> warning_result;
	vector<int>which_camera;//是哪个相机触发了
};
struct CameraParams {
	string address;
	string username;
	string password;
	WORD port;
	string windowName;
};
class Prossess
{
public:

	//MyUdpServer myUdpSrv;
	MyTcpServer tcp_s;
	MyTcpServer tcp_shangwei;
	int left_num = 0;
	int right_num = 0;
	int myflag = 0;
	MyDataTool myDataTools;
	//MySqlTools mysqltools;
	vector<CameraParams> camParams;
	HK_camera camDriver[CamNumber];//创建相机类的对象个数
	MyStruct structdata[CamNumber];//创建结构体的个数
	thread camThreads[CamNumber];//相机线程的个数
	thread inferThreads[CamNumber];//处理图像的线程个数，即YOLOv8推理的线程个数
	HK_camera SDK_Init;

	queue<cv::Mat> imageQueue[CamNumber];
	mutex mtx[CamNumber];
	condition_variable Imagecv[CamNumber];
	Monitor monitor;
	std::mutex monitor_mutex;

	vector<Output> result[CamNumber];//每个相机的目标检测结果

	vector<WarningRoi> warning_roi;
	vector<vector<DangerRoi>> danger_roi;

	Yolov8 task_detect_onnx;
	Net net[CamNumber];
	int maxQueueSize = 10;
	float conf = 0.87;
	float iou = 0.5;//设置的置信度和阈值
	int sleep_time = 20;
	bool is_save;
	double ComputeArea(const vector<_Point>& points);

	void DrawRegion(Mat& image, vector<_Point>AlarmPoints, vector<DangerRoi> DangerPoints);
	//输入模型的路径，以及设置是否开启GPU;
	int InitModel(string model_path, bool isCuda);

	void GrabImage(HK_camera& camera, int camIndex, int sleepTime);

	void DetectPerson(int camIndex, const string& windowName, bool saveImage, int sleepTime);

	Prossess();
	~Prossess();
	int loadParams();
	int iniPeopleMonitor();
	int peopleMonitorRelease();
	int sysIni();
	void printMonitorData();
	Net model; // OpenCV DNN模型

private:
};

