#include <iostream>
#include "fstream"
#include <string>
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
#define TEST_first 1
#define TEST_first_demo	0


std::random_device rd;
std::mt19937 gen(rd());

int random(int low, int high)
{
	std::uniform_int_distribution<> dist(low, high);
	return dist(gen);
}

int main()
{

	int i;
	Mat src;
	Mat console;
	int kodim_num;
	int quality;
	int filter_strength;
	int filter_strength_conv;
	int quality_mul;
	int counti = 0;
	int jnd = -1;
	
	std::ofstream backup("backup.csv");
	int t = 12;
	unsigned int now = (unsigned int)time(0);
	srand(now);
	now = (unsigned int)time(0);
	srand(now);
	auto now_t = chrono::system_clock::now().time_since_epoch().count();
	int key = -1;

	vector<string> in_str = { "Not the same","    Same" };

	int count[10][5][4];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 4; k++) {
				count[i][j][k] = -1;
			}
		}
	}

	int count_first[10][5][4];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 4; k++) {
				count_first[i][j][k] = -1;
			}
		}
	}

	int flag[10][5][4];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 4; k++) {
				count_first[i][j][k] = -1;
			}
		}
	}

	int flag_first[10][5][4];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 4; k++) {
				count_first[i][j][k] = -1;
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
		cv::moveWindow("demo", 700, 400);

		console = Mat::zeros(512, 512, CV_8U);
		cv::namedWindow("console");
		cv::moveWindow("console", 1724, 400);



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
		cv::moveWindow("demo", 700, 400);

		console = Mat::zeros(512, 512, CV_8U);
		cv::namedWindow("console");
		cv::moveWindow("console", 1724, 400);

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
		cv::moveWindow("demo", 700, 400);

		console = Mat::zeros(512, 512, CV_8U);
		cv::namedWindow("console");
		cv::moveWindow("console", 1724, 400);

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
		cv::moveWindow("demo", 700, 400);

		console = Mat::zeros(512, 512, CV_8U);
		cv::namedWindow("console");
		cv::moveWindow("console", 1724, 400);

		
		
		cv::putText(console, "please wait", Point(50, 250), cv::FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 2);
		cv::imshow("console", console);
		cv::imshow("demo", src);
		key = waitKey(1);
	}
	destroyWindow("demo");
	
	now_t = chrono::system_clock::now().time_since_epoch().count();



	
#if TEST_first
	//‰æ‘œ‘I‘ð
	i = 0;
	now_t = chrono::system_clock::now().time_since_epoch().count();
	while (i < 200 && key != 'q')
	{
		key = -1;
		jnd = -1;
		kodim_num = random(1, 10);
		quality = random(5, 9);
		filter_strength = random(0, 3);
		t = 12;





		if (count_first[kodim_num - 1][quality - 5][filter_strength] == -1)
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
				filter_strength_conv = 2015;
			}
			else if (filter_strength == 3)
			{
				filter_strength_conv = 101;
			}
			else {
				cout << "error" << endl;
			}

			quality_mul = quality * 10;

			if (filter_strength_conv == 2015)
			{
				if (quality_mul == 60)
				{
					quality_mul = 30;
				}
				else if (quality_mul == 70)
				{
					quality_mul = 35;
				}
				else if (quality_mul == 80)
				{
					quality_mul = 40;
				}
				else if (quality_mul == 90)
				{
					quality_mul = 45;
				}
			}

			String str = format("./kodak_comp_gray_200/kodim%d_gray_%d_%d.png", kodim_num, quality_mul, filter_strength_conv);
			src = imread(str, 0);
			cv::namedWindow("test");
			cv::moveWindow("test", 700, 400);

			while (key != ENTER || jnd == -1)
			{
				console = Mat::zeros(512, 512, CV_8U);
				cv::namedWindow("console");
				cv::moveWindow("console", 1724, 400);

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




			count_first[kodim_num - 1][quality - 5][filter_strength] = jnd;
			string str1 = format("kodim%d_%d_%d", kodim_num, quality * 10, filter_strength);
			backup << str1 << "," << jnd << "," << endl;
			i++;
			flag_first[kodim_num - 1][quality - 5][filter_strength] = i;
			cout << i << endl;
			cout << flag_first[kodim_num - 1][quality - 5][filter_strength] << endl;
			cout << "kodim_num-1" << "," << kodim_num - 1 << "," << "quality " << "," << quality - 5 << "," << "filter_strength" << filter_strength << "," << endl;
 			cout << count_first[kodim_num - 1][quality - 5][filter_strength] << endl;
			destroyWindow("test");


			if (i == 100||i==200)
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

#endif



	
#if TEST	

	//‰æ‘œ‘I‘ð
	i = 0;
	now_t = chrono::system_clock::now().time_since_epoch().count();
	while (i < 200 && key != 'q')
	{
		key = -1;
		jnd = -1;
		kodim_num = random(1, 10);
		quality = random(2, 6);
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
				filter_strength_conv = 2015;
			}
			else if (filter_strength == 3)
			{
				filter_strength_conv = 101;
			}
			else {
				cout << "error" << endl;
			}

			quality_mul = quality * 10;

			if (filter_strength_conv == 2015)
			{
				if (quality_mul == 50)
				{
					quality_mul = 25;
				}
				else if (quality_mul == 60)
				{
					quality_mul = 35;
				}
			}

			String str = format("./kodak_comp_gray_100/kodim%d_gray_%d_%d.png", kodim_num, quality_mul, filter_strength_conv);
			src = imread(str, 0);
			cv::namedWindow("test");
			cv::moveWindow("test", 700, 400);

			while (key != ENTER || jnd == -1)
			{
				console = Mat::zeros(512, 512, CV_8U);
				cv::namedWindow("console");
				cv::moveWindow("console", 1724, 400);

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
			flag[kodim_num - 1][quality - 2][filter_strength] = i;
			cout << i << endl;
			destroyWindow("test");


			if (i == 100 )
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

#endif

	std::ofstream fout("test.csv");

	string str;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << flag_first[i][j][0] << endl;
			str = format("kodim%d_%d", i + 1, (j + 5) * 10);
			fout << str <<  "," <<count_first[i][j][0] <<  "," << count_first[i][j][1]  << "," << count_first[i][j][2] <<  "," << count_first[i][j][3] << "," << endl;

		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << flag_first[i][j][0] << endl;
			str = format("kodim%d_%d", i + 1, (j + 5) * 10);
			fout << str << "," << flag_first[i][j][0] <<  "," << flag_first[i][j][1]  << "," << flag_first[i][j][2] << "," << flag_first[i][j][3] << "," << endl;

		}
	}
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			str = format("kodim%d_%d", i + 1, (j +2)* 10);
			fout << str << ","  << count[i][j][0] <<  "," << count[i][j][1] << "," << count[i][j][2] << "," << count[i][j][3] << "," << endl;
			
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			str = format("kodim%d_%d", i + 1, (j + 2) * 10);
			fout << str << "," << flag[i][j][0] <<  "," << flag[i][j][1] <<  "," << flag[i][j][2] << "," << flag[i][j][3]  << "," << endl;

		}
	}

	int sum1[5][4] = {};
	int sum0[5][4] = {};

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 10; i++)
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

	for (int j = 0; j < 5; j++)
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