#pragma once
#include "SortAlgo.h"

class InsertionSort : public SortAlgo
{
private:
	void InsertionSortImplementation(int* arr, int l, int r)
	{
		//Start from (l+1)th element and check if it's smaller than
		//Elements before it
		for (int i = l + 1; i < r; i++) {
			int j = i - 1, temp = arr[i];

			//If it's in fact smaller, then shift larger elements to the right
			for (; j >= l && temp < arr[j]; j--) {
				arr[j + 1] = arr[j];
			}

			//Place the element in its correct position
			arr[j + 1] = temp;
		}
	}

public:
	InsertionSort() {/* Empty */ }

	double sort(int* arr, int l, int r)
	{
		//Run and calculate elapsed time
		start = high_resolution_clock::now();
		InsertionSortImplementation(arr, l, r);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};