#pragma once
#include "SortAlgo.h"

/*A context class to execute the startegy design pattern*/

class Context
{
private:
	//A reference on the chosen algo (startegy) to be used.
	SortAlgo* StartegyExec;

public:
	Context (SortAlgo* Startegy) : StartegyExec(Startegy){ /* Empty */}

	double Execute(int* arr, int l, int r)
	{
		return StartegyExec->sort(arr, l, r);
	}
};