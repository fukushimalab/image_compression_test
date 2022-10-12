#include "iostream"
#include "fstream"
#include "string"
#include "opencp.hpp"
#include <random>
#include <map>
#include <vector>
#include <filesystem>
#include <time.h>

using namespace cv;
using namespace std;

#ifdef _DEBUG
#pragma comment(lib, "opencpd.lib")
#else
#pragma comment(lib, "opencp.lib")
#endif

#define REST 0
#define TEST 1
#define ENTER 13
#define DEMO 1

std::random_device rd;
std::mt19937 gen(rd());

int random(int low, int high)
{
	std::uniform_int_distribution<> dist(low, high);
	return dist(gen);
}

int main()
{


	Mat src;
	Mat console;
	int kodim_num;
	int quality;
	int filter_strength;
	int filter_strength_conv;
	int quality_mul;
	int counti = 0;
	int jnd = -1;
	std::ofstream fout("test.csv");
	std::ofstream backup("backup.csv");
	int t = 12;
	unsigned int now = (unsigned int)time(0);
	srand(now);
	now = (unsigned int)time(0);
	srand(now);
	auto now_t = chrono::system_clock::now().time_since_epoch().count();
	int key = -1;

	vector<string> in_str = { "Not the same","    Same" };

	int count[16][7][4];
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 7; j++) {
			for (int k = 0; k < 4; k++) {
				count[i][j][k] = -1;
			}
		}
	}
	
#if DEMO
	Mat background = Mat::zeros(1440, 2550, CV_8U);
	cv::namedWindow("background");
	cv::moveWindow("background", 0, 0);
	cv::imshow("background", background);
	while (key != 's')
	{
		src = Mat::zeros(512, 1024, CV_8U);
		cv::namedWindow("demo");
		cv::moveWindow("demo", 360, 200);

		console = Mat::zeros(512, 512, CV_8U);
		cv::namedWindow("console");
		cv::moveWindow("console", 1384, 200);



		cv::putText(console, "please wait", Point(50, 250), cv::FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 2);
		cv::imshow("console", console);
		cv::imshow("demo", src);
		key = cv::waitKey(1);
	}
	now_t = chrono::system_clock::now().time_since_epoch().count();
	while (key != ENTER || jnd == -1)
	{
		src = imread("./demo/lenna_same.png", 0);
		cv::namedWindow("demo");
		cv::moveWindow("demo", 360, 200);

		console = Mat::zeros(512, 512, CV_8U);
		cv::namedWindow("console");
		cv::moveWindow("console", 1384, 200);

		if (key == '1')
		{
			jnd = 1;
		}
		else if (key == '0')
		{
			jnd = 0;
		}
		else if (key == 'q')
		{
			break;
		}
		string text = (jnd != -1) ? in_str[jnd] : "";
		string request = (jnd == -1) ? "Please enter your answer." : "";
		t = 12 - (chrono::system_clock::now().time_since_epoch().count() - now_t) / 10000000;
		t = (t < 0) ? 0 : t;
		cv::putText(console, request, Point(30, 100), cv::FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2);
		cv::putText(console, text, Point(30, 120), cv::FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 2);
		cv::putText(console, format("%2d", t), Point(130, 350), cv::FONT_HERSHEY_SIMPLEX, 5, Scalar(255, 255, 255), 10);
		cv::imshow("console", console);
		cv::imshow("demo", src);
		key = waitKey(1);
	}
	jnd = -1;
	;
	now_t = chrono::system_clock::now().time_since_epoch().count();
	while (key != ENTER || jnd == -1)
	{
		src = imread("./demo/lenna_notsame.png", 0);
		cv::namedWindow("demo");
		cv::moveWindow("demo", 360, 200);

		console = Mat::zeros(512, 512, CV_8U);
		cv::namedWindow("console");
		cv::moveWindow("console", 1384, 200);

		if (key == '1')
		{
			jnd = 1;
		}
		else if (key == '0')
		{
			jnd = 0;
		}
		else if (key == 'q')
		{
			break;
		}
		string text = (jnd != -1) ? in_str[jnd] : "";
		string request = (jnd == -1) ? "Please enter your answer." : "";
		t = 12 - (chrono::system_clock::now().time_since_epoch().count() - now_t) / 10000000;
		t = (t < 0) ? 0 : t;
		cv::putText(console, request, Point(30, 100), cv::FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2);
		cv::putText(console, text, Point(30, 120), cv::FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 2);
		cv::putText(console, format("%2d", t), Point(130, 350), cv::FONT_HERSHEY_SIMPLEX, 5, Scalar(255, 255, 255), 10);
		cv::imshow("console", console);
		cv::imshow("demo", src);
		key = waitKey(1);
	}
#endif
	jnd = -1;
	while (key != 's' )
	{
		src = Mat::zeros(512, 1024, CV_8U);
		cv::namedWindow("demo");
		cv::moveWindow("demo", 360, 200);

		console = Mat::zeros(512, 512, CV_8U);
		cv::namedWindow("console");
		cv::moveWindow("console", 1384, 200);

		
		
		cv::putText(console, "please wait", Point(50, 250), cv::FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 2);
		cv::imshow("console", console);
		cv::imshow("demo", src);
		key = waitKey(1);
	}
	destroyWindow("demo");
	


	while (key != ENTER || jnd == -1)
	{
		src = imread("./demo/first_img.png", 0);
		cv::namedWindow("demo");
		cv::moveWindow("demo", 360, 200);

		console = Mat::zeros(512, 512, CV_8U);
		cv::namedWindow("console");
		cv::moveWindow("console", 1384, 200);

		if (key == '1')
		{
			jnd = 1;
		}
		else if (key == '0')
		{
			jnd = 0;
		}
		else if (key == 'q')
		{
			break;
		}
		string text = (jnd != -1) ? in_str[jnd] : "";
		string request = (jnd == -1) ? "Please enter your answer." : "";
		t = 12 - (chrono::system_clock::now().time_since_epoch().count() - now_t) / 10000000;
		t = (t < 0) ? 0 : t;
		cv::putText(console, request, Point(30, 100), cv::FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2);
		cv::putText(console, text, Point(30, 120), cv::FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 2);
		cv::putText(console, format("%2d", t), Point(130, 350), cv::FONT_HERSHEY_SIMPLEX, 5, Scalar(255, 255, 255), 10);
		cv::imshow("console", console);
		cv::imshow("demo", src);
		key = waitKey(1);
	}
	key=waitKey(500);
	destroyWindow("demo");
	
	jnd = -1;
	

	//‰æ‘œ‘I‘ð
	int i = 0;
	now_t = chrono::system_clock::now().time_since_epoch().count();
	while (i < 448 && key != 'q')
	{
		key = -1;
		jnd = -1;
		kodim_num = random(1, 16);
		quality = random(2, 8);
		filter_strength = random(0, 3);
		t = 12;


		
		

		if (count[kodim_num - 1][quality - 2][filter_strength] == -1)
		{

			if (filter_strength == 0)
			{
				filter_strength_conv = 0;
			}
			else if (filter_strength == 1)
			{
				filter_strength_conv = 35;
			}
			else if (filter_strength == 2)
			{
				filter_strength_conv = 100;
			}
			else if (filter_strength == 3)
			{
				filter_strength_conv = 101;
			}
			else {
				cout << "error" << endl;
			}

			quality_mul = quality * 10;

			String str = format("./kodak_comp_img/kodim%d_gray_%d_%d.png", kodim_num, quality_mul, filter_strength_conv);
			src = imread(str, 0);
			cv::namedWindow("test");
			cv::moveWindow("test", 360, 200);

			while (key != ENTER || jnd == -1)
			{
				console = Mat::zeros(512, 512, CV_8U);
				cv::namedWindow("console");
				cv::moveWindow("console", 1384, 200);

				if (key == '1')
				{
					jnd = 1;


				}
				else if (key == '0')

				{
					jnd = 0;

				}

				else if (key == 'q')
				{
					exit(0);
				}

				string text = (jnd != -1) ? in_str[jnd] : "";
				string request = (jnd == -1) ? "Please enter your answer." : "";
				t = 12 - (chrono::system_clock::now().time_since_epoch().count() - now_t) / 10000000;
				t = (t < 0) ? 0 : t;


				cv::putText(console, request, Point(30, 100), cv::FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2);
				cv::putText(console, text, Point(30, 120), cv::FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 2);
				cv::putText(console, format("%2d", t), Point(130, 350), cv::FONT_HERSHEY_SIMPLEX, 5, Scalar(255, 255, 255), 10);

				cv::imshow("console", console);
				cv::imshow("test", src);
				key = waitKey(1);


			}




			count[kodim_num - 1][quality - 2][filter_strength] = jnd;
			string str1 = format("kodim%d_%d_%d", kodim_num, quality * 10, filter_strength);
			backup << str1 << "," << jnd << "," << endl;
			i++;
			cout << i << endl;
			destroyWindow("test");


			if (i == 150 || i == 300)
			{
				while (key != 's')
				{
					Mat rest = Mat::zeros(1440, 2560, CV_8U);
					putText(rest, "Please rest your eyes", Point(300, 700), cv::FONT_HERSHEY_COMPLEX, 3, Scalar(255, 255, 255), 10);
					namedWindow("rest");
					moveWindow("rest", 0, 0);
					imshow("rest", rest);
					key = waitKey(1);

				}
				destroyWindow("rest");
			}
			waitKey(500);
			now_t = chrono::system_clock::now().time_since_epoch().count();
			//waitKey(1);

		}

	}

	string str;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			str = format("kodim%d_%d", i + 1, (j +2)* 10);
			fout << str << "," << count[i][j][0] << "," << count[i][j][1] << "," << count[i][j][2] << "," << count[i][j][3] << "," << endl;
			
		}
	}

	int sum1[7][4] = {};
	int sum0[7][4] = {};

	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (count[i][j][k] == 1)
				{
					sum1[j][k]++;
				}
				else if (count[i][j][k] == 0)
				{
					sum0[j][k]++;
				}
			}
		}
	}

	for (int j = 0; j < 7; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			str = format("q=%d f=%d", (j + 2) * 10, k);
			fout << str << "," << sum1[j][k] << "," << sum0[j][k] << "," << endl;
		}
	}

	Mat finish = Mat::zeros(512, 1024, CV_8UC3);
	cv::namedWindow("finish");
	cv::moveWindow("finish", 360, 200);
	cv::putText(finish, "Thanks for your cooperation!!", Point(50, 250), cv::FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 1);
	cv::imshow("finish", finish);
	waitKey(0);
	cv::destroyWindow("background");






	return 0;
}