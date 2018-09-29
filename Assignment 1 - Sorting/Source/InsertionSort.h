#pragma once
#include "SortAlgo.h"

class InsertionSort : public SortAlgo
{
private:
	void InsertionSortImplementation(int* arr, int l, int r)
	{
		for (int i = l + 1; i < r; i++) {
			int j = i - 1, temp = arr[i];
			for (; j >= l && temp < arr[j]; j--) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}
	}

public:
	InsertionSort() {/* Empty */ }

	double sort(int* arr, int l, int r)
	{
		start = high_resolution_clock::now();
		InsertionSortImplementation(arr, l, r);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};