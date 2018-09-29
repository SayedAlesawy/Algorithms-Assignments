#pragma once
#include "SortAlgo.h"

class Context
{
private:
	SortAlgo* StartegyExec;

public:
	Context (SortAlgo* Startegy) : StartegyExec(Startegy){ /* Empty */}

	double Execute(int* arr, int l, int r)
	{
		return StartegyExec->sort(arr, l, r);
	}
};