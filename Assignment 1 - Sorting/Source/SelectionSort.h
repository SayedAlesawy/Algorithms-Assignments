#pragma once
#include "SortAlgo.h"

class SelectionSort : public SortAlgo
{
private:
	void SelectionSortImplementation(int* arr, int l, int r)
	{
		//For each position between [l, r-1) find the minimum element
		for (int i = l; i < r - 1; i++) {
			int MinimumIndex = i, MinimumValue = arr[i];

			//Search the minimum element that's supposed to be in position i
			for (int j = i + 1; j < r; j++) {
				if (arr[j] < MinimumValue) {
					MinimumValue = arr[j];
					MinimumIndex = j;
				}
			}

			//Place the element at its correct position
			swap(arr[i], arr[MinimumIndex]);
		}
	}

public:
	SelectionSort() {/* Empty */}

	double sort(int* arr, int l, int r)
	{
		//Run and calculate elapsed time
		start = high_resolution_clock::now();
		SelectionSortImplementation(arr, l, r);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};