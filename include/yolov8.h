#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include <numeric>
#include"ColiisionDetector2D.h"

#define YOLO_P6 false 
#define ORT_OLD_VISON 12

struct Output {
	int id;   //结果类别id  
	float confidence;   //结果置信度
	cv::Rect box;       //矩形框
};

typedef struct WarningRoi
{
	int warningRoi_id = 0;
	vector<_Point> roi_points;
};

typedef struct DangerRoi
{
	int dangerRoi_id;
	vector<_Point> roi_points;
};


//一张图获取行人检测获取的结果
/*
	一张图像上危险区域、警告区的人数；
	哪几个Roi区域的编号出现行人；
*/
typedef struct dangerous {
	int person_num;
	vector<int> dangerous_roi;//哪个区域出现，哪个位置就是1，否则为0
};
typedef struct warning {
	int person_num;
	vector<int> warning_roi;//触发的编号
};

class Yolov8 {
public:
	Yolov8() {
	}
	~Yolov8() {}

	bool ReadModel(cv::dnn::Net& net, std::string& netPath, bool isCuda); //该函数用于读onnx模型，net是模型，netPath是模型的地址，设置isCuda的true是GPU来推理,（默认false用CPU来推理）
	bool Detect(cv::Mat& srcImg, cv::dnn::Net& net, std::vector<Output>& output, float _classThreshold, float _nmsThreshold);//该函数用于检测图像，输入srcImg（图像），net（网络），output用于输出结果——结构体OutputSeg包含的内容
	void DrawPred(Mat& img, vector<Output> result, WarningRoi alarmPoints,
		std::vector<DangerRoi> dangerPoints, dangerous& dangerous_result, warning& warning_result);//该函数用于画图，框出图像中的目标，输入img（图像），检测的结果OutputSeg，检测的类别名，画框的颜色。
	void LetterBox(const cv::Mat& image, cv::Mat& outImage,//letterbox操作：在对图片进行resize时，保持原图的长宽比进行等比例缩放,这里设置输入网络的图片统一缩放至640*640的大小。
		cv::Vec4d& params, //[ratio_x,ratio_y,dw,dh]
		const cv::Size& newShape = cv::Size(640, 640),
		bool autoShape = false,
		bool scaleFill = false,
		bool scaleUp = true,
		int stride = 32,
		const cv::Scalar& color = cv::Scalar(114, 114, 114));
	std::vector<std::string> _className = { "person" };//检测目标的类别名，自己的模型需要修改此项


private:
	const int _netWidth = 640;   //ONNX模型输入图片的宽度
	const int _netHeight = 640;  //ONNX图片输入图片的高度

	//float _classThreshold = 0.25;//类别阈值
	//float _nmsThreshold = 0.45;//非极大抑制，用计算IOU筛选目标框


};
