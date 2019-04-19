#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

std::vector<Rect> face_rects;
string face_cascade_name = "haarcascade_frontalface_alt2.xml";
//该文件存在于OpenCV安装目录下的\sources\data\haarcascades内，需复制到当前工程目录下
CascadeClassifier face_cascade;
void detectAndDisplay(Mat & frame, String fname);

int main(int argc, char** argv)
{
	if (!face_cascade.load(face_cascade_name)) {
		cout << "错误，可能原因未找到haarcascade_frontalface_alt2.xml，请拷贝该文件到exe程序同目录下！\n" << endl;
		return -1;
	}

	//---------------------------------检测jpg格式图片---------------------------------
	string pattern = "photos/*.jpg";  //设置照片目录
	vector<String> photo_names;
	glob(pattern, photo_names, false);
	size_t count = photo_names.size();

	cout << "正在提取jpg格式照片：" << endl;
	Mat image;
	for (int i = 0; i < count; i++)
	{
		cout << i + 1 << "/" << count << endl;
		image = imread(photo_names[i]);
		if (image.empty())
		{
			cout << "图片错误！" << endl;
			return 1;
		}
		/*namedWindow("原始照片", WINDOW_AUTOSIZE);
		imshow("原始照片", image);
		waitKey(100);
		detectAndDisplay(image, photo_names[i]);*/
	}
	//destroyAllWindows();
	string pattern1 = "photos/*.JPG";  //设置照片目录
	vector<String> photo_names1;
	glob(pattern1, photo_names1, false);
	count = photo_names1.size();
	cout << "正在提取JPG格式照片：" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << i + 1 << "/" << count << endl;
		image = imread(photo_names1[i]);
		if (image.empty())
		{
			cout << "图片错误！" << endl;
			return 1;
		}
		/*namedWindow("原始照片", WINDOW_AUTOSIZE);
		imshow("原始照片", image);
		waitKey(100);
		detectAndDisplay(image, photo_names[i]);*/
	}

	//---------------------------------检测png格式图片---------------------------------
	string pattern2 = "photos/*.png";  //设置照片目录
	vector<String> photo_names2;
	glob(pattern2, photo_names2, false);
	count = photo_names2.size();
	cout << "正在提取png格式照片：" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << i + 1 << "/" << count << endl;
		image = imread(photo_names2[i]);
		if (image.empty())
		{
			cout << "图片错误！" << endl;
			return 1;
		}
		/*namedWindow("原始照片", WINDOW_AUTOSIZE);
		imshow("原始照片", image);
		waitKey(100);
		detectAndDisplay(image, photo_names[i]);*/
	}

	//---------------------------------检测jpeg格式图片---------------------------------
	string pattern3 = "photos/*.jpeg";  //设置照片目录
	vector<String> photo_names3;
	glob(pattern3, photo_names3, false);
	count = photo_names3.size();
	cout << "正在提取jpeg格式照片：" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << i + 1 << "/" << count << endl;
		image = imread(photo_names3[i]);
		if (image.empty())
		{
			cout << "图片错误！" << endl;
			return 1;
		}
		/*namedWindow("原始照片", WINDOW_AUTOSIZE);
		imshow("原始照片", image);
		waitKey(100);
		detectAndDisplay(image, photo_names[i]);*/
	}

	return 0;
}

void detectAndDisplay(Mat & face, String fname)
{
	Mat face_gray;
	cvtColor(face, face_gray, CV_BGR2GRAY);  //rgb类型转换为灰度类型
	equalizeHist(face_gray, face_gray);  //直方图均衡化
	face_cascade.detectMultiScale(face_gray, face_rects, 1.1, 6, CV_HAAR_DO_CANNY_PRUNING, Size(50, 50));  //找出人脸

	Mat raw_face;
	Mat resized_face;
	string str_old_name = fname;

	if (face_rects.size() == 1)
	{
		raw_face = face(face_rects[0]);
		/*if (raw_face.cols > 100)
		{*/
		resize(raw_face, resized_face, Size(200, 200)); //调整保存的脸部图片大小
		//cout << saved_name << endl;
		/*namedWindow("脸部图片", WINDOW_AUTOSIZE);
		imshow("脸部图片", resized_face);*/
		imwrite(str_old_name.replace(0, 6, "faces"), resized_face);
		/*waitKey(100);
		destroyWindow("脸部图片");*/
		/*}*/
	}
	else if (face_rects.size() > 1)
	{
		string temp = str_old_name.replace(0, 6, "faces");
		string new_name = temp.replace(temp.size() - 4, 4, "_");
		for (size_t j = 0; j < face_rects.size(); j++)
		{
			raw_face = face(face_rects[j]);
			/*if (raw_face.cols > 100)  //检测脸部图片是否符合要求
			{*/
			resize(raw_face, resized_face, Size(200, 200)); //调整保存的脸部图片大小
			//cout << saved_name << endl;
			/*namedWindow("脸部图片", WINDOW_AUTOSIZE);
			imshow("脸部图片", resized_face);*/
			imwrite(new_name + to_string(j) + string(".jpg"), resized_face);
			/*waitKey(100);*/
			//}
		}
		//destroyWindow("脸部图片");
	}
	else
	{
		//namedWindow("失败图片", WINDOW_NORMAL);
		//imshow("失败图片", face);
		//waitKey(500);
		cout << "提取面部图片失败：" << str_old_name;
		imwrite(str_old_name.replace(0, 6, "failed"), face);
	}
}