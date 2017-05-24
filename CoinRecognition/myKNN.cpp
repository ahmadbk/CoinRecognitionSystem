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
	//Mat matTrainFeatures(0, TRAINING_SIZE, CV_32F);
	//Mat matSample(0, TEST_SIZE, CV_32F);

	//Mat matTrainLabels(0, TRAINING_SIZE, CV_32F);
	//Mat matSampleLabels(0, TEST_SIZE, CV_32F);

	//Mat matResults(0, 0, CV_32F);

	const int class_count = 6;
	Mat train_data = Mat(TRAINING_SIZE, VEC_SIZE, CV_32FC1, &trainingData);
	Mat responses = Mat(TRAINING_SIZE, 1, CV_32S, &labels);

	Mat test_data = Mat(TEST_SIZE, VEC_SIZE, CV_32FC1, &pData);
	Mat test_responses = Mat(TEST_SIZE, 1, CV_32S, &pLabels);

	Ptr<TrainData> trainingData;
	Ptr<KNearest> kclassifier = KNearest::create();

	trainingData = TrainData::create(train_data,
		SampleTypes::ROW_SAMPLE, responses);

	kclassifier->setIsClassifier(true);
	kclassifier->setAlgorithmType(KNearest::Types::BRUTE_FORCE);
	kclassifier->setDefaultK(1);

	kclassifier->train(trainingData);

	kclassifier->findNearest(test_data, kclassifier->getDefaultK(), test_responses);


	cout << "Begin Prediction..." << endl;
	cout << "KNN Results..." << endl << endl;
	predict_display_results(kclassifier, filename_to_save);
	cout << endl << "KNN Prediction Done!" << endl << endl;

	return true;
}

void myKNN::predict_display_results(const Ptr<KNearest>& model, const string& filename_to_save)
{
	Mat test_data = Mat(TEST_SIZE, VEC_SIZE, CV_32FC1, &pData);
	Mat random[10][1];
	Mat p_responses = Mat(TEST_SIZE, 1, CV_32S, &random);
	model->findNearest(test_data, model->getDefaultK(), p_responses);

	float *data = (float *)(p_responses.data);
	
	for (int i = 0; i < TEST_SIZE; i++)
	{
		if (pLabels[i] == 1)
		{
			if (data[i] == 1)
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

float myKNN::getVal(int c)
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