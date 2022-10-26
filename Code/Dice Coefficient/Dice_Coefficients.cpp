#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


static int label = 1;
int equi[2000] = { 0 };
void all_zero(int** arr11, int i, int j)
{
	arr11[i][j] = label;
	label = label + 1;
}
void not_zero(int** arr11, int i, int j, int minimum)
{
	arr11[i][j] = minimum;
}
int find_min(int sides_arr11[4], int minimum)
{
	for (int i = 0; i < 4; i++)
	{
		if (sides_arr11[i] != 0)
		{
			if (sides_arr11[i] < minimum)
			{
				minimum = sides_arr11[i];
			}
		}
	}
	for (int i = 0; i < 4; i++)
		if (sides_arr11[i] && sides_arr11[i] != minimum)
			equi[sides_arr11[i]] = minimum;
	return minimum;
}
void compare(int** arr1, int i, int j)
{
	int minimum = 0;
	int sides_arr1[] = { arr1[i][j - 1]   ,   arr1[i - 1][j - 1]  ,   arr1[i - 1][j]  , arr1[i - 1][j + 1] };
	if (sides_arr1[0] == 0 && sides_arr1[1] == 0 && sides_arr1[2] == 0 && sides_arr1[3] == 0)
	{
		all_zero(arr1, i, j);
	}
	else
	{
		minimum = find_min(sides_arr1, INT16_MAX);
		for (int k = 0; k < 4; k++)
		{
			if (sides_arr1[k] != 0)
			{
				not_zero(arr1, i, j, minimum);
			}
		}
	}
}
void second_pass(int** arr1, int equi[2000], int r, int c)
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (equi[arr1[i][j]] != 0)
			{
				int ind = equi[arr1[i][j]];
				while (equi[ind])
					ind = equi[ind];
				arr1[i][j] = ind;
			}
		}
	}
}
int mostOccured(int** arr1, int rows, int cols)
{
	int max[2000] = { 0 };
	int maximum_occured = 0;
	int most_repeated;
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (arr1[i][j] != 0)
			{
				max[arr1[i][j]] = max[arr1[i][j]] + 1;
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
		if (max[i] == maximum_occured)
		{
			most_repeated = i;
		}
	}
	return most_repeated;
}
int main()
{
	int tp = 0, fp = 0, fn = 0 ;
	double dice_c = 0;
	int tp2 = 0, fp2 = 0, fn2 = 0;
	double dice_c2 = 0;
	int max_occured, size;
	string filename1, filename2, filename3;
	cout << "Enter the name of the file from task1 : \n";
	getline(cin, filename1);
	cout << "Enter the name of the file from task2:\n";
	getline(cin, filename3);
	cout << "Enter the name of the file from ground truths:\n";
	getline(cin, filename2);
	Mat obj;
	Mat image = imread("D:\\DS A1\\Segmented Outputs\\" + filename1 + ".bmp", IMREAD_GRAYSCALE);
	Mat image2 = imread("D:\\DS A1\\Ground Truths\\" + filename2 + ".bmp", IMREAD_GRAYSCALE);
	Mat image3 = imread("D:\\DS A1\\Original Images\\" + filename3 + ".bmp", IMREAD_GRAYSCALE);
	int nmbr_of_rows1 = image.rows;
	int nmbr_of_cols1 = image.cols;
	int nmbr_of_rows2 = image2.rows;
	int nmbr_of_cols2 = image2.cols;
	int nmbr_of_rows3 = image3.rows;
	int nmbr_of_cols3 = image3.cols;
	int** arr1 = new int* [nmbr_of_rows1];
	for (int i = 0; i < nmbr_of_rows1; i++)
	{
		arr1[i] = new int[nmbr_of_cols1];
	}
	int** arr2 = new int* [nmbr_of_rows2];
	for (int i = 0; i < nmbr_of_rows2; i++)
	{
		arr2[i] = new int[nmbr_of_cols2];
	}
	int** arr3 = new int* [nmbr_of_rows3];
	for (int i = 0; i < nmbr_of_rows3; i++)
	{
		arr3[i] = new int[nmbr_of_cols3];
	}
	//CONVERTING IMAGES INTO ARRAY
	for (int i = 0; i < nmbr_of_rows1; i++)
	{
		for (int j = 0; j < nmbr_of_cols1; j++)
		{
			arr1[i][j] = image.at<unsigned char>(i, j);
		}
	}
	for (int i = 0; i < nmbr_of_rows2; i++)
	{
		for (int j = 0; j < nmbr_of_cols2; j++)
		{
			arr2[i][j] = image2.at<unsigned char>(i, j);
		}
	}
	for (int i = 0; i < nmbr_of_rows3; i++)
	{
		for (int j = 0; j < nmbr_of_cols3; j++)
		{
			arr3[i][j] = image3.at<unsigned char>(i, j);
		}
	}
	//Question 1 part
	for (int i = 1; i < nmbr_of_rows1 - 1; i++)
	{
		for (int j = 1; j < nmbr_of_cols1 - 1; j++)
		{
			if (arr1[i][j] == 255)
			{
				compare(arr1, i, j);
			}
		}
	}
	second_pass(arr1, equi, nmbr_of_rows1, nmbr_of_cols1);
	max_occured = mostOccured(arr1, nmbr_of_rows1, nmbr_of_cols1);//finding the max label occured
	for (int i = 0; i < nmbr_of_rows1; i++)//replacing the max label occured with 255
	{
		for (int j = 0; j < nmbr_of_cols1; j++)
		{
			if (arr1[i][j] == max_occured)
			{
				arr1[i][j] = 255;
			}
			else
			{
				arr1[i][j] = 0;
			}
		}
	}




	//Question 2 Part
	srand(time(0));
	int centeroid1 = rand() % 256;
	int centeroid2 = rand() % 256;
	int diff1 = 0, diff2 = 0;
	int sum1 = 0, sum2 = 0;
	int mean1 = 0, mean2 = 0;
	int counter1 = 0, counter2 = 0;
	int** c1 = new int* [nmbr_of_rows3];//arr for c1
	for (int i = 0; i < nmbr_of_rows3; i++)
	{
		c1[i] = new int[nmbr_of_cols3];
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
		for (int i = 0; i < nmbr_of_rows3; i++)
		{
			for (int j = 0; j < nmbr_of_cols3; j++)
			{
				diff1 = abs(centeroid1 - arr3[i][j]);
				diff2 = abs(centeroid2 - arr3[i][j]);
				if (diff1 > diff2)
				{
					c1[i][j] = 0;
					counter2 = counter2 + 1;
				}
				else
				{
					c1[i][j] = 1;
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

		for (int i = 0; i < nmbr_of_rows3; i++)
		{
			for (int j = 0; j < nmbr_of_cols3; j++)
			{
				if (c1[i][j] == 1)
					sum1 = sum1 + arr3[i][j];
				else
					sum2 = sum2 + arr3[i][j];
			}
		}
		mean1 = sum1 / counter1;
		mean2 = sum2 / counter2;
	}

	if (centeroid1 < centeroid2)
	{
		for (int i = 0; i < nmbr_of_rows3; i++)
		{
			for (int j = 0; j < nmbr_of_cols3; j++)
			{
				arr3[i][j] = 0;
				if (c1[i][j] == 1)
				{
					arr3[i][j] = 255;
				}
			}
		}
	}
	else if (centeroid2 < centeroid1)
	{
		for (int i = 0; i < nmbr_of_rows3; i++)
		{
			for (int j = 0; j < nmbr_of_cols3; j++)
			{
				arr3[i][j] = 0;
				if (c1[i][j] == 0)
				{
					arr3[i][j] = 255;
				}
			}
		}
	}

	//START OF 3RD------
	for (int i = 0; i < nmbr_of_rows1; i++)
	{
		for (int j = 0; j < nmbr_of_cols1; j++)
		{
			if (arr1[i][j] == 255 && arr2[i][j] == 255)
			{
				tp = tp + 1;
			}
			else if (arr1[i][j] == 0 && arr2[i][j] == 255)
			{
				fp = fp + 1;
			}
			else if (arr1[i][j] == 255 && arr2[i][j] == 0)
			{
				fn = fn + 1;
			}
		}
	}


	for (int i = 0; i < nmbr_of_rows3; i++)
	{
		for (int j = 0; j < nmbr_of_cols3; j++)
		{
			if (arr3[i][j] == 255 && arr2[i][j] == 255)
			{
				tp2 = tp2 + 1;
			}
			else if (arr3[i][j] == 0 && arr2[i][j] == 255)
			{
				fp2 = fp2 + 1;
			}
			else if (arr3[i][j] == 255 && arr2[i][j] == 0)
			{
				fn2 = fn2 + 1;
			}
		}
	}
	dice_c = double(2 * tp) / double(2 * tp + fp + fn);
	dice_c2 = double(2 * tp2) / double(2 * tp2 + fp2 + fn2);
	cout << "Dice coefficient for task 1 is:" << dice_c << endl;
	cout << "Dice coefficient for task 2 is:" << dice_c2 << endl;

	/*Mat A = cv::Mat(nmbr_of_rows, nmbr_of_cols, CV_8UC1);
	for (int i = 0; i < nmbr_of_rows; i++)
		for (int j = 0; j < nmbr_of_cols; j++)
			A.data[A.step[0] * i + A.step[1] * j] = unsigned char(arr1[i][j]);
	cv::namedWindow("title", cv::WINDOW_NORMAL);
	cv::imshow("title", A);*/
	cv::waitKey();
	return 0;
}