#include<iostream>
#include<string>
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
using namespace std;
using namespace cv;



void drawNumber(Mat img, int board[][9], double fontScale, int thickness)
{
	//TODO read board

	static const string n[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	int fontFace = CV_FONT_HERSHEY_TRIPLEX;


	int baseline = 0;
	Size textSize = getTextSize(n[2], fontFace, fontScale, thickness, &baseline);
	baseline += thickness;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			float x = img.size().width/9.0f*(i+0.5), y = img.size().height/9.0f*(j+0.5);
			Point textOrg(x - textSize.width / 2, y + textSize.height / 2);
			putText(img, n[board[i][j]], textOrg, fontFace, fontScale, Scalar::all(0), thickness, CV_AA);
		}
	}
}

void drawGrids(Mat img, float line_thickness, float line_thickness_b)
{
	Point2f coner(img.size().width, img.size().height);
	rectangle(img, cv::Rect2f(Point2f(0 + line_thickness_b / 2, 0 + line_thickness_b / 2),
		Point2f(coner.x - line_thickness_b / 2, coner.y - line_thickness_b / 2)), Scalar(0), line_thickness_b, CV_AA);
	for (int i = 1; i < 9; i++)
	{
		float thick = line_thickness;
		if (i % 3 == 0)
			thick = line_thickness_b;
		cv::line(img, Point2f(i*img.size().width / 9.0f, 0), Point2f(i*img.size().width / 9.0f, i*img.size().height), Scalar(0), thick, CV_AA);
		cv::line(img, Point2f(0, i*img.size().height / 9.0f), Point2f(img.size().width, i*img.size().height / 9.0f),Scalar(0), thick, CV_AA);
	}
}

void fillGrid(Mat img, int x, int y, const cv::Scalar &color)
{
	Rect2f rect(Point2f(x*img.size().width / 9, y*img.size().height / 9), 
		Point2f((x+1)*img.size().width / 9, (y+1)*img.size().height / 9));
	rectangle(img,rect, color, CV_FILLED, CV_AA);
}


int main(int argc, char * argv[])
{
	int resolution = 1080/2;
	float line_thickness_bold = 0.004f*resolution;
	float line_thickness = 0.001f*resolution;
	double fontScale = 0.002*resolution;
	int thickness = 0.002*resolution;


	//open file
	//for loop, read a board

	int board[9][9] = { 1 };
	for (int i = 0; i < 9; i++)
	for (int j = 0; j < 9; j++)
	{
		board[i][j] = (i + j) % 9;
	}

	Mat img(resolution, resolution, CV_8UC3, Scalar(255,255,255));

	//todo check who need coloring
	//todo coloring
	fillGrid(img, 2, 3, Scalar(100, 100, 100));
	fillGrid(img,1,1,Scalar(255,100,100));

	drawGrids(img, line_thickness, line_thickness_bold);
	drawNumber(img, board, fontScale, thickness);

	cv::imshow("test", img);
	cv::waitKey(0);
	cv::imwrite("sudokuBoard.png",img);
	return 0;
}