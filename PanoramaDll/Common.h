#pragma once
namespace OpenCVClr
{
	ref class Common
	{
	};
	ref class Point2D
	{
	public:
		int x;
		int y;
		Point2D(int X, int Y);
		~Point2D();
		Point2D();
		void GetCoordinates(int x, int y);
	};

}

