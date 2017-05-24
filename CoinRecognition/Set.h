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
#include "Features.h"

using namespace std;

class Set {

private:
	float distance;
	float orientation;

public:

	Features f;

	float getDistance()
	{
		return distance;
	}

	float getOrientation()
	{
		return orientation;
	}

	void setDistance(float d)
	{
		distance = d;
	}

	void setOrientation(float o)
	{
		orientation = o;
	}

};