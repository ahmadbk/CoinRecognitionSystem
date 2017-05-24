#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif 
#include"NN.h"

using namespace std;

NN::NN(int VS, float tD[15][100], int l[15], float pD[10][100], int pl[15])
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

bool NN::train_mlp_classifier(const string& filename_to_save)
{
	const int class_count = 6;
	Mat train_data = Mat(TRAINING_SIZE, VEC_SIZE, CV_32FC1, &trainingData);
	Mat responses = Mat(TRAINING_SIZE, 1, CV_32S, &labels);

	Ptr<ANN_MLP> model;

	Mat train_responses = Mat::zeros(train_data.rows, class_count, CV_32F);

	// 1. unroll the responses
	cout << "Beginning Neural Network Classification..." << endl << endl;
	cout << "Unrolling the responses...\n";
	for (int i = 0; i < train_data.rows; i++)
	{
		int cls_label = responses.at<int>(i);
		train_responses.at<float>(i, cls_label) = 1.f;
	}

	// 2. train classifier
	//int layer_sz[] = { train_data.cols,5,class_count };
	int layer_sz[] = { train_data.cols,class_count };
	int nlayers = (int)(sizeof(layer_sz) / sizeof(layer_sz[0]));
	Mat layer_sizes(1, nlayers, CV_32S, layer_sz);

#if 1
	int method = ANN_MLP::BACKPROP;
	double method_param = 0.000001;
	int max_iter = 10000;
#else
	int method = ANN_MLP::RPROP;
	double method_param = 0.1;
	int max_iter = 1000;
#endif

	Ptr<TrainData> tdata = TrainData::create(train_data, ROW_SAMPLE, train_responses);

	cout << "Training the ANN classifier..." << endl;
	model = ANN_MLP::create();
	model->setLayerSizes(layer_sizes);
	model->setActivationFunction(ANN_MLP::SIGMOID_SYM, 0, 0);
	model->setTermCriteria(TC(max_iter, 0));
	model->setTrainMethod(method, method_param);
	model->train(tdata);
	//cout << endl;

	cout << "Begin Prediction..." << endl;
	cout << "Neural Network Results..." << endl << endl;
	predict_display_results(model, filename_to_save);
	cout << endl << "Neural Network Prediction Done!" << endl << endl;

	return true;
}

inline TermCriteria NN::TC(int iters, double eps)
{
	return TermCriteria(TermCriteria::MAX_ITER + (eps > 0 ? TermCriteria::EPS : 0), iters, eps);
}

void NN::predict_display_results(const Ptr<StatModel>& model, const string& filename_to_save)
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

	if (!filename_to_save.empty())
	{
		model->save(filename_to_save);
	}
}

float NN::getVal(int c)
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