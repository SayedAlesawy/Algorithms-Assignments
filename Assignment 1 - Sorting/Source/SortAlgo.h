#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std::chrono;
using namespace std;

/*Base class for all algorithms*/

class SortAlgo
{
protected:
	/*Used to record the time elapsed for execution*/
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	duration<double> TimeElapsed;

public:
	SortAlgo() { /* Empty */}

	virtual double sort(int* arr, int l, int r) = 0;
};