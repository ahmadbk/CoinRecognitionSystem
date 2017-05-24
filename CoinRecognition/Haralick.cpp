#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif 
#include"Haralick.h"

using namespace std;

Haralick::Haralick(int VS)
{
	VEC_SIZE = VS;
}

void Haralick::start(const char * path,bool console)
{
	cout << endl;
	std::cout << "Extracting Haralick Features..." << endl;

	std::cout << "Extracting Haralick Features for Training Data...";
	extractFeatures(TrainingImagesArray, 1, path, console);		//Extract Training Features
	cout << "DONE" << endl;

	std::cout << "Extracting Haralick Features for Test Data...";
	extractFeatures(TestingImagesArray, 0, path, console);		//Extract Testing Features
	cout << "DONE" << endl;

	std::cout << "Extract Training Haralick Features from textfile...";
	ExtractData(training, 1, path, console);					//Extract Data from train textfile
	cout << "DONE" << endl;
	std::cout << "Store Training Data in Matrices...";
	setUpMatrices(training, 1, labels, trainingData);			//Split data into appropriate training matrices
	cout << "DONE" << endl;

	std::cout << "Extract Test Features from textfile...";
	ExtractData(test, 0, path, console);						//Extract Data from test textfile
	cout << "DONE" << endl;
	std::cout << "Store Test Data in Matrices...";
	setUpMatrices(test, 0, pLabels, pData);						//Split data into appropriate test matrices
	cout << "Training and Test Matrices Created!" << endl << endl;
}

void Haralick::ExtractData(Coin *p, boolean t, const char *path, boolean console)
{
	std::ifstream file;
	string line;

	if (console)
	{
		string temp1;
		if (t)
			temp1 = "train.txt";
		else
			temp1 = "test.txt";

		string temp2(path);
		string temp3 = temp2 + temp1;
		file.open(temp3);
	}
	else
	{
		if (t)
			file.open("train.txt");
		else
			file.open("test.txt");
	}

	if (!file.is_open())
	{
		std::cout << "Failed To Open File";
	}
	else
	{
		int i = 0;
		int k = 0;

		while (getline(file, line))
		{
			char * line1 = &line[0];
			char *next_token1 = NULL;
			char *next_token2 = NULL;
			char *token1 = NULL;
			char *token2 = NULL;
			token1 = strtok_s(line1, ";", &next_token1);
			string imageName = token1;

			p[i].setName(imageName);

			if (imageName.find("50") != string::npos)
				p[i].setValue(4);
			else if (imageName.find("20") != string::npos)
				p[i].setValue(5);
			else if (imageName.find("10") != string::npos)
				p[i].setValue(0);
			else if (imageName.find("5") != string::npos)
				p[i].setValue(3);
			else if (imageName.find("2") != string::npos)
				p[i].setValue(2);
			else if (imageName.find("1") != string::npos)
				p[i].setValue(1);

			token1 = strtok_s(NULL, ";", &next_token1);

			while (token1 != NULL)
			{
				if (token1 != NULL)
				{
					token2 = strtok_s(token1, "#", &next_token2);//distance
					if (token2 != NULL)
						p[i].coinData[k].setDistance(atof(token2));

					token2 = strtok_s(NULL, "#", &next_token2);//orientation
					if (token2 != NULL)
						p[i].coinData[k].setOrientation(atof(token2));

					token2 = strtok_s(NULL, "#", &next_token2);//Max Probability
					if (token2 != NULL)
						p[i].coinData[k].f.setMaxProb(atof(token2));

					token2 = strtok_s(NULL, "#", &next_token2);//Energy
					if (token2 != NULL)
						p[i].coinData[k].f.setEnergy(atof(token2));

					token2 = strtok_s(NULL, "#", &next_token2);//Homogeneity
					if (token2 != NULL)
						p[i].coinData[k].f.setHomogeneity(atof(token2));

					token2 = strtok_s(NULL, "#", &next_token2);//Contrast
					if (token2 != NULL)
						p[i].coinData[k].f.setContrast(atof(token2));

					token2 = strtok_s(NULL, "#", &next_token2);//Correlation
					if (token2 != NULL)
						p[i].coinData[k].f.setCorrelation(atof(token2));

					token2 = strtok_s(NULL, "#", &next_token2);//Entropy
					if (token2 != NULL)
						p[i].coinData[k].f.setEntropy(atof(token2));

				}
				token1 = strtok_s(NULL, ";", &next_token1);
				k++;
			}
			k = 0;
			i++;
		}

		//for (int j = 0; j < 10; j++)
		//{
		//	cout << p[j].getName() << ":" << p[j].getValue() << endl;
		//	for (int k = 0; k < 8; k++)
		//	{
		//		cout << p[j].coinData[k].getDistance() << ":" << p[j].coinData[k].getOrientation() << ":";
		//		cout << p[j].coinData[k].f.getMaxProb() << ":" << p[j].coinData[k].f.getEnergy() << ":" << p[j].coinData[k].f.getHomogeneity() << ":" << p[j].coinData[k].f.getContrast() << ":" << p[j].coinData[k].f.getCorrelation() << ":" << p[j].coinData[k].f.getEntropy() << endl;
		//	}
		//	cout << endl;
		//}
	}

	file.close();

}

void Haralick::extractFeatures(string *imagesArray, boolean t, const char * path, boolean console)
{
	int size = 0;
	if (t)
		size = TRAINING_SIZE;
	else
		size = TEST_SIZE;

	//double duration;
	//std::clock_t start;

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

	int orientation[4] = { 0,45,90,135 };
	int distances[2] = { 1,3 };
	ofstream result;

	if (t)
		result.open("train.txt");
	else
		result.open("test.txt");

	cv::Mat imgOriginal;		// input image
	cv::Mat imgGrayscale;		// grayscale of input image
	cv::Mat finalImage;			//16-tone grayscae image
	cv::Mat hist_output;
	cv::Mat imgBlur;
	cv::Mat medBlur;
	cv::Mat gaussBlur;			// Gaussian Blur
	cv::Mat canny_output;
	cv::Mat sharp;

	//result << "ImageName;Distance#Orientation#MaxProbabilty#Energy#Homogeneity#Contrast#Correlation#Entropy;Distance#Orientation...\n";

	//Run the program for all the images found in the folder
	//------------------------------------------------------------------------------
	for (int w = 0; w < size; w++)
	{
		string imgName = imagesArray[w];

		result << imgName << ";";

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
		imgOriginal = cv::imread(path);								// open image

		if (imgOriginal.empty()) {									// if unable to open image
			std::cout << "error: image not read from file\n\n";		// show error message on command line
		}															//return(0);												// and exit program

		cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);		// convert to grayscale
		equalizeHist(imgGrayscale, hist_output);
		blur(hist_output, imgBlur, Size(10, 10));
		medianBlur(imgBlur, medBlur, 3);
		GaussianBlur(medBlur, gaussBlur, Size(5, 5), 1.5);
		sharp = 5 * (imgGrayscale - gaussBlur) + imgGrayscale;

		//Convert the grayscale image to 16-tone grayscal using lookup table
		//------------------------------------------------------------------------------
		uchar *p;
		cv::Mat lookuptable(1, 256, CV_8U);
		p = lookuptable.data;
		for (int i = 0; i < 256; ++i)
			p[i] = (i / 16);
		LUT(sharp, lookuptable, finalImage);

		for (int i = 0; i < finalImage.rows; i++)
		{
			for (int j = 0; j < finalImage.cols; j++)
			{
				int pixel = (int)(finalImage.at<uchar>(i, j));
				x[i][j] = pixel;
			}
		}
		//------------------------------------------------------------------------------

		//Calculate all features and store in textfile
		//------------------------------------------------------------------------------
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result << distances[i] << "#";
				//cout << "Distance: " << distances[i] << endl;
				result << orientation[j] << "#";
				//cout << "Orientation: " << orientation[j] << endl;

				calculateGLCM(orientation[j], distances[i], finalImage.cols, finalImage.rows);

				float t1 = maxProb();
				//cout << "Max Probability: " << t1 << endl;
				result << t1 << "#";

				float t2 = energy();
				//cout << "Energy: " << t2 << endl;
				result << t2 << "#";

				float t3 = homogeneity();
				//cout << "Homogeneity: " << t3 << endl;
				result << t3 << "#";

				float t4 = contrast();
				//cout << "Contrast: " << t4 << endl;
				result << t4 << "#";

				float t5 = correlation();
				//cout << "Correlation: " << t5 << endl;
				result << t5 << "#";

				float t6 = entropy();
				//cout << "Entropy: " << t6 << endl;
				result << t6;

				if (i != 1 || j != 3)
					result << ";";
				else
					result << "\n";
				//cout << endl;

			}
		}
		//------------------------------------------------------------------------------
	}
	//------------------------------------------------------------------------------

	result.close();
}

void Haralick::setUpMatrices(Coin *p, boolean t, int *tempLabels, float tempTrainingData[][100])
{
	int size = 0;
	if (t)
		size = TRAINING_SIZE;
	else
		size = TEST_SIZE;

	for (int i = 0; i < size; i++)
		tempLabels[i] = p[i].getValue();


	for (int i = 0; i < size; i++)
	{
		int k = 0;
		for (int j = 0; j < 8; j++)
		{
			tempTrainingData[i][k++] = p[i].coinData[j].f.getContrast();
			tempTrainingData[i][k++] = p[i].coinData[j].f.getCorrelation();
			tempTrainingData[i][k++] = p[i].coinData[j].f.getEnergy();
			tempTrainingData[i][k++] = p[i].coinData[j].f.getEntropy();
			tempTrainingData[i][k++] = p[i].coinData[j].f.getHomogeneity();
			tempTrainingData[i][k++] = p[i].coinData[j].f.getMaxProb();
		}
	}
}

void Haralick::getMatrices(float tD[15][100], int l[15], float pD[10][100], int pl[15])
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

void Haralick::calculateGLCM(int angle, int distance, int cols, int rows)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			int temp = 0;
			for (int k = 0; k < rows; k++)
			{
				for (int l = 0; l < cols; l++)
				{
					if (x[k][l] == i)
					{
						if (angle == 0)
						{
							if (l + distance < cols)
								if (x[k][l + distance] == j)
									temp += 1;

							if (l - distance >= 0)
								if (x[k][l - distance] == j)
									temp += 1;
						}
						if (angle == 45)
						{
							if (l + distance < cols && k - distance >= 0)
								if (x[k - distance][l + distance] == j)
									temp += 1;

							if (l - distance >= 0 && k + distance < rows)
								if (x[k + distance][l - distance] == j)
									temp += 1;
						}

						if (angle == 90)
						{
							if (k - distance >= 0)
								if (x[k - distance][l] == j)
									temp += 1;

							if (k + distance < rows)
								if (x[k + distance][l] == j)
									temp += 1;
						}

						if (angle == 135)
						{
							if (k - distance >= 0 && l - distance >= 0)
								if (x[k - distance][l - distance] == j)
									temp += 1;

							if (k + distance < rows && l + distance < cols)
								if (x[k + distance][l + distance] == j)
									temp += 1;
						}
					}
				}
			}
			GLCM[i][j] = temp;
		}
	}

	float total = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			total += GLCM[i][j];
		}
	}

	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			p[i][j] = (float)(GLCM[i][j] / total);
		}
	}
}

float Haralick::maxProb()
{
	float temp = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (p[i][j] > temp)
				temp = p[i][j];
		}
	}
	return temp;
}

float Haralick::energy()
{
	float total = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			total += p[i][j] * p[i][j];
		}
	}
	return total;
}

float Haralick::homogeneity()
{
	float temp = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			temp += p[i][j] / (1 + abs(i - j));
		}
	}
	return temp;
}

float Haralick::contrast()
{
	float temp = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			temp += p[i][j] * (abs(i - j))*(abs(i - j));
		}
	}
	return temp;
}

float Haralick::entropy()
{
	float temp = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (p[i][j] != 0)
				temp += p[i][j] * (-log(p[i][j]));
		}
	}
	return temp;
}

float Haralick::correlation()
{
	float mi = meani();
	float mj = meanj();
	float di = deviationi();
	float dj = deviationj();
	float total = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			float temp1 = i - mi;
			float temp2 = j - mj;
			float temp3 = di*dj;
			total += (p[i][j] * temp1 * temp2) / temp3;
		}
	}
	return total;
}

float Haralick::meani()
{
	float total = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			total += i*p[i][j];
		}
	}
	return total;
}

float Haralick::meanj()
{
	float total = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			total += j*p[i][j];
		}
	}
	return total;
}

float Haralick::deviationi()
{
	float mi = meani();
	float total = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			float temp = (i - mi)*(i - mi);
			total += p[i][j] * temp;
		}
	}
	return sqrt(total);
}

float Haralick::deviationj()
{
	float mj = meanj();
	float total = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			float temp = (j - mj)*(j - mj);
			total += p[i][j] * temp;
		}
	}
	return sqrt(total);
}

