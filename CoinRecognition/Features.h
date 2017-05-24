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

using namespace std;

class Features {

private:
	float maxProb;
	float energy;
	float homogeneity;
	float contrast;
	float entropy;
	float correlation;

public:

	float getMaxProb()
	{
		return maxProb;
	}

	float getEnergy()
	{
		return energy;
	}

	float getHomogeneity()
	{
		return homogeneity;
	}

	float getContrast()
	{
		return contrast;
	}

	float getEntropy()
	{
		return entropy;
	}

	float getCorrelation()
	{
		return correlation;
	}

	void setMaxProb(float m)
	{
		maxProb = m;
	}

	void setEnergy(float e)
	{
		energy = e;
	}

	void setHomogeneity(float h)
	{
		homogeneity = h;
	}

	void setContrast(float c)
	{
		contrast = c;
	}

	void setEntropy(float e)
	{
		entropy = e;
	}

	void setCorrelation(float c)
	{
		correlation = c;
	}

};