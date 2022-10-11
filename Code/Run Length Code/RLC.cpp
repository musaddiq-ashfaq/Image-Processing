#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class node {
public:
	int data;
	node* next;
	node()
	{
		data = 0;
		next = NULL;
	}
};

int main()
{
	string filename;
	cout << "Enter the name of the file : ";
	getline(cin, filename);
	Mat obj;
	Mat image = imread("D:\\DS A1\\Segmented Outputs\\" + filename + ".bmp", IMREAD_GRAYSCALE);
	int nmbr_of_rows = image.rows;
	int nmbr_of_cols = image.cols;
	int** arr = new int* [nmbr_of_rows];//arr for image
	for (int i = 0; i < nmbr_of_rows; i++)
	{
		arr[i] = new int[nmbr_of_cols];
	}
	for (int i = 0; i < nmbr_of_rows; i++)
	{
		for (int j = 0; j < nmbr_of_cols; j++)
		{
			arr[i][j] = image.at<unsigned char>(i, j);
		}
	}
	int i = 0, j = 0;
	node* head = new node;
	node* temp = head;
	while (j < nmbr_of_cols && i < nmbr_of_rows + 1)
	{
		for (; i < nmbr_of_rows; i++)
		{
			int prevwhite = -1;
			for (j=0; j < nmbr_of_cols; j++)
			{
				if (arr[i][j] == 255)
				{
					if (prevwhite != j - 1 || prevwhite==-1)
					{
						cout << j<<" ";
						temp->data = j;
						temp->next = new node();
						temp = temp->next;
					}
					prevwhite = j;
				}
				else
				{
					if (prevwhite == -1)
						continue;
					temp->data = prevwhite;
					temp->next = new node();
					temp = temp->next;
					cout << prevwhite<<" ";
					prevwhite = -1;
				}
			}
			temp->data = -1;
			temp->next = new node();
			temp = temp->next;
			cout << -1<<endl;
		}
	}
}