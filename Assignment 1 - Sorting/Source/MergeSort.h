#pragma once
#include "SortAlgo.h"

class MergeSort : public SortAlgo
{
public:
	void Merge(int* arr, int l, int mid, int r)
	{
		//Calculate the sizes of the left and the right halves
		int LeftHalfSize = mid - l;  //[l, mid)
		int RightHalfSize = r - mid; //[mid, r)

		//Prepare aux. storage 
		vector<int> LeftHalf(LeftHalfSize), RightHalf(RightHalfSize);

		//Copy the two halves into the aux. storage
		for (int i = 0; i < LeftHalfSize; i++)
			LeftHalf[i] = arr[l + i];
		for (int i = 0; i < RightHalfSize; i++)
			RightHalf[i] = arr[mid + i];

		//Merge the two arrays until either of them ends
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

		//Copy the rest of the left half (if any)
		while (i < LeftHalfSize) {
			arr[k] = LeftHalf[i];
			k++; i++;
		}

		//Copy the rest of the right half (if any)
		while (j < RightHalfSize) {
			arr[k] = RightHalf[j];
			k++; j++;
		}
	}

private:
	void MergeSortImplementation(int* arr, int l, int r)
	{
		//Reached a leaf in the recursion tree
		if (r - l <= 1) return;

		int mid = (l + r) / 2;

		MergeSortImplementation(arr, l, mid); //[l, mid)
		MergeSortImplementation(arr, mid, r); //[mid, r)

		//Merge the two halves
		Merge(arr, l, mid, r);
	}


public:
	MergeSort() {/* Empty */ }

	double sort(int* arr, int l, int r)
	{
		//Run and calculate elapsed time
		start = high_resolution_clock::now();
		MergeSortImplementation(arr, l, r);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};