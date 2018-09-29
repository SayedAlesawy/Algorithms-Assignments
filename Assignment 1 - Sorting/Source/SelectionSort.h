#pragma once
#include "SortAlgo.h"

class SelectionSort : public SortAlgo
{
private:
	void SelectionSortImplementation(int* arr, int l, int r)
	{
		for (int i = l; i < r - 1; i++) {
			int MinimumIndex = i, MinimumValue = arr[i];
			for (int j = i + 1; j < r; j++) {
				if (arr[j] < MinimumValue) {
					MinimumValue = arr[j];
					MinimumIndex = j;
				}
			}
			swap(arr[i], arr[MinimumIndex]);
		}
	}

public:
	SelectionSort() {/* Empty */}

	double sort(int* arr, int l, int r)
	{
		start = high_resolution_clock::now();
		SelectionSortImplementation(arr, l, r);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};