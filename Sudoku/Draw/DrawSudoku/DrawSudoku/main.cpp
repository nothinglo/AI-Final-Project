#include<iostream>
#include<string>
#include<fstream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

#include"../../../Sudoku/sudoku-operateBoard.h"

using namespace std;
using namespace cv;



//image, index of grid
void fillGrid(Mat img, int x, int y, const cv::Scalar &color);


void drawNumberBackground(Mat img, const int board[][sudokuSize])
{
	for (int i = 0; i < sudokuSize; i++)
	{
		for (int j = 0; j < sudokuSize; j++)
		{
			if (board[j][i] == 0)
				continue;
			//fillGrid(img, i, j, Scalar(225, 225, 225));
			fillGrid(img, i, j, Scalar(255, 210, 160));
			//fillGrid(img, i, j, Scalar(255, 255, 255));//white
		}
	}
}

void drawNumber(Mat img, const int board[][sudokuSize], double fontScale, int thickness)
{
	//TODO read board

	static const string n[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	int fontFace = CV_FONT_HERSHEY_TRIPLEX;


	int baseline = 0;
	Size textSize = getTextSize(n[2], fontFace, fontScale, thickness, &baseline);
	baseline += thickness;

	for (int i = 0; i < sudokuSize; i++)
	{
		for (int j = 0; j < sudokuSize; j++)
		{
			if (board[j][i] == 0)
				continue;

			float x = (float)img.size().width/sudokuSize*(i+0.5), y = (float)img.size().height/sudokuSize*(j+0.5);
			Point textOrg(x - textSize.width / 2, y + textSize.height / 2);
			putText(img, n[board[j][i]], textOrg, fontFace, fontScale, Scalar::all(0), thickness, CV_AA);

			
		}
	}
}

void drawGrids(Mat img, float line_thickness, float line_thickness_b)
{
	Point2f coner(img.size().width, img.size().height);
	rectangle(img, cv::Rect2f(Point2f(0 + line_thickness_b / 2, 0 + line_thickness_b / 2),
		Point2f(coner.x - line_thickness_b / 2, coner.y - line_thickness_b / 2)), Scalar(0), line_thickness_b, CV_AA);
	for (int i = 1; i < sudokuSize; i++)
	{
		float thick = line_thickness;
		if (i % 3 == 0)
			thick = line_thickness_b;
		cv::line(img, Point2f((float)i*img.size().width / sudokuSize, 0), Point2f((float)i*img.size().width / sudokuSize, i*img.size().height), Scalar(0), thick, CV_AA);
		cv::line(img, Point2f(0, (float)i*img.size().height / sudokuSize), Point2f((float)img.size().width, i*img.size().height / sudokuSize),Scalar(0), thick, CV_AA);
	}
}

void fillGrid(Mat img, int x, int y, const cv::Scalar &color)
{
	Rect2f rect(Point2f((float)x*img.size().width / sudokuSize, (float)y*img.size().height / sudokuSize), 
		Point2f((float)(x+1)*img.size().width / sudokuSize, (float)(y+1)*img.size().height / sudokuSize));
	rectangle(img,rect, color, CV_FILLED, CV_AA);
}


void drawBoard(Mat &img, const int board[][sudokuSize])
{
	int resolution = 1080;
	//float line_thickness_bold = 0.005f*resolution;
	float line_thickness_bold = 4;
	//float line_thickness = 0.0025f*resolution;
	float line_thickness = 2;
	double fontScale = 0.0032*resolution;
	int thickness = 0.006*resolution;

	//#clear color
	img = Mat(resolution, resolution, CV_8UC3, Scalar(255, 255, 255));//white
	//img = Mat(resolution, resolution, CV_8UC3, Scalar(190, 190, 190));//gray

	drawNumberBackground(img,board);

	//specify color
	//BGR
	//GD
	//fillGrid(img,8,2,Scalar(150,255,150));
	//fillGrid(img, 7, 3, Scalar(150, 255, 150));
	//fillGrid(img, 3, 4, Scalar(150, 255, 150));

	//SL
	//fillGrid(img, 4, 4, Scalar(150,150,255));//1
	//fillGrid(img, 5, 2, Scalar(150, 150, 255));//2
	//fillGrid(img, 5, 5, Scalar(150, 150, 255));//3
	//fillGrid(img, 2, 3, Scalar(150, 150, 255));//4

	drawNumber(img, board, fontScale, thickness);

	drawGrids(img, line_thickness, line_thickness_bold);

	cv::imshow("test", img);
	cv::waitKey(0);
}

void drawBoardFileToFile(char *inputFile, char *outputFile)
{
	Mat img;

	int board[sudokuSize][sudokuSize] = { 1 };

	/*
	for (int i = 0; i < sudokuSize; i++)
	for (int j = 0; j < sudokuSize; j++)
	{
	board[i][j] = (i + j) % sudokuSize;
	}*/
	generateByFileInputBoard(board, inputFile);
	drawBoard(img, board);
	cv::imwrite(outputFile, img);
}


int main(int argc, char * argv[])
{
	char *inputFileName = argv[1];
	char *outputFileName = argv[2];

	drawBoardFileToFile(inputFileName, outputFileName);

	return 0;
}