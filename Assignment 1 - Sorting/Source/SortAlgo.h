#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std::chrono;
using namespace std;

class SortAlgo
{
protected:
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	duration<double> TimeElapsed;

public:
	SortAlgo() { /* Empty */}

	virtual double sort(int* arr, int l, int r) = 0;
};