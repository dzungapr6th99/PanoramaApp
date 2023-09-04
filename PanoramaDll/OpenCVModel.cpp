#include "OpenCVModel.h"
#include<msclr/marshal.h>
#include<algorithm>
#include "Common.h"
using namespace System::Drawing;
namespace OpenCVClr
{
	static bool CompareEye(cv::Rect e1, cv::Rect e2)
	{
		{
			int x1 = (e1.x - e1.width) * (e1.y * e1.height);
			int x2 = (e2.x - e2.width) * (e2.y * e2.height);
			return true;
		}
	}

	OpenCVModel::OpenCVModel(char* path, char* path_eye)
	{
		{
			//char* path = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Path);
			//char* path_eye = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Path_Eyes);
			Detector = new cv::CascadeClassifier();
			Eye_Detector = new cv::CascadeClassifier();
		
			if (Detector->load(path))
				cout << "Load Detect Face FrontScale Complete" << endl;
			else
				cout << "Load Detect Face FrontScale Fail";
			if (Eye_Detector->load(path_eye))
				cout << "Load Detect Eye Complete"<<endl;
			else
				cout << "Load Detect Eye Fail" << endl;
			cout << "Init Detector at locate: " << Detector << endl;
			cout << "Init Eye Detector locate: " << Eye_Detector << endl;
		
		}
	}

	void OpenCVModel::Detect(char* Base64Array, int Length ,bool Align, System::Collections::Generic::List<int>^% EyeCoordinate)
	{
		vector<cv::Mat> Detect_Faces;
		vector<cv::Rect> Eye_Region;
		//System::Drawing::Rectangle _Rect = System::Drawing::Rectangle(0, 0, BmpImage->Width, BmpImage->Height);
		//BitmapData^ bmpData = BmpImage->LockBits(_Rect, ImageLockMode::ReadWrite, BmpImage->PixelFormat);
		//System::IntPtr data = bmpData->Scan0;
		cv::Mat img; //= cv::imread("D:\\NAVISOFT Project\\face_service-main\\lee_1.jpg");
		//cv::imwrite("ReadPath.jpg", img);
		//char* base64dataraw = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Base64Img);
		vector<uchar> base64data(Base64Array + 0, Base64Array + Length);
		img = cv::imdecode(base64data, IMREAD_COLOR);
		
		vector<cv::Rect> objects;
		cv::Size MaxSize();
		cv::Size MinSize();
		Detector->detectMultiScale(img, objects, 1.1, 10); //Detect Face
		
		for each (cv::Rect var in objects)
		{
			cv::Mat Eye;
			vector<cv::Rect> detectFaceRect;
			cv::Mat Face = img(cv::Range(var.y, var.y + var.height), cv::Range(var.x, var.x + var.width)); // Crop Image
			if (Align)
			{
				vector<cv::Rect> Eye_Align = Align_Face(Face);
				Eye_Region.insert(Eye_Region.end(), Eye_Align.begin(), Eye_Align.end());
				if (Eye_Align.size() > 0)
				{
					EyeCoordinate->Add((Eye_Align[0].x + Eye_Align[0].width) / 2);
					EyeCoordinate->Add((Eye_Align[0].y + Eye_Align[0].height) / 2);
					EyeCoordinate->Add((Eye_Align[1].x + Eye_Align[1].width) / 2);
					EyeCoordinate->Add((Eye_Align[1].y + Eye_Align[1].height) / 2);
				}				 
				//Left_Eye.GetCoordinates((Eye_Align[0].x + Eye_Align[0].width) / 2, (Eye_Align[0].y + Eye_Align[0].height) / 2);
				//Right_Eye.GetCoordinates((Eye_Align[1].x + Eye_Align[1].width) / 2, (Eye_Align[1].y + Eye_Align[1].height) / 2);
			}
			
		}

	}

	vector<cv::Rect> OpenCVModel::Align_Face(cv::Mat Face)
	{
		cv::Mat Face_Gray;
		cvtColor(Face, Face_Gray, cv::COLOR_BGR2GRAY, 0);

		vector<cv::Rect> Eyes;
		cv::Rect Left_Eye;
		cv::Rect Right_Eye;
		
		Eye_Detector->detectMultiScale(Face_Gray, Eyes, 1.1, 10, 0);
		std::sort(Eyes.begin(), Eyes.end(), &CompareEye);
		if (Eyes.size() >= 2)
		{
			if (Eyes[0].x < Eyes[1].x)
			{
				Left_Eye = Eyes[0];
				Right_Eye = Eyes[1];
			}
			else
			{
				Left_Eye = Eyes[1];
				Right_Eye = Eyes[0];
			}

		}
		vector<cv::Rect> Detect_Eyes;
		Detect_Eyes.push_back(Left_Eye);
		Detect_Eyes.push_back(Right_Eye);
		return Detect_Eyes;
		
	}

	


}
