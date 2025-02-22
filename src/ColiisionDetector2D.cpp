#pragma once
#include "ColiisionDetector2D.h"

#pragma region 2D凸包碰撞检测

double crossProduct(_Point a, _Point b)
{
	return a.x * b.y - a.y * b.x;
}

_Point subtract(_Point a, _Point b)
{
	_Point v;
	v.x = a.x - b.x;
	v.y = a.y - b.y;
	return v;
}


std::vector<_Point> getAxes(const PolygonYY& polygon)
{
	std::vector<_Point> axes(polygon.size());
	for (size_t i = 0; i < polygon.size(); ++i) {
		_Point edge = subtract(polygon[i], polygon[(i + 1) % polygon.size()]);
		axes[i] = { -edge.y, edge.x };  // perpendicular to the edge
	}
	return axes;
}

std::pair<double, double> project(const PolygonYY& polygon, _Point axis)
{
	double min = crossProduct(axis, polygon[0]);
	double max = min;
	for (const _Point& p : polygon) {
		double projection = crossProduct(axis, p);
		min = std::min(min, projection);
		max = std::max(max, projection);
	}
	return { min, max };
}

bool overlap(std::pair<double, double> a, std::pair<double, double> b)
{
	return a.first <= b.second && a.second >= b.first;
}

bool polygonsIntersect(const PolygonYY& a, const PolygonYY& b)
{
	std::vector<_Point> axes = getAxes(a);
	for (const _Point& axis : axes) {
		if (!overlap(project(a, axis), project(b, axis))) {
			return false;  // Separating axis found
		}
	}
	axes = getAxes(b);
	for (const _Point& axis : axes) {
		if (!overlap(project(a, axis), project(b, axis))) {
			return false;  // Separating axis found
		}
	}
	return true;  // No separating axis found
}

void DrawPolygon(cv::Mat inputImage, vector<_Point> polygonPoint, const cv::Scalar &color, bool bIsFill, bool bIsClosed = true)
{
	vector<Point> points;
	for (int i = 0; i < polygonPoint.size(); i++)
	{
		int x = polygonPoint[i].x;
		int y = polygonPoint[i].y;
		cv::Point point(x, y);
		points.push_back(point);
	}
	vector<vector<Point>> contours;
	contours.push_back(points);
	if (bIsFill)
		fillPoly(inputImage, contours, color, 8);
	else
		polylines(inputImage, points, bIsClosed, color, 2, 8);
}

#pragma endregion
