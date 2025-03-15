#include"main.h"
#include <filesystem>
void tcpInit(MyTcpServer& tcp_var, const int port, const char* addr) {
	tcp_var.openServer(port, addr);
}
Prossess::Prossess()
{
}

Prossess::~Prossess()
{
	peopleMonitorRelease();
}

int Prossess::loadParams() {
	//mysqltools.ConnectDatabase();
	//char search_name[2] = "*";
	//char table_name[14] = "MonitorParams";
	//char where_name[3] = "id";
	//char where_value[2] = "1";
	//vector<vector<std::string>>values;
	//mysqltools.search1(search_name, table_name, where_name, where_value, values);
	//cout << "接收到的数据: " << values.size() << " " << values.size()*values[values.size() - 1].size() << endl;
	//if (values.size() > 0) {
	//	if (values[0].size() > 0) {
	//		for (int i = 0; i < 6; i++) {
	//			if (values[0][i * 6+1] != "0") {
	//				CameraParams temp_CameraParams;
	//				temp_CameraParams.address = values[0][i * 6 + 1].c_str();
	//				//cout << "cam" << i + 1 << ": " << values[0][i * 6 + 1] << " ";
	//				temp_CameraParams.username = values[0][i * 6 + 2].c_str();
	//				//cout << values[0][i * 6 + 2] << " ";
	//				temp_CameraParams.port = stoi(values[0][i * 6 + 3]);
	//				//cout << values[0][i * 6 + 3] << " ";
	//				temp_CameraParams.password = values[0][i * 6 + 4].c_str();
	//				temp_CameraParams.windowName = "相机" + std::to_string(i+1);
	//				//cout << values[0][i * 6 + 4] << endl;
	//				camParams.push_back(temp_CameraParams);
	//				WarningRoi temp_warningRoi;
	//				string temp_str = values[0][i * 6 + 5];
	//				string temp_pt = "";
	//				bool flag = false;
	//				for (int n = 0; n < temp_str.size(); n++) {
	//					if (temp_str[n] == '(') {
	//						flag = true;
	//						continue;
	//					}
	//					else if (temp_str[n] == ')') {
	//						_Point mypt;
	//						string temp_value;
	//						for (int m = 0; m < temp_pt.size(); m++) {
	//							if (temp_pt[m] == ',') {
	//								mypt.x = stod(temp_value);
	//								temp_value = "";
	//								continue;
	//							}
	//							else if (m == (temp_pt.size() - 1)) {
	//								temp_value += temp_pt[m];
	//								mypt.y = stod(temp_value);
	//							}
	//							temp_value += temp_pt[m];
	//						}
	//						temp_warningRoi.roi_points.push_back(mypt);
	//						temp_pt = "";
	//						flag = false;
	//						continue;
	//					}
	//					if (flag) {
	//						temp_pt += temp_str[n];
	//					}
	//				}
	//				cout << endl;
	//				temp_warningRoi.warningRoi_id = 0;
	//				warning_roi.push_back(temp_warningRoi);
	//				cout << "警告区域: " << temp_warningRoi.warningRoi_id << endl;
	//				for (int n = 0; n < temp_warningRoi.roi_points.size(); n++) {
	//					cout <<  temp_warningRoi.roi_points[n].x << "," << temp_warningRoi.roi_points[n].y << "\t";
	//				}
	//				cout << endl;
	//				vector<DangerRoi>dangeRois;
	//				temp_str = values[0][i * 6 + 6];
	//				flag = false;
	//				string temp_dangeRoi_str;
	//				cout << "temp_str: " << temp_str << endl;
	//				int id = 1;
	//				for (int k = 0; k < temp_str.size(); k++) {
	//					if (temp_str[k] == '{') {
	//						flag = true;
	//						continue;
	//					}
	//					else if (temp_str[k] == '}') {
	//						temp_pt = "";
	//						DangerRoi temp_dangeRoi;
	//						flag = false;
	//						cout << "temp_dangeRoi_str：" << temp_dangeRoi_str << endl;
	//						for (int n = 0; n < temp_dangeRoi_str.size(); n++) {
	//							if (temp_dangeRoi_str[n] == '(') {
	//								flag = true;
	//								continue;
	//							}
	//							else if (temp_dangeRoi_str[n] == ')') {
	//								_Point mypt;
	//								string temp_value;
	//								for (int m = 0; m < temp_pt.size(); m++) {
	//									if (temp_pt[m] == ',') {
	//										mypt.x = stod(temp_value);
	//										temp_value = "";
	//										continue;
	//									}
	//									else if (m == (temp_pt.size() - 1)) {
	//										temp_value += temp_pt[m];
	//										mypt.y = stod(temp_value);
	//									}
	//									temp_value += temp_pt[m];
	//								}
	//								temp_dangeRoi.roi_points.push_back(mypt);
	//								temp_pt = "";
	//								flag = false;
	//								continue;
	//							}
	//							if (flag) {
	//								temp_pt += temp_dangeRoi_str[n];
	//							}
	//						}
	//						temp_dangeRoi_str = "";
	//						temp_dangeRoi.dangerRoi_id = id;
	//						id++;
	//						dangeRois.push_back(temp_dangeRoi);
	//					}
	//					if (flag == true) {
	//						temp_dangeRoi_str += temp_str[k];
	//					}
	//				}
	//				danger_roi.push_back(dangeRois);
	//				
	//				for (int n = 0; n < dangeRois.size(); n++) {
	//					cout << "危险区域: ";
	//					cout << dangeRois[n].dangerRoi_id << ",";
	//					for (int m = 0; m < dangeRois[n].roi_points.size(); m++) {
	//						cout << dangeRois[n].roi_points[m].x << "," << dangeRois[n].roi_points[m].y << "\t";
	//					}
	//					cout << endl;
	//				}
	//			}
	//		}
	//		is_save = stoi(values[0][5 * 6 + 7]);
	//		if (is_save) { cout << "需要保存图像" << endl; }
	//		else {cout << "不需要保存图像" << endl;}
	//		sleep_time = stoi(values[0][5 * 6 + 8]);
	//		cout << "刷新率: " << sleep_time << endl;
	//		maxQueueSize = stoi(values[0][5 * 6 + 10]);
	//		cout << "队列数量: " << maxQueueSize << endl;
	//	}
	//	else {
	//		return 0;
	//	}
	//}
	//else {
	//	return 0;
	//}		 
	camParams = { 
		{
			"192.168.8.160",
			"admin",
			"jkrobot@",
			8000,
			"camera1"
		},
		{
			"192.168.8.161",
			"admin",
			"jkrobot@",
			8000,
			"camera2"
		}
	};
	WarningRoi temp_warningRoi;
	temp_warningRoi.roi_points = { _Point(205, 130),_Point(1056, 141),_Point(944, 603),_Point(497, 582),_Point(198, 510) };
	warning_roi.push_back(temp_warningRoi);
	temp_warningRoi.roi_points = { _Point(306, 130),_Point(744, 152),_Point(731, 380),_Point(350, 392) };
	warning_roi.push_back(temp_warningRoi);


	DangerRoi temp_dangerRoi;
	vector<DangerRoi>temp_v_dangerRoi;
	temp_dangerRoi.roi_points = { _Point(241, 121),_Point(1004, 157),_Point(1042, 209),_Point(952, 578),_Point(268, 496) };
	temp_v_dangerRoi.push_back(temp_dangerRoi);
	danger_roi.push_back(temp_v_dangerRoi);
	temp_dangerRoi.roi_points = { _Point(443, 195),_Point(722, 264),_Point(729, 424),_Point(401, 402) };
	temp_v_dangerRoi.resize(0);
	temp_v_dangerRoi.push_back(temp_dangerRoi);
	danger_roi.push_back(temp_v_dangerRoi);

	return 0;
}

int Prossess::iniPeopleMonitor() {
	SDK_Init.Init();
	if (SDK_Init.Init() == true)
	{
		cout << "初始化海康相机SDK成功！" << endl;
	}
	else
	{
		cout << "初始化海康相机SDK失败！" << endl;
	}
	//vector<string> windowNames = { "jk1","jk2" };
	cout << "准备配置相机参数..." << endl;
	for (int i = 0; i < camParams.size(); ++i) {
		structdata[i].lUserId = -1;
		structdata[i].UserlRealPlayHandle = -1;
		//cout << "相机" << i + 1 << ": " << camParams[i].address << " " << camParams[i].password << " " << camParams[i].port << " " << camParams[i].username << endl;
		bool Login_OK = camDriver[i].Login(camParams[i].address.c_str(), camParams[i].username.c_str(), camParams[i].password.c_str(), camParams[i].port, (void*)&structdata[i]);
		if (Login_OK)
		{
			cout << "相机" << i + 1 << ": " << camParams[i].address << " " << camParams[i].password << " " << camParams[i].port << " " << camParams[i].username << " " << "配置正确，准备打开预览" << endl;
		}
		else
		{
			cout << "相机" << i + 1 << ": " << camParams[i].address << " " << camParams[i].password << " " << camParams[i].port << " " << camParams[i].username << " " << "无法正确配置相机，请检查相机参数" << endl;
			return 0;
		}
		Sleep(5000); // 暂停一段时间，等待预览开始
		//string windowNames[2] = { "jk1","jk2" };
	}
	cout << "开始初始化行人监控线程..." << endl;
	for (int i = 0; i < camParams.size(); ++i) {
		camThreads[i] = thread(&Prossess::GrabImage, this, std::ref(this->camDriver[i]), i, sleep_time);
		inferThreads[i] = thread(&Prossess::DetectPerson, this, i, camParams[i].windowName, false, sleep_time);
	}
	cout << "初始化完成" << endl;
	return 0;
}

int Prossess::peopleMonitorRelease() {
	return 0;
}

int Prossess::sysIni() {
	
	std::thread t1(tcpInit, std::ref(tcp_s), 6666, "127.0.0.1");
	std::thread t2(tcpInit, std::ref(tcp_shangwei), 8888, "127.0.0.1");
	loadParams();
	monitor.dangerous_result.resize(danger_roi.size());
	monitor.warning_result.resize(warning_roi.size());

	monitor.which_camera.resize(camParams.size());
	monitor.dangerous_grade.resize(camParams.size());
	for (int i = 0; i < danger_roi.size(); i++) {
		monitor.warning_result[i].warning_roi.resize(1);

	}
	for (int i = 0; i < danger_roi.size(); i++) {
		monitor.dangerous_result[i].dangerous_roi.resize(danger_roi[i].size(), 0);

	}
	string model_path = "best.onnx";
	cout << "开始加载模型..." << endl;
	if (InitModel(model_path, true)) {
		cout << "模型加载完毕！" << endl;
	}
	else {
		cout << "加载模型失败，请确认模型路径是否正确！" << endl;
		return 0;
	}
	t2.join();
	t1.join();
	
	//iniSocket();
	return 1;
}


void Prossess::printMonitorData() {
	std::lock_guard<std::mutex> guard(monitor_mutex);
	//if (monitor.dangerous_grade) {
	//	cout << "检测到行人" << endl;
	//	for (int i = 0; i < monitor.which_camera.size(); i++) {
	//		if (monitor.which_camera[i] == 1) {
	//			cout << "相机 " << i + 1;
	//			if (monitor.dangerous_grade == 1) {
	//				cout << " 的警告区域";
	//				cout << "中共出现 " << monitor.warning_result[i].person_num << "个人" << endl;
	//			}
	//			else if (monitor.dangerous_grade == 2) {
	//				cout << " 危险区域编号：";
	//				for (size_t j = 0; j < monitor.dangerous_result[i].dangerous_roi.size(); ++j) {
	//					cout << monitor.dangerous_result[i].dangerous_roi[j] << " ";
	//				}
	//				cout << "中共出现 " << monitor.dangerous_result[i].person_num << "个人" << endl;
	//			}
	//		}
	//	}
	//}
	int grade = 0;
	//int msg_num = 5 + 3 * monitor.which_camera.size();
	//char msg[1024];
	//msg[0] = 0xb2;
	//cout << "num: " << msg_num << endl;
	//msg[1] = msg_num;
	//msg[2] = monitor.which_camera.size();
	for (int i = 0; i < monitor.dangerous_grade.size(); i++) {
		//msg[i * 3 + 3] = monitor.dangerous_grade[i];
		int warning_person_num = 0;
		int dangerous_person_num = 0;
		//int area = 128;
		if (monitor.dangerous_grade[i]) {
			if (monitor.dangerous_grade[i] > grade) {
				grade = monitor.dangerous_grade[i];
			}
			cout << "相机 " << i << " 检测到" << endl;
			if (monitor.dangerous_grade[i] == 1) {
				cout << " 的警告区域";
				cout << "中共出现 " << monitor.warning_result[i].person_num << "个人" << endl;
				warning_person_num += monitor.warning_result[i].person_num;
				//area += 1;
			}
			else if (monitor.dangerous_grade[i] == 2) {
				cout << " 危险区域编号：";
				for (size_t j = 0; j < monitor.dangerous_result[i].dangerous_roi.size(); ++j) {
					cout << monitor.dangerous_result[i].dangerous_roi[j] << " ";
					//area += pow(monitor.dangerous_result[i].dangerous_roi[j] - 1, 2);
				}
				cout << "中共出现 " << monitor.dangerous_result[i].person_num << "个人" << endl;
				dangerous_person_num += monitor.dangerous_result[i].person_num;

			}
		}
		//msg[i * 3 + 4] = area;
		int person_num = warning_person_num + dangerous_person_num;
		std::string rev_str;
		tcp_s.RecvStr(rev_str);
		size_t start = rev_str.find('{');
		size_t end = rev_str.find('}', start + 1);
		std::string result;
		if (start != std::string::npos && end != std::string::npos) {
			// 提取子字符串（跳过 '{'，长度为 end - start - 1）
			result = rev_str.substr(start + 1, end - start - 1);
		}
		cout << result << endl;
		if (person_num == 0 && result == "safe") {
			std::string send_str = "{safe}\0";
			tcp_shangwei.SendStr(send_str);
		}
		else if (dangerous_person_num != 0 || result == "danger") {
			std::string send_str = "{danger}\0";
			tcp_shangwei.SendStr(send_str);
		}
		else {
			std::string send_str = "{warning}\0";
			tcp_shangwei.SendStr(send_str);
		}
		//msg[i * 3 + 5] = person_num;
	}
	//msg[msg_num - 2] = 0x11;
	//msg[msg_num - 1] = 0x01;
	////tcp_s.printHex(msg, 11);
	//tcp_s.SendChar(msg, msg_num);
	////myUdpSrv.sendChar(msg,msg_num);

}

// 假设的计算多边形面积函数
double Prossess::ComputeArea(const vector<_Point>& points)
{
	double area = 0.0;
	int n = points.size();
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		area += points[i].x * points[j].y;
		area -= points[j].x * points[i].y;
	}
	return fabs(area) / 2.0;
}

void Prossess::DrawRegion(Mat& image, vector<_Point>AlarmPoints, vector<DangerRoi> DangerPoints)
{
	Mat mask_img = image.clone();
	// 绘制警告区域
	DrawPolygon(image, AlarmPoints, cv::Scalar(0, 255, 0), true, true);
	addWeighted(image, 0.5, mask_img, 0.5, 0, image);

	// 对危险区域按面积排序
	std::sort(DangerPoints.begin(), DangerPoints.end(), [&](const DangerRoi& a, const DangerRoi& b) {
		return ComputeArea(a.roi_points) > ComputeArea(b.roi_points); // 按面积降序排序
		});
	for (const auto& dangerPoint : DangerPoints) {
		DrawPolygon(image, dangerPoint.roi_points, Scalar(0, 0, 255), true, true);
		addWeighted(image, 0.5, mask_img, 0.5, 0, image);
	}
}

int Prossess::InitModel(string model_path, bool isCuda)//输入模型的路径，以及设置是否开启GPU
{
	for (int i = 0; i < camParams.size(); ++i)
	{
		bool initModel = task_detect_onnx.ReadModel(net[i], model_path, isCuda);
		if (initModel)  // 加载模型，打印是否成功，若使用 GPU 改成 true，若使用 CPU 改成 false
		{
			//std::cout << "net：" << i << "read ok!" << std::endl;
		}
		else
		{
			//std::cout << "net：" << i << "read failed!" << std::endl;
			return 0;
		}
	}
	return 1;
};

void Prossess::GrabImage(HK_camera& camera, int camIndex, int sleepTime) {
	cv::Mat image;
	while (cv::waitKey(1) < 0) {
		camera.grabRGBImage(&image);
	
		if (imageQueue[camIndex].size() >= maxQueueSize) {
			// 如果队列已满，等待一段时间直到队列有空间
			Sleep(10);
			continue;
		}
		unique_lock<mutex> lock(mtx[camIndex]);
		imageQueue[camIndex].push(image);
		lock.unlock();
		Imagecv[camIndex].notify_one();
		Sleep(sleepTime);
	}
}

void Prossess::DetectPerson(int camIndex, const string& windowName, bool saveImage, int sleepTime) {
	Mat mask_img;
	while (true) {
		if (1) {//tcp_s.isConnected() > 0
			unique_lock<mutex> lock(mtx[camIndex]);
			Imagecv[camIndex].wait(lock, [&] { return !imageQueue[camIndex].empty(); });
			cv::Mat img_camera = imageQueue[camIndex].front();

			// 采集数据
			int flag = 1;

			if (flag) {
				string file_name = "E:/pic2/cam" + to_string(camIndex) + "/" + "20250304_" + to_string(camIndex) + to_string(myflag + 1) + ".jpg";
				cv::imwrite(file_name, img_camera);
				myflag++;
				Sleep(2000);
			}
			//if (camIndex == 0) {
			//	string file_name = "datas/left/left" + to_string(left_num)+".png";
			//	cv::imwrite(file_name, img_camera);
			//	left_num++;
			//}
			//else if (camIndex == 1) {
			//	string file_name = "datas/right/right" + to_string(right_num) + ".png";
			//	cv::imwrite(file_name, img_camera);
			//	right_num++;
			//}
			imageQueue[camIndex].pop();
			lock.unlock();

			mask_img = img_camera.clone();
			DrawRegion(mask_img, warning_roi[camIndex].roi_points, danger_roi[camIndex]);
			if (!img_camera.empty()) {
				LARGE_INTEGER t1, t2, tc;
				QueryPerformanceFrequency(&tc);
				QueryPerformanceCounter(&t1);
				
				if (task_detect_onnx.Detect(img_camera, net[camIndex], result[camIndex], conf, iou))
				{
					// 在每次检测开始前清空前次检测结果
					lock_guard<mutex> guard(monitor_mutex);
					monitor.dangerous_result[camIndex].dangerous_roi.clear();
					monitor.warning_result[camIndex].warning_roi.clear();

					task_detect_onnx.DrawPred(mask_img, result[camIndex], warning_roi[camIndex], danger_roi[camIndex], monitor.dangerous_result[camIndex], monitor.warning_result[camIndex]);
					bool hasDangerous = monitor.dangerous_result[camIndex].person_num > 0;
					bool hasWarning = monitor.warning_result[camIndex].person_num > 0;

					if (!hasDangerous && !hasWarning)//若都没有人进入警告区和危险区
					{
						monitor.dangerous_grade[camIndex] = 0;//安全，危险等级为0
						monitor.which_camera[camIndex] = 0;
					}
					else
					{
						//cout << "相机 " << camIndex;
						if (hasDangerous) {//一旦有人进入危险区
							monitor.dangerous_grade[camIndex] = 2; // 停止，危险等级为2
							monitor.which_camera[camIndex] = 1;
						}
						else if (hasWarning) {//有人进入警告区（危险区没有人）
							monitor.dangerous_grade[camIndex] = 1; // 减速，危险等级为1
							monitor.which_camera[camIndex] = 1;
						}
						//monitor_mutex.unlock();  // 修改完成后解锁

						/*if (hasWarning) {
							cout << "，警告人数：" << monitor.warning_result[camIndex].person_num << "，警告区域编号：";
							for (int roi : monitor.warning_result[camIndex].warning_roi) {
								cout << roi << " ";
							}
						}
						if (hasDangerous) {
							cout << "，危险人数：" << monitor.dangerous_result[camIndex].person_num << "，危险区域编号：";
							for (int roi : monitor.dangerous_result[camIndex].dangerous_roi) {
								cout << roi << " ";
							}
						}
						cout << endl;*/

						if (saveImage)//是否开启检测到人进行存图
						{
							time_t rawtime;
							struct tm timeinfo;
							time(&rawtime);
							localtime_s(&timeinfo, &rawtime);

							// 格式化当前时间为字符串
							char buffer[80];
							strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &timeinfo);
							string timestamp(buffer);

							string output_folder = "OutFile";
							//判断保存图片的OutFile目录是否存在，不存在就创建
							if (!CreateDirectoryA(output_folder.c_str(), NULL)) {
								DWORD dwError = GetLastError();
								if (dwError == ERROR_ALREADY_EXISTS) {
									// 目录已经存在，不进行任何操作
								}
								else {
									// 创建目录失败
									cout << "创建目录失败" << endl;
								}
							}
							string outfile = output_folder + "/" + timestamp + ".jpg";
							imwrite(outfile, mask_img);
						}
					}
				}
				else
				{
					lock_guard<mutex> guard(monitor_mutex);
					monitor.dangerous_grade[camIndex] = 0;//安全，危险等级为0
					monitor.which_camera[camIndex] = 0;
					monitor.dangerous_result[camIndex].dangerous_roi.clear();
					monitor.warning_result[camIndex].warning_roi.clear();
				}
				resize(mask_img, mask_img, Size(640, 480));
				QueryPerformanceCounter(&t2);
				double time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
				cout << "time = " << time*1000.0 << endl;  //输出时间（单位：ｓ）
				cv::imshow(windowName, mask_img);
				cv::waitKey(1);
				Sleep(sleepTime);
			}
			else { 
				cout << "image is empty" << endl;
			}
		}
		else {
			Sleep(500);
		}
	}
}

int main() {
	Prossess proseess;
	if (proseess.sysIni()) {
	loop:
		int res = proseess.iniPeopleMonitor();//行人监控初始化
		//int res = 0;
		if (res == 0) {
			while (true) {
				proseess.printMonitorData();//打印行人检测结果
				Sleep(500); 
			}
		}
		else {
			goto loop;
		}
		system("pause");
	}

}

