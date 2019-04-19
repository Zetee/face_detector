#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

std::vector<Rect> face_rects;
string face_cascade_name = "haarcascade_frontalface_alt2.xml";
//���ļ�������OpenCV��װĿ¼�µ�\sources\data\haarcascades�ڣ��踴�Ƶ���ǰ����Ŀ¼��
CascadeClassifier face_cascade;
void detectAndDisplay(Mat & frame, String fname);

int main(int argc, char** argv)
{
	if (!face_cascade.load(face_cascade_name)) {
		cout << "���󣬿���ԭ��δ�ҵ�haarcascade_frontalface_alt2.xml���뿽�����ļ���exe����ͬĿ¼�£�\n" << endl;
		return -1;
	}

	//---------------------------------���jpg��ʽͼƬ---------------------------------
	string pattern = "photos/*.jpg";  //������ƬĿ¼
	vector<String> photo_names;
	glob(pattern, photo_names, false);
	size_t count = photo_names.size();

	cout << "������ȡjpg��ʽ��Ƭ��" << endl;
	Mat image;
	for (int i = 0; i < count; i++)
	{
		cout << i + 1 << "/" << count << endl;
		image = imread(photo_names[i]);
		if (image.empty())
		{
			cout << "ͼƬ����" << endl;
			return 1;
		}
		/*namedWindow("ԭʼ��Ƭ", WINDOW_AUTOSIZE);
		imshow("ԭʼ��Ƭ", image);
		waitKey(100);
		detectAndDisplay(image, photo_names[i]);*/
	}
	//destroyAllWindows();
	string pattern1 = "photos/*.JPG";  //������ƬĿ¼
	vector<String> photo_names1;
	glob(pattern1, photo_names1, false);
	count = photo_names1.size();
	cout << "������ȡJPG��ʽ��Ƭ��" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << i + 1 << "/" << count << endl;
		image = imread(photo_names1[i]);
		if (image.empty())
		{
			cout << "ͼƬ����" << endl;
			return 1;
		}
		/*namedWindow("ԭʼ��Ƭ", WINDOW_AUTOSIZE);
		imshow("ԭʼ��Ƭ", image);
		waitKey(100);
		detectAndDisplay(image, photo_names[i]);*/
	}

	//---------------------------------���png��ʽͼƬ---------------------------------
	string pattern2 = "photos/*.png";  //������ƬĿ¼
	vector<String> photo_names2;
	glob(pattern2, photo_names2, false);
	count = photo_names2.size();
	cout << "������ȡpng��ʽ��Ƭ��" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << i + 1 << "/" << count << endl;
		image = imread(photo_names2[i]);
		if (image.empty())
		{
			cout << "ͼƬ����" << endl;
			return 1;
		}
		/*namedWindow("ԭʼ��Ƭ", WINDOW_AUTOSIZE);
		imshow("ԭʼ��Ƭ", image);
		waitKey(100);
		detectAndDisplay(image, photo_names[i]);*/
	}

	//---------------------------------���jpeg��ʽͼƬ---------------------------------
	string pattern3 = "photos/*.jpeg";  //������ƬĿ¼
	vector<String> photo_names3;
	glob(pattern3, photo_names3, false);
	count = photo_names3.size();
	cout << "������ȡjpeg��ʽ��Ƭ��" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << i + 1 << "/" << count << endl;
		image = imread(photo_names3[i]);
		if (image.empty())
		{
			cout << "ͼƬ����" << endl;
			return 1;
		}
		/*namedWindow("ԭʼ��Ƭ", WINDOW_AUTOSIZE);
		imshow("ԭʼ��Ƭ", image);
		waitKey(100);
		detectAndDisplay(image, photo_names[i]);*/
	}

	return 0;
}

void detectAndDisplay(Mat & face, String fname)
{
	Mat face_gray;
	cvtColor(face, face_gray, CV_BGR2GRAY);  //rgb����ת��Ϊ�Ҷ�����
	equalizeHist(face_gray, face_gray);  //ֱ��ͼ���⻯
	face_cascade.detectMultiScale(face_gray, face_rects, 1.1, 6, CV_HAAR_DO_CANNY_PRUNING, Size(50, 50));  //�ҳ�����

	Mat raw_face;
	Mat resized_face;
	string str_old_name = fname;

	if (face_rects.size() == 1)
	{
		raw_face = face(face_rects[0]);
		/*if (raw_face.cols > 100)
		{*/
		resize(raw_face, resized_face, Size(200, 200)); //�������������ͼƬ��С
		//cout << saved_name << endl;
		/*namedWindow("����ͼƬ", WINDOW_AUTOSIZE);
		imshow("����ͼƬ", resized_face);*/
		imwrite(str_old_name.replace(0, 6, "faces"), resized_face);
		/*waitKey(100);
		destroyWindow("����ͼƬ");*/
		/*}*/
	}
	else if (face_rects.size() > 1)
	{
		string temp = str_old_name.replace(0, 6, "faces");
		string new_name = temp.replace(temp.size() - 4, 4, "_");
		for (size_t j = 0; j < face_rects.size(); j++)
		{
			raw_face = face(face_rects[j]);
			/*if (raw_face.cols > 100)  //�������ͼƬ�Ƿ����Ҫ��
			{*/
			resize(raw_face, resized_face, Size(200, 200)); //�������������ͼƬ��С
			//cout << saved_name << endl;
			/*namedWindow("����ͼƬ", WINDOW_AUTOSIZE);
			imshow("����ͼƬ", resized_face);*/
			imwrite(new_name + to_string(j) + string(".jpg"), resized_face);
			/*waitKey(100);*/
			//}
		}
		//destroyWindow("����ͼƬ");
	}
	else
	{
		//namedWindow("ʧ��ͼƬ", WINDOW_NORMAL);
		//imshow("ʧ��ͼƬ", face);
		//waitKey(500);
		cout << "��ȡ�沿ͼƬʧ�ܣ�" << str_old_name;
		imwrite(str_old_name.replace(0, 6, "failed"), face);
	}
}