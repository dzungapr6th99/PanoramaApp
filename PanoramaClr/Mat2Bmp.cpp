#include "pch.h"
#include "Mat2Bmp.h"
using namespace System::Runtime::InteropServices;
using namespace System;
namespace PanoramaClr
{
	typedef unsigned char byte;
	Bitmap^ Mat2Bmp::MatToBitmap(cv::Mat img)
	{
		if (img.data == nullptr)
			return nullptr;
		if (img.type() != CV_8UC3 && img.type() != CV_8UC4)
		{
			throw gcnew NotSupportedException("Only images of type CV_8UC3 are supported for conversion to Bitmap");
		}

		//create the bitmap and get the pointer to the data
		Bitmap^ bmpimg = gcnew Bitmap(img.cols, img.rows, PixelFormat::Format24bppRgb);

		BitmapData^ data;
		if (img.type() == CV_8UC3)
			data = bmpimg->LockBits(System::Drawing::Rectangle(0, 0, img.cols, img.rows), ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);
		else if (img.type() == CV_8UC4)
			data = bmpimg->LockBits(System::Drawing::Rectangle(0, 0, img.cols, img.rows), ImageLockMode::WriteOnly, PixelFormat::Format32bppRgb);

		byte* dstData = reinterpret_cast<byte*>(data->Scan0.ToPointer());

		unsigned char* srcData = img.data;

		for (int row = 0; row < data->Height; ++row)
		{
			memcpy(reinterpret_cast<void*>(&dstData[row * data->Stride]), reinterpret_cast<void*>(&srcData[row * img.step]), img.cols * img.channels());
		}

		bmpimg->UnlockBits(data);
		delete(data);
		img.release();
		return bmpimg;
	}


	
}