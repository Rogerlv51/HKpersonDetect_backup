#pragma once
#pragma once

#include <vector>
#include <iostream>
#include <stack>
#include <cmath>
#include <algorithm> // 使用C++17
#include<opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <numeric>

using namespace std;
using namespace cv;
using namespace cv::dnn;

/// <summary>
/// 点结构体定义
/// </summary>
struct _Point
{
	double x, y;
	_Point(double x, double y) :x(x), y(y) {}
	_Point() :x(0), y(0) {}
};
using PolygonYY = std::vector<_Point>;

#pragma region 分离轴多边形碰撞检测

/// 向量叉乘
double crossProduct(_Point a, _Point b);

/// 向量减法
_Point subtract(_Point a, _Point b);


/// 计算分离轴

std::vector<_Point> getAxes(const PolygonYY& polygon);

/// 多边形投影到分离轴

std::pair<double, double> project(const PolygonYY& polygon, _Point axis);

/// 投影重叠检测

bool overlap(std::pair<double, double> a, std::pair<double, double> b);

/// 凸多边形碰撞检测
bool polygonsIntersect(const PolygonYY& a, const PolygonYY& b);
void DrawPolygon(cv::Mat inputImage, vector<_Point> polygonPoint, const cv::Scalar &color, bool bIsFill, bool bIsClosed);
#pragma endregion


