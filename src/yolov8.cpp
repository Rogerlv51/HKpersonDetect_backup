#include"yolov8.h"

using namespace std;
using namespace cv;
using namespace cv::dnn;


bool Yolov8::ReadModel(Net& net, string& netPath, bool isCuda = false) {
	try {
		net = readNet(netPath);
#if CV_VERSION_MAJOR==4 &&CV_VERSION_MINOR==7&&CV_VERSION_REVISION==0
		net.enableWinograd(false);  //bug of opencv4.7.x in AVX only platform ,https://github.com/opencv/opencv/pull/23112 and https://github.com/opencv/opencv/issues/23080 
		//net.enableWinograd(true);		//If your CPU supports AVX2, you can set it true to speed up
#endif
	}
	catch (const std::exception&) {
		return false;
	}

	if (isCuda) {
		//cuda
		cout << "推理设备: GPU" << endl;
		net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
		net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA); //or DNN_TARGET_CUDA_FP16
	}
	else {
		//cpu
		cout << "推理设备: CPU" << endl;
		net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
		net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
	}
	return true;
}

void Yolov8::LetterBox(const cv::Mat& image, cv::Mat& outImage, cv::Vec4d& params, const cv::Size& newShape,
	bool autoShape, bool scaleFill, bool scaleUp, int stride, const cv::Scalar& color)
{
	if (false) {
		int maxLen = MAX(image.rows, image.cols);
		outImage = Mat::zeros(Size(maxLen, maxLen), CV_8UC3);
		image.copyTo(outImage(Rect(0, 0, image.cols, image.rows)));
		params[0] = 1;
		params[1] = 1;
		params[3] = 0;
		params[2] = 0;
	}

	cv::Size shape = image.size();
	float r = std::min((float)newShape.height / (float)shape.height,
		(float)newShape.width / (float)shape.width);
	if (!scaleUp)
		r = std::min(r, 1.0f);

	float ratio[2]{ r, r };
	int new_un_pad[2] = { (int)std::round((float)shape.width * r),(int)std::round((float)shape.height * r) };

	auto dw = (float)(newShape.width - new_un_pad[0]);
	auto dh = (float)(newShape.height - new_un_pad[1]);

	if (autoShape)
	{
		dw = (float)((int)dw % stride);
		dh = (float)((int)dh % stride);
	}
	else if (scaleFill)
	{
		dw = 0.0f;
		dh = 0.0f;
		new_un_pad[0] = newShape.width;
		new_un_pad[1] = newShape.height;
		ratio[0] = (float)newShape.width / (float)shape.width;
		ratio[1] = (float)newShape.height / (float)shape.height;
	}

	dw /= 2.0f;
	dh /= 2.0f;

	if (shape.width != new_un_pad[0] && shape.height != new_un_pad[1])
	{
		cv::resize(image, outImage, cv::Size(new_un_pad[0], new_un_pad[1]));
	}
	else {
		outImage = image.clone();
	}

	int top = int(std::round(dh - 0.1f));
	int bottom = int(std::round(dh + 0.1f));
	int left = int(std::round(dw - 0.1f));
	int right = int(std::round(dw + 0.1f));
	params[0] = ratio[0];
	params[1] = ratio[1];
	params[2] = left;
	params[3] = top;
	cv::copyMakeBorder(outImage, outImage, top, bottom, left, right, cv::BORDER_CONSTANT, color);
}


bool Yolov8::Detect(Mat& srcImg, Net& net, vector<Output>& output, float _classThreshold, float _nmsThreshold) {
	Mat blob;
	output.clear();
	int col = srcImg.cols;
	int row = srcImg.rows;
	Mat netInputImg;
	Vec4d params;
	LetterBox(srcImg, netInputImg, params, cv::Size(_netWidth, _netHeight));
	blobFromImage(netInputImg, blob, 1 / 255.0, cv::Size(_netWidth, _netHeight), cv::Scalar(0, 0, 0), true, false);
	//**************************************************************************************************************************************************/
	//如果在其他设置没有问题的情况下但是结果偏差很大，可以尝试下用下面两句语句
	// If there is no problem with other settings, but results are a lot different from  Python-onnx , you can try to use the following two sentences
	// 
	//$ blobFromImage(netInputImg, blob, 1 / 255.0, cv::Size(_netWidth, _netHeight), cv::Scalar(104, 117, 123), true, false);
	//$ blobFromImage(netInputImg, blob, 1 / 255.0, cv::Size(_netWidth, _netHeight), cv::Scalar(114, 114,114), true, false);
	//****************************************************************************************************************************************************/
	net.setInput(blob);
	std::vector<cv::Mat> net_output_img;

	net.forward(net_output_img, net.getUnconnectedOutLayersNames()); //get outputs
	std::vector<int> class_ids;// res-class_id
	std::vector<float> confidences;// res-conf 
	std::vector<cv::Rect> boxes;// res-box
	int net_width = _className.size() + 4;
	Mat output0 = Mat(Size(net_output_img[0].size[2], net_output_img[0].size[1]), CV_32F, (float*)net_output_img[0].data).t();  //[bs,116,8400]=>[bs,8400,116]
	int rows = output0.rows;
	float* pdata = (float*)output0.data;
	for (int r = 0; r < rows; ++r) {
		cv::Mat scores(1, _className.size(), CV_32FC1, pdata + 4);
		Point classIdPoint;
		double max_class_socre;
		minMaxLoc(scores, 0, &max_class_socre, 0, &classIdPoint);
		max_class_socre = (float)max_class_socre;
		if (max_class_socre >= _classThreshold) {
			//rect [x,y,w,h]
			float x = (pdata[0] - params[2]) / params[0];
			float y = (pdata[1] - params[3]) / params[1];
			float w = pdata[2] / params[0];
			float h = pdata[3] / params[1];
			int left = MAX(int(x - 0.5 * w + 0.5), 0);
			int top = MAX(int(y - 0.5 * h + 0.5), 0);
			class_ids.push_back(classIdPoint.x);
			confidences.push_back(max_class_socre);
			boxes.push_back(Rect(left, top, int(w + 0.5), int(h + 0.5)));
		}
		pdata += net_width;//next line
	}
	//NMS
	vector<int> nms_result;
	NMSBoxes(boxes, confidences, _classThreshold, _nmsThreshold, nms_result);
	std::vector<vector<float>> temp_mask_proposals;
	Rect holeImgRect(0, 0, srcImg.cols, srcImg.rows);
	for (int i = 0; i < nms_result.size(); ++i) {
		int idx = nms_result[i];
		Output result;
		result.id = class_ids[idx];
		result.confidence = confidences[idx];
		result.box = boxes[idx] & holeImgRect;
		output.push_back(result);
	}
	if (output.size())
		return true;
	else
		return false;
}

//判断行人是否进入特定区域：一个警告区(roi_id=1)，多个危险区(roi_id=2、3、4...)
void Yolov8::DrawPred(Mat& img, vector<Output> result, WarningRoi alarmPoints,
	std::vector<DangerRoi> dangerPoints, dangerous& dangerous_result, warning& warning_result) {
	int alarmperson = 0;
	int dangerperson = 0;
	int danger_roi_number = dangerPoints.size();//计算图像上多少个危险区

	dangerous_result.dangerous_roi.clear();
	//对每一个检测的目标框进行判断是否进入特定区域，并画框显示
	for (int i = 0; i < result.size(); i++) {
		double x, y, xw, yh;
		x = result[i].box.x;
		y = result[i].box.y;
		xw = result[i].box.x + result[i].box.width;
		yh = result[i].box.y + result[i].box.height;

		std::vector<_Point> RawRect1Points
		{
			{ x, y },
			{ x + xw, y },
			{ x + xw,  y + yh},
			{ x,  y + yh }
		};

		vector<bool> collision_danger(danger_roi_number, false);//初始化危险区域的判断，默认false,未进入危险区
		bool collision_alarm = polygonsIntersect(alarmPoints.roi_points, RawRect1Points);// 根据目标检测框与警告区域是否相交判断目标是否进入警告区
		// 检查是否有任何一个危险区与目标框相交
		bool any_danger_collision = false;
		int dangeroi;


		if (collision_alarm)//如果目标进入警告区，画绿色框
		{

			//判断目标是否进入危险区，从最内的框开始算
			for (int j = 0; j < danger_roi_number; ++j) {
				collision_danger[j] = polygonsIntersect(dangerPoints[j].roi_points, RawRect1Points);
				if (collision_danger[j]) {
					any_danger_collision = true;
					dangeroi = dangerPoints[j].dangerRoi_id;
					dangerous_result.dangerous_roi.push_back(dangeroi);//在危险区，输出危险区的roi编号；
					break;
				}
			}
			if (any_danger_collision)//如果目标进入任意一个危险区，画红色框
			{
				dangerperson = dangerperson + 1;
				rectangle(img, result[i].box, Scalar(0, 0, 255), 2, 8);
				string label = "person:" + to_string(result[i].confidence);
				int baseLine;
				Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
				result[i].box.y = max(result[i].box.y, labelSize.height);
				putText(img, label, Point(result[i].box.x, result[i].box.y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1);
			}
			else
			{
				alarmperson = alarmperson + 1;
				rectangle(img, result[i].box, Scalar(0, 255, 0), 2, 8);
				string label = "person:" + to_string(result[i].confidence);
				int baseLine;
				Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
				result[i].box.y = max(result[i].box.y, labelSize.height);
				putText(img, label, Point(result[i].box.x, result[i].box.y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
			}
		}
	}
	dangerous_result.person_num = dangerperson;
	warning_result.person_num = alarmperson;
	if (alarmperson > 0)
	{
		warning_result.warning_roi.push_back(alarmPoints.warningRoi_id);
	}

}