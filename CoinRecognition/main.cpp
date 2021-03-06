//Ahmad Bin Khalid - 213504260

#include<Windows.h>
#include <vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<fstream>
#include<iostream>
#include<String.h>
#include<ctime>
#include "opencv2/ml.hpp"
#include "NN.h"
#include "mySVM.h"
#include "Haralick.h"
#include "myMoments.h"
#include "myKNN.h"

#define TRAINING_SIZE 11
#define TEST_SIZE 10
#define VEC_SIZE 7
#define HARALICK 48

using namespace std;
using namespace cv;
using namespace ml;

//Feature Extraction Variables
//--------------------------------------
//Training Purposes
int labels[TRAINING_SIZE];
float trainingData[TRAINING_SIZE][100];

//Prediction Purposes
int pLabels[TEST_SIZE];
float pData[TEST_SIZE][100];
//--------------------------------------

int main(int argc, char * argv[]) {

	const char * path = argv[1];

	boolean console = false;
	boolean exit = false;

	while (!exit) {

		cout << endl << "Welcome to the South African Coin CLassification System" << endl;
		cout << endl << "Choose one of the following options:" << endl;

		cout << "1) Extract Hu Moments using ANN classification" << endl;
		cout << "2) Extract Hu Moments using SVM classification" << endl;
		cout << "3) Extract Hu Moments using KNN classification" << endl;
		cout << "4) Extract Haralick Features using ANN classification" << endl;
		cout << "5) Extract Haralick Features using SVM classification" << endl;
		cout << "6) Extract Haralick Features using KNN classification" << endl;

		cout << "Enter an option (1-6):";

		int option;
		cin >> option;

		if (option == 1) {
			myMoments *Mm = new myMoments(VEC_SIZE);
			Mm->start(path, console);
			Mm->getMatrices(trainingData, labels, pData, pLabels);
			NN ann(VEC_SIZE, trainingData, labels, pData, pLabels);
			ann.train_mlp_classifier("classifier.txt");
		}
		else if (option == 2) {
			myMoments *Mm = new myMoments(VEC_SIZE);
			Mm->start(path, console);
			Mm->getMatrices(trainingData, labels, pData, pLabels);
			mySVM sv(VEC_SIZE, trainingData, labels, pData, pLabels);
			sv.train_mlp_classifier("classifier.txt");
		}
		else if (option == 3) {
			myMoments *Mm = new myMoments(VEC_SIZE);
			Mm->start(path, console);
			Mm->getMatrices(trainingData, labels, pData, pLabels);
			myKNN mk(VEC_SIZE, trainingData, labels, pData, pLabels);
			mk.train_mlp_classifier("classifier.txt");
		}
		else if (option == 4) {
			Haralick *hrl = new Haralick(HARALICK);
			hrl->start("", console);
			hrl->getMatrices(trainingData, labels, pData, pLabels);
			NN ann(HARALICK, trainingData, labels, pData, pLabels);
			ann.train_mlp_classifier("classifier.txt");
		}
		else if (option == 5) {
			Haralick *hrl = new Haralick(HARALICK);
			hrl->start("", console);
			hrl->getMatrices(trainingData, labels, pData, pLabels);
			mySVM sv(HARALICK, trainingData, labels, pData, pLabels);
			sv.train_mlp_classifier("classifier.txt");
		}
		else if (option == 6) {
			Haralick *hrl = new Haralick(HARALICK);
			hrl->start("", console);
			hrl->getMatrices(trainingData, labels, pData, pLabels);
			myKNN mk(HARALICK, trainingData, labels, pData, pLabels);
			mk.train_mlp_classifier("classifier.txt");
		}

		cout << endl << "Enter q to quit the program. Enter any other character to go back to the menu:";
		char q;
		cin >> q;
		if (q == 'q')
			exit = true;
	}

	//cv::waitKey();
	system("pause");
	return 0;

}

//for (int i = 0; i < gaussBlur.rows; i++)
//{
//	for (int j = 0; j < gaussBlur.cols; j++)
//	{
//		int pixel = (int)(gaussBlur.at<uchar>(i, j));
//		x[i][j] = pixel;
//	}
//}
//int count = 0;
//for (int i = 0; i < 2; i++)
//{
//	for (int j = 0; j < 4; j++)
//	{
//
//		calculateGLCM(orientation[j], distances[i], gaussBlur.cols, gaussBlur.rows);
//		Moments mp;
//		Mat dst = Mat(16, 16, CV_32F, p).inv();
//		mp = moments(dst, true);
//		double hu[7];
//		HuMoments(mp, hu);
//
//		if (t)
//		{
//			for (int i = 0; i < 7; i++)
//			{
//				trainingData[w][count] = hu[i];
//				count++;
//			}
//		}
//		else
//		{
//			for (int i = 0; i < 7; i++)
//			{
//				pData[w][count] = hu[i];
//			}
//		}
//	}
//}
//
//for (int i = 0; i < 16; i++)
//{
//	for (int j = 0; j < 16; j++)
//	{
//		cout << log10(p[i][j]) << " ";
//	}
//	cout << endl;
//}
//
//cout << endl << endl;