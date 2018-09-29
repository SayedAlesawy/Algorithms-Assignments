#pragma once
#include "SortAlgo.h"

class QuickSort : public SortAlgo
{
private:
	int GetParitionIndex(int* arr, int l, int r)
	{
		int ParitionIndex = l, pivot = arr[r - 1];
		for (int j = l; j < r - 1; j++) {
			if (arr[j] <= pivot) {
				swap(arr[ParitionIndex], arr[j]);
				ParitionIndex++;
			}
		}
		swap(arr[ParitionIndex], arr[r - 1]);
		return ParitionIndex;
	}

	void QuickSortImplementation(int* arr, int l, int r)
	{
		if (r - l <= 1) return;
		int p = GetParitionIndex(arr, l, r);
		QuickSortImplementation(arr, l, p);
		QuickSortImplementation(arr, p, r);
	}

public:
	QuickSort() {/* Empty */ }

	double sort(int* arr, int l, int r)
	{
		start = high_resolution_clock::now();
		QuickSortImplementation(arr, l, r);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};