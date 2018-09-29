#pragma once
#include "SortAlgo.h"
#include "InsertionSort.h"
#include "MergeSort.h"

class TimSort : public SortAlgo
{
private:
	InsertionSort HelperInsertionSort;
	MergeSort HelperMergeSort;

	void TimSortImplementation(int* arr, int size, int BucketSize)
	{
		for (int i = 0; i < size; i += BucketSize) {
			HelperInsertionSort.sort(arr, i, min(i + BucketSize, size));
		}
		for (int i = BucketSize; i < size; i *= 2) {
			for (int j = 0; j < size; j += 2 * i) {
				int l = j, mid = min(j + i, size), r = min(j + 2 * i, size);
				HelperMergeSort.Merge(arr, l, mid, r);
			}
		}
	}

public:
	TimSort() { /* */}

	double sort(int* arr, int l, int r)
	{
		start = high_resolution_clock::now();
		TimSortImplementation(arr, l, r);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};