#pragma once
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
#include "Coin.h"
#define TRAINING_SIZE 11
#define TEST_SIZE 10
#define IMAGE_SIZE_HEIGHT_MAX 500
#define IMAGE_SIZE_WIDTH_MAX 500
#define MAX_SIZE 16

using namespace std;
using namespace cv;
using namespace ml;

class myMoments {

	int VEC_SIZE;
	float trainingData[TRAINING_SIZE][100];
	int labels[TRAINING_SIZE];
	int pLabels[TEST_SIZE];
	float pData[TEST_SIZE][100];
	string TrainingImagesArray[TRAINING_SIZE];
	string TestingImagesArray[TEST_SIZE];

public:

	myMoments(int VS);
	void start(const char * path, bool console);
	void extractHuMoments(string *imagesArray, boolean t, const char * path, boolean console);
	void getMatrices(float tD[15][100], int l[15], float pD[10][100], int pl[15]);
};