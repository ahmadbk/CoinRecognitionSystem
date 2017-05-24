#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif 
#include"myMoments.h"

using namespace std;

myMoments::myMoments(int VS)
{
	VEC_SIZE = VS;
}

void myMoments::start(const char * path, bool console)
{
	cout << endl << endl;
	std::cout << "Extracting Hu Moments for Training Data..." << endl;
	extractHuMoments(TrainingImagesArray, 1, path, console);		//Extract Training Features
	extractHuMoments(TestingImagesArray, 0, path, console);
	cout << "Training and Test Matrices Created!" << endl << endl;
}

void myMoments::extractHuMoments(string *imagesArray, boolean t, const char * path, boolean console)
{
	int size = 0;
	if (t)
		size = TRAINING_SIZE;
	else
		size = TEST_SIZE;

	int orientation[4] = { 0,45,90,135 };
	int distances[2] = { 1,3 };

	char* imageFilePath;
	char* temp4;
	if (console)
	{
		string temp1;
		if (t)
			temp1 = "train/*";
		else
			temp1 = "test/*";

		string temp2(path);
		string temp3 = temp2 + temp1;
		temp4 = new char[temp3.length() + 1];
		string temp5(temp4);
		strcpy_s(temp4, temp5.length(), temp3.c_str());
		imageFilePath = temp4;
		delete temp4;
	}
	else
	{
		if (t)
			imageFilePath = "train/*";	//path to all the train images
		else
			imageFilePath = "test/*";	//path to all the test images
	}

	string temp(imageFilePath);
	string imagePath = temp.substr(0, (temp.length() - 2));

	//Obtain the names of all the images in the filepath
	//------------------------------------------------------------------------------
	WIN32_FIND_DATA search_data;
	memset(&search_data, 0, sizeof(WIN32_FIND_DATA));
	HANDLE handle = FindFirstFile(imageFilePath, &search_data);
	int count = 0;
	while (handle != INVALID_HANDLE_VALUE)
	{
		if (count > 1)
			imagesArray[count - 2] = search_data.cFileName;
		count++;
		if (FindNextFile(handle, &search_data) == FALSE)
			break;
	}
	FindClose(handle);
	//------------------------------------------------------------------------------

	//Run the program for all the images found in the folder
	//------------------------------------------------------------------------------

	for (int w = 0; w < size; w++)
	{
		string imgName = imagesArray[w];
		string imagePathl;

		if (console)
		{
			string temp1;
			if (t)
				temp1 = "train/";
			else
				temp1 = "test/";

			string temp(path);
			string temp3 = temp + temp1;
			//imagePath = temp.substr(0, (temp.length() - 2));
			imagePath = temp3;
		}
		else
		{
			if (t)
				imagePath = "train/";
			else
				imagePath = "test/";
		}

		string path = imagePath + imgName;

		cv::Mat imgOriginal;										// input image
		cv::Mat imgGrayscale;										// grayscale of input image
	cv:Mat imgGrayScaleNew;
		cv::Mat gaussBlur;											// Gaussian Blur
		cv::Mat canny_output;

		imgOriginal = cv::imread(path);								// open image
		if (imgOriginal.empty()) {									// if unable to open image
			std::cout << "error: image not read from file\n\n";		// show error message on command line
		}
		cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);		// convert to grayscale

																	//uchar *p1;
																	//cv::Mat lookuptable(1, 256, CV_8U);
																	//p1 = lookuptable.data;
																	//for (int i = 0; i < 256; ++i)
																	//	p1[i] = (i / 16);
																	//LUT(imgGrayscale, lookuptable, imgGrayScaleNew);

		GaussianBlur(imgGrayscale, gaussBlur, Size(5, 5), 1.5);
		Canny(gaussBlur, canny_output, 50, 150, 3);

		//namedWindow("Canny", WINDOW_AUTOSIZE);
		//imshow("Canny", canny_output);

		Moments mp;
		mp = moments(canny_output, true);
		double hu[7] = { 0 };
		HuMoments(mp, hu);

		if (t)
		{
			for (int i = 0; i < 7; i++)
			{
				trainingData[w][i] = hu[i] < 0 ? (-1)*log10(abs(hu[i])) : log10(abs(hu[i]));
			}
		}
		else
		{
			for (int i = 0; i < 7; i++)
			{
				pData[w][i] = hu[i];
			}
		}

		if (t)
		{
			if (imgName.find("50") != string::npos)
				labels[w] = 4;
			else if (imgName.find("20") != string::npos)
				labels[w] = 5;
			else if (imgName.find("10") != string::npos)
				labels[w] = 0;
			else if (imgName.find("5") != string::npos)
				labels[w] = 3;
			else if (imgName.find("2") != string::npos)
				labels[w] = 2;
			else if (imgName.find("1") != string::npos)
				labels[w] = 1;
		}
		else
		{
			if (imgName.find("50") != string::npos)
				pLabels[w] = 4;
			else if (imgName.find("20") != string::npos)
				pLabels[w] = 5;
			else if (imgName.find("10") != string::npos)
				pLabels[w] = 0;
			else if (imgName.find("5") != string::npos)
				pLabels[w] = 3;
			else if (imgName.find("2") != string::npos)
				pLabels[w] = 2;
			else if (imgName.find("1") != string::npos)
				pLabels[w] = 1;
		}
	}
}

void myMoments::getMatrices(float tD[15][100], int l[15], float pD[10][100], int pl[15])
{
	for (int i = 0; i < TRAINING_SIZE; i++)
		for (int j = 0; j < VEC_SIZE; j++)
			tD[i][j] = trainingData[i][j];

	for (int i = 0; i < TEST_SIZE; i++)
		for (int j = 0; j < VEC_SIZE; j++)
			pD[i][j] = pData[i][j];

	for (int i = 0; i < TRAINING_SIZE; i++)
		l[i] = labels[i];

	for (int i = 0; i < TEST_SIZE; i++)
		pl[i] = pLabels[i];
}

