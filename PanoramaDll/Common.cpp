#include "Common.h"
namespace OpenCVClr
{
	Point2D::Point2D(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	Point2D::Point2D()
	{
		x = 0;
		y = 0;
	}
	Point2D::~Point2D()
	{

	}

	void Point2D::GetCoordinates(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
}