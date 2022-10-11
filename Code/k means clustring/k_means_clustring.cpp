#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdlib>
using namespace cv;
using namespace std;


int main()
{
	srand(time(0));
	int centeroid1 = rand() % 256;
	int centeroid2 = rand() % 256;
	int diff1 = 0, diff2 = 0;
	int sum1 = 0, sum2 = 0;
	int mean1 = 0, mean2 = 0;
	int counter1 = 0, counter2 = 0;
	string filename;
	cout << "Enter the name of the file : ";
	getline(cin, filename);
	Mat obj;
	Mat image = imread("D:\\DS A1\\Original Images\\" + filename + ".bmp", IMREAD_GRAYSCALE);
	int nmbr_of_rows = image.rows;
	int nmbr_of_cols = image.cols;
	int** arr = new int* [nmbr_of_rows];//arr for image
	for (int i = 0; i < nmbr_of_rows; i++)
	{
		arr[i] = new int[nmbr_of_cols];
	}
	int** c1 = new int* [nmbr_of_rows];//arr for c1
	for (int i = 0; i < nmbr_of_rows; i++)
	{
		c1[i] = new int[nmbr_of_cols];
	}
	for (int i = 0; i < nmbr_of_rows; i++)
	{
		for (int j = 0; j < nmbr_of_cols; j++)
		{
			c1[i][j] = 0;
		}
	}
	//CONVERTING IMAGE INTO ARRAY
	for (int i = 0; i < nmbr_of_rows; i++)
	{
		for (int j = 0; j < nmbr_of_cols; j++)
		{
			arr[i][j] = image.at<unsigned char>(i, j);
		}
	}

	while (mean1 != centeroid1 && mean2 != centeroid2)
	{
		if (mean1 != 0 && mean2 != 0)
		{
			centeroid1 = mean1;
			centeroid2 = mean2;
		}
		counter1 = 0;
		counter2 = 0;
		for (int i = 0; i < nmbr_of_rows; i++)
		{
			for (int j = 0; j < nmbr_of_cols; j++)
			{
				diff1 = abs(centeroid1 - arr[i][j]);
				diff2 = abs(centeroid2 - arr[i][j]);
				if (diff1 > diff2)
				{
					c1[i][j] = 0;
					counter2 = counter2 + 1;
				}
				else
				{
					c1[i][j] =1;
					counter1 = counter1 + 1;
				}
			}
		}

		if (counter1 == 0 || counter2 == 0)
		{
			centeroid1 = rand() % 256;
			centeroid2 = rand() % 256;
			continue;
		}
		sum1 = 0; sum2 = 0;

		for (int i = 0; i < nmbr_of_rows; i++)
		{
			for (int j = 0; j < nmbr_of_cols; j++)
			{
				if (c1[i][j] == 1)
					sum1 = sum1 + arr[i][j];
				else
					sum2 = sum2 + arr[i][j];
			}
		}
		mean1 = sum1 / counter1;
		mean2 = sum2 / counter2;
	}
	
	if (centeroid1 < centeroid2)
	{
		for (int i = 0; i < nmbr_of_rows; i++)
		{
			for (int j = 0; j < nmbr_of_cols; j++)
			{
				arr[i][j] = 0;
				if (c1[i][j] == 1)
				{
					arr[i][j] = 255;
				}	
			}
		}
	}
	else if (centeroid2 < centeroid1)
	{
		for (int i = 0; i < nmbr_of_rows; i++)
		{
			for (int j = 0; j < nmbr_of_cols; j++)
			{
				arr[i][j] = 0;
				if (c1[i][j] == 0)
				{
					arr[i][j] = 255;
				}
			}
		}
	}
	
	Mat A = cv::Mat(nmbr_of_rows, nmbr_of_cols, CV_8UC1);
	for (int i = 0; i < nmbr_of_rows; i++)
		for (int j = 0; j < nmbr_of_cols; j++)
			A.data[A.step[0] * i + A.step[1] * j] = unsigned char(arr[i][j]);
	cv::namedWindow("title", cv::WINDOW_NORMAL);
	cv::imshow("title", A);
	cv::waitKey();
	return 0;
}