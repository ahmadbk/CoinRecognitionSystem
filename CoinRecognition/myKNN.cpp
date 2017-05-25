#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif 
#include"myKNN.h"

using namespace std;

myKNN::myKNN(int VS, float tD[15][100], int l[15], float pD[10][100], int pl[15])
{
	VEC_SIZE = VS;
	for (int i = 0; i < TRAINING_SIZE; i++)
		for (int j = 0; j < VEC_SIZE; j++)
			trainingData[i][j] = tD[i][j];

	for (int i = 0; i < TEST_SIZE; i++)
		for (int j = 0; j < VEC_SIZE; j++)
			pData[i][j] = tD[i][j];

	for (int i = 0; i < TRAINING_SIZE; i++)
		labels[i] = l[i];

	for (int i = 0; i < TEST_SIZE; i++)
		pLabels[i] = pl[i];
}

bool myKNN::train_mlp_classifier(const string& filename_to_save)
{
	const int class_count = 6;
	Mat train_data = Mat(TRAINING_SIZE, VEC_SIZE, CV_32FC1, &trainingData);//Set up training data into Mat
	Mat responses = Mat(TRAINING_SIZE, 1, CV_32S, &labels);//Set up corresponding labels into Mat

	Ptr<TrainData> trainingData;
	Ptr<KNearest> kclassifier = KNearest::create();//Initialing KNearest neighbor classifier

	trainingData = TrainData::create(train_data,
		SampleTypes::ROW_SAMPLE, responses);//creating TrainData type using train data and corrsponding labels

	kclassifier->setIsClassifier(true);
	kclassifier->setAlgorithmType(KNearest::Types::BRUTE_FORCE);
	kclassifier->setDefaultK(1);

	kclassifier->train(trainingData);//Training the classifier

	//kclassifier->findNearest(test_data, kclassifier->getDefaultK(), test_responses);


	cout << "Begin Prediction..." << endl;
	cout << "KNN Results..." << endl << endl;
	predict_display_results(kclassifier, filename_to_save);
	cout << endl << "KNN Prediction Done!" << endl << endl;

	return true;
}

void myKNN::predict_display_results(const Ptr<KNearest>& model, const string& filename_to_save)
{
	Mat test_data = Mat(TEST_SIZE, VEC_SIZE, CV_32FC1, &pData);//Set up test data into a Mat
	Mat random[10][1];//Will store the result for one sample against all classes 
	Mat p_responses = Mat(TEST_SIZE, 1, CV_32S, &random);//redundant 
	model->findNearest(test_data, model->getDefaultK(), p_responses); //Using test data and labels to find nearest neighbours for each test sample
																	  //Distances stored in p_responses Mat

	float *data = (float *)(p_responses.data);//Conversion from Mat to float so the values can be accessed and used to compare more easily
	
	for (int i = 0; i < TEST_SIZE; i++)
	{
		if (pLabels[i] == 1)//original label of the test sample
		{
			if (data[i] == 1)//predicted label from the classifier
				std::cout << "Correct R1" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(data[i]) << "\n";
		}
		else if (pLabels[i] == 2)
		{
			if (data[i] == 2)
				std::cout << "Correct R2" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(data[i]) << "\n";
		}
		else if (pLabels[i] == 5)
		{
			if (data[i] == 5)
				std::cout << "Correct R0.2" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(data[i]) << "\n";
		}
		else if (pLabels[i] == 3)
		{
			if (data[i] == 3)
				std::cout << "Correct R5" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(data[i]) << "\n";
		}
		else if (pLabels[i] == 4)
		{
			if (data[i] == 4)
				std::cout << "Correct R0.5" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(data[i]) << "\n";
		}
		else if (pLabels[i] == 0)
		{
			if (data[i] == 0)
				std::cout << "Correct R0.1" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(data[i]) << "\n";
		}
	}

	//if (!filename_to_save.empty())
	//{
	//	model->save(filename_to_save);
	//}
}

float myKNN::getVal(int c)//converting label to the value in rands 
{
	switch (c)
	{
	case 0: return 0.1;
		break;
	case 1: return 1;
		break;
	case 2: return 2;
		break;
	case 3: return 5;
		break;
	case 4: return 0.5;
		break;
	case 5: return 0.2;
		break;
	}
}