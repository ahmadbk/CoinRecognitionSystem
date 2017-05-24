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
#include "Set.h"

using namespace std;
//R1 - 1
//R2 - 2
//R5 - 3
//R0.5 - 4
//R0.2 - 5
//R0.1 - 0


class Coin {

private:
	int value;
	string name;

public:

	Set coinData[8];

	string getName()
	{
		return name;
	}

	void setName(string n)
	{
		name = n;
	}

	int getValue()
	{
		return value;
	}

	void setValue(int v)
	{
		value = v;
	}
};