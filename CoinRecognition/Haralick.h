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

class Haralick {

	int VEC_SIZE;
	float trainingData[TRAINING_SIZE][100];
	int labels[TRAINING_SIZE];
	int pLabels[TEST_SIZE];
	float pData[TEST_SIZE][100];
	string TrainingImagesArray[TRAINING_SIZE];
	string TestingImagesArray[TEST_SIZE];
	Coin training[TRAINING_SIZE];
	Coin test[TEST_SIZE];

	int x[IMAGE_SIZE_HEIGHT_MAX][IMAGE_SIZE_WIDTH_MAX] = { 0 };		//Stores the pixel values of the image
	int GLCM[MAX_SIZE][MAX_SIZE] = { 0 };							//corresponding GLCM matrix
	float p[MAX_SIZE][MAX_SIZE] = { 0 };							//Normalized Matrix

public:

	Haralick(int VS);

	//Runs the sequence of methods in order to successfully generate the test and train matrices
	void start(const char * path, bool console);

	//Extract Data from the text file and put into objects 
	void ExtractData(Coin *p, boolean t, const char *path, boolean console);

	//Extract the number of images in test/train folder and use the methods below to calc features and store in text file
	void extractFeatures(string *imagesArray, boolean t, const char * path, boolean console);

	//Set up the train and test matrices 
	void setUpMatrices(Coin *p, boolean t, int *tempLabels, float tempTrainingData[][100]);

	//Used to return the training and test matrices to the main
	void getMatrices(float tD[15][100], int l[15], float pD[10][100], int pl[15]);

	//Methods to obtain the actual Haralick Features:
	void calculateGLCM(int angle, int distance, int cols, int rows);
	float maxProb();
	float energy();
	float homogeneity();
	float contrast();
	float entropy();
	float correlation();
	float meani();
	float meanj();
	float deviationi();
	float deviationj();


};