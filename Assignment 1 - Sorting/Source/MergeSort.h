#pragma once
#include "SortAlgo.h"

class MergeSort : public SortAlgo
{
public:
	void Merge(int* arr, int l, int mid, int r)
	{
		int LeftHalfSize = mid - l;
		int RightHalfSize = r - mid;
		vector<int> LeftHalf(LeftHalfSize), RightHalf(RightHalfSize);

		for (int i = 0; i < LeftHalfSize; i++)
			LeftHalf[i] = arr[l + i];
		for (int i = 0; i < RightHalfSize; i++)
			RightHalf[i] = arr[mid + i];

		int i = 0, j = 0, k = l;
		while (i<LeftHalfSize && j<RightHalfSize) {
			if (LeftHalf[i] <= RightHalf[j]) {
				arr[k] = LeftHalf[i];
				i++;
			}
			else {
				arr[k] = RightHalf[j];
				j++;
			}
			k++;
		}

		while (i < LeftHalfSize) {
			arr[k] = LeftHalf[i];
			k++; i++;
		}

		while (j < RightHalfSize) {
			arr[k] = RightHalf[j];
			k++; j++;
		}
	}

private:
	void MergeSortImplementation(int* arr, int l, int r)
	{
		if (r - l <= 1) return;
		int mid = (l + r) / 2;
		MergeSortImplementation(arr, l, mid);
		MergeSortImplementation(arr, mid, r);
		Merge(arr, l, mid, r);
	}


public:
	MergeSort() {/* Empty */ }

	double sort(int* arr, int l, int r)
	{
		start = high_resolution_clock::now();
		MergeSortImplementation(arr, l, r);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};