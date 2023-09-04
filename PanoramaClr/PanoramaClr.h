#pragma once
#include <opencv2/opencv.hpp>
#include "Mat2Bmp.h"
using namespace System;
using namespace cv;
using namespace System::Collections::Generic;
using namespace System::Drawing;

namespace PanoramaClr
{
	public ref class Panorama
	{
	public:
		Panorama()
		{
			
		}
		static Bitmap^ MergeImage(List<System::String^>^ ListPath, System::String^ SavePath);
	private:
		static Mat2Bmp DataConvert;


	};
	class ParallelMandelbrot : public cv::ParallelLoopBody
	{
	public:
		ParallelMandelbrot(cv::Mat& TransformedImage, cv::Mat& InitialImage, std::vector<int> ti_x, std::vector<int> ti_y, std::vector<int> ii_tl_x, std::vector<int> ii_tl_y, std::vector<float> weight_tl, std::vector<float> weight_tr, std::vector<float> weight_bl, std::vector<float> weight_br)
			: TransformedImage(TransformedImage), InitialImage(InitialImage), ti_x(ti_x), ti_y(ti_y), ii_tl_x(ii_tl_x), ii_tl_y(ii_tl_y), weight_tl(weight_tl), weight_tr(weight_tr), weight_bl(weight_bl), weight_br(weight_br)
		{
		}
		virtual void operator ()(const cv::Range& range) const CV_OVERRIDE
		{
			for (int i = range.start; i < range.end; i++)
			{

				cv::Vec3b& TransformedImage_intensity = TransformedImage.at<cv::Vec3b>(ti_y[i], ti_x[i]);
				cv::Vec3b& InitialImage_intensity_tl = InitialImage.at<cv::Vec3b>(ii_tl_y[i], ii_tl_x[i]);
				cv::Vec3b& InitialImage_intensity_tr = InitialImage.at<cv::Vec3b>(ii_tl_y[i], ii_tl_x[i] + 1);
				cv::Vec3b& InitialImage_intensity_bl = InitialImage.at<cv::Vec3b>(ii_tl_y[i] + 1, ii_tl_x[i]);
				cv::Vec3b& InitialImage_intensity_br = InitialImage.at<cv::Vec3b>(ii_tl_y[i] + 1, ii_tl_x[i] + 1);

				for (int k = 0; k < InitialImage.channels(); k++)
				{
					TransformedImage_intensity.val[k] = (weight_tl[i] * InitialImage_intensity_tl.val[k]) +
						(weight_tr[i] * InitialImage_intensity_tr.val[k]) +
						(weight_bl[i] * InitialImage_intensity_bl.val[k]) +
						(weight_br[i] * InitialImage_intensity_br.val[k]);
				}
			}
		}
		ParallelMandelbrot& operator=(const ParallelMandelbrot&) {
			return *this;
		};
	private:
		cv::Mat& TransformedImage;
		cv::Mat& InitialImage;
		std::vector<int> ti_x;
		std::vector<int> ti_y;
		std::vector<int> ii_tl_x;
		std::vector<int> ii_tl_y;
		std::vector<float> weight_tl;
		std::vector<float> weight_tr;
		std::vector<float> weight_bl;
		std::vector<float> weight_br;
	};
}
