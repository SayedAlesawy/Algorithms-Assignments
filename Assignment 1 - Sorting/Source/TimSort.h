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
		//Divide the range into buckets each of size 32 element
		for (int i = 0; i < size; i += BucketSize) {
			//Sort each bucket using insertion sort which is great with small datasets
			HelperInsertionSort.sort(arr, i, min(i + BucketSize, size));
		}

		//Merge buckets of sizes 32, 64, 128, etc.
		for (int i = BucketSize; i < size; i *= 2) {
			for (int j = 0; j < size; j += 2 * i) {
				//Pay attention to cases in which indices goes out of bounds (incomplete bucket)
				int l = j, mid = min(j + i, size), r = min(j + 2 * i, size);

				//[l, mid) and [mid, r)
				HelperMergeSort.Merge(arr, l, mid, r);
			}
		}
	}

public:
	TimSort() { /* */}

	double sort(int* arr, int l, int r)
	{
		//Run and calculate elapsed time
		start = high_resolution_clock::now();
		TimSortImplementation(arr, r, 32);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};