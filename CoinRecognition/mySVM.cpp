#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif 
#include"mySVM.h"

using namespace std;

mySVM::mySVM(int VS, float tD[15][100], int l[15], float pD[10][100], int pl[15])
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

bool mySVM::train_mlp_classifier(const string& filename_to_save)
{
	const int class_count = 6;
	Mat train_data = Mat(TRAINING_SIZE, VEC_SIZE, CV_32FC1, &trainingData);
	Mat responses = Mat(TRAINING_SIZE, 1, CV_32S, &labels);

	Ptr<ml::SVM> svm = ml::SVM::create();

	//set the parameters of the SVM
	svm->setType(ml::SVM::C_SVC);
	svm->setKernel(ml::SVM::LINEAR);
	CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-10);
	svm->setTermCriteria(criteria);

	svm->train(train_data, ml::ROW_SAMPLE, responses);

	cout << endl << endl;
	std::cout << "Begin Predicting using Support Vector Machines..." << endl << endl;
	predict_display_results(svm, filename_to_save);
	cout << endl << "SVM Prediction Done!" << endl << endl;

	return true;
}

void mySVM::predict_display_results(const Ptr<StatModel>& model, const string& filename_to_save)
{
	Mat pdata = Mat(TEST_SIZE, VEC_SIZE, CV_32FC1, &pData);   //Loading the rest of the data for prediction
	int i, nsamples_all = pdata.rows;

	for (i = 0; i < nsamples_all; i++)
	{
		Mat sample = pdata.row(i);
		float r = model->predict(sample);
		if (pLabels[i] == 1)
		{
			if (r == 1)
				std::cout << "Correct R1" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(r) << "\n";
		}
		else if (pLabels[i] == 2)
		{
			if (r == 2)
				std::cout << "Correct R2" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(r) << "\n";
		}
		else if (pLabels[i] == 5)
		{
			if (r == 5)
				std::cout << "Correct R0.2" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(r) << "\n";
		}
		else if (pLabels[i] == 3)
		{
			if (r == 3)
				std::cout << "Correct R5" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(r) << "\n";
		}
		else if (pLabels[i] == 4)
		{
			if (r == 4)
				std::cout << "Correct R0.5" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(r) << "\n";
		}
		else if (pLabels[i] == 0)
		{
			if (r == 0)
				std::cout << "Correct R0.1" << "\n";
			else
				std::cout << "Incorrect: Expected-R" << getVal(pLabels[i]) << "\tPredicted-R" << getVal(r) << "\n";
		}
	}

	//if (!filename_to_save.empty())
	//{
	//	model->save(filename_to_save);
	//}
}

float mySVM::getVal(int c)
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