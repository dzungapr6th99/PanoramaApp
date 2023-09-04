#pragma once
#include<opencv2/opencv.hpp>
using namespace System::Drawing::Imaging;
using namespace System::Drawing;
namespace PanoramaClr
{
	public ref class Mat2Bmp
	{
	public:
		Mat2Bmp(){}
		static Bitmap^ MatToBitmap(cv::Mat img);
	
	};
}


