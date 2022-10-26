#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


static int label = 1;
int equi[2000] = { 0 };//array for storing equivalnce
void all_zero(int** arr, int i, int j)
{
	arr[i][j] = label;
	label = label + 1;
}
void not_zero(int** arr, int i, int j, int minimum)
{
	arr[i][j] = minimum;
}
int find_min(int sides_arr[4], int minimum)
{
	for (int i = 0; i < 4; i++)
	{
		if (sides_arr[i] != 0)
		{
			if (sides_arr[i] < minimum)
			{
				minimum = sides_arr[i];
			}
		}
	}
	for (int i = 0; i < 4; i++)
		if (sides_arr[i] && sides_arr[i] != minimum)
			equi[sides_arr[i]] = minimum;
	return minimum;
}
void compare(int** arr, int i, int j)
{
	int minimum = 0;
	int sides_arr[] = { arr[i][j - 1]   ,   arr[i - 1][j - 1]  ,   arr[i - 1][j]  , arr[i - 1][j + 1] };
	if (sides_arr[0] == 0 && sides_arr[1] == 0 && sides_arr[2] == 0 && sides_arr[3] == 0)
	{
		all_zero(arr, i, j);
	}
	else
	{
		minimum = find_min(sides_arr, INT16_MAX);
		for (int k = 0; k < 4; k++)
		{
			if (sides_arr[k] != 0)
			{
				not_zero(arr, i, j, minimum);
			}
		}
	}
}
void second_pass(int** arr, int equi[2000], int r, int c)
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (equi[arr[i][j]] != 0)
			{
				int ind = equi[arr[i][j]];
				while (equi[ind])
					ind = equi[ind];
				arr[i][j] = ind;
			}
		}
	}
}
int mostOccured(int** arr, int rows, int cols)
{
	int max[2000] = { 0 };
	int maximum_occured = 0;
	int most_repeated;
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (arr[i][j] != 0)
			{
				max[arr[i][j]] = max[arr[i][j]] + 1;
			}
		}
	}
	maximum_occured = 0;
	for (int i = 0; i < 2000; i++)
	{
		if (max[i] > maximum_occured)
		{
			maximum_occured = max[i];
		}
	}
	for (int i = 0; i < 2000; i++)
	{
		//cout << i << "   " << max[i] << endl;
		if (max[i] == maximum_occured)
		{
			most_repeated = i;
		}
	}
	return most_repeated;
}
int main()
{
	int max_occured, size;
	string filename;
	cout << "Enter the name of the file : ";
	getline(cin, filename);
	Mat obj;
	Mat image = imread("D:\\DS A1\\Segmented Outputs\\" + filename + ".bmp", IMREAD_GRAYSCALE);
	int nmbr_of_rows = image.rows;
	int nmbr_of_cols = image.cols;
	int** arr = new int* [nmbr_of_rows];
	for (int i = 0; i < nmbr_of_rows; i++)
	{
		arr[i] = new int[nmbr_of_cols];
	}
	//CONVERTING IMAGE INTO ARRAY
	for (int i = 0; i < nmbr_of_rows; i++)
	{
		for (int j = 0; j < nmbr_of_cols; j++)
		{
			arr[i][j] = image.at<unsigned char>(i, j);
		}
	}
	for (int i = 1; i < nmbr_of_rows - 1; i++)
	{
		for (int j = 1; j < nmbr_of_cols - 1; j++)
		{
			if (arr[i][j] == 255)
			{
				compare(arr, i, j);
			}
		}
	}
	second_pass(arr, equi, nmbr_of_rows, nmbr_of_cols);
	max_occured = mostOccured(arr, nmbr_of_rows, nmbr_of_cols);//finding the max label occured
	for (int i = 0; i < nmbr_of_rows; i++)//replacing the max label occured with 255
	{
		for (int j = 0; j < nmbr_of_cols; j++)
		{
			if (arr[i][j] == max_occured)
			{
				arr[i][j] = 255;
			}
			else
			{
				arr[i][j] = 0;
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