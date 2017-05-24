#pragma once
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

using namespace std;
using namespace cv;
using namespace ml;

class NN {

	int VEC_SIZE;
	float trainingData[TRAINING_SIZE][100];
	int labels[TRAINING_SIZE];
	int pLabels[TEST_SIZE];
	float pData[TEST_SIZE][100];

public:

	NN(int VS = 0, float tD[15][100] = { 0 }, int l[15] = { 0 }, float pD[10][100] = { 0 }, int pl[15] = { 0 });

	bool train_mlp_classifier(const string& filename_to_save);
	inline TermCriteria TC(int iters, double eps);
	void predict_display_results(const Ptr<StatModel>& model, const string& filename_to_save);
	float getVal(int c);

};