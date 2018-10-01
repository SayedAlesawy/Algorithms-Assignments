#pragma once
#include "SortAlgo.h"
#include <cstdlib>

class QuickSort : public SortAlgo
{
private:
	int GetParitionIndex(int* arr, int l, int r)
	{
		//Always takes the last element in the range as the pivot
		int ParitionIndex = l, pivot = arr[r - 1];
		for (int j = l; j < r - 1; j++) {
			//If an element is smaller than or equal to the pivot
			//Move it to the left half
			if (arr[j] <= pivot) {
				swap(arr[ParitionIndex], arr[j]);
				ParitionIndex++;
			}
		}

		//Place the pivot in its correct position and return it
		swap(arr[ParitionIndex], arr[r - 1]);

		return ParitionIndex;
	}

	int GetRandomParitionIndex(int* arr, int l, int r)
	{
		//Generate a random number in range [l, r)
		int ran = (rand() % (r - l)) + l;

		//Make the random number at last
		swap(arr[ran], arr[r - 1]);

		//Get the correct position of the pivot
		int p = GetParitionIndex(arr, l, r);

		return p;
	}

	void QuickSortImplementation(int* arr, int l, int r)
	{
		//Reached a leaf in the recursion tree
		if (r - l <= 1) return;
		
		int p = GetRandomParitionIndex(arr, l, r);

		QuickSortImplementation(arr, l, p); //Left  [l, p)
		QuickSortImplementation(arr, p, r); //Right [p, r)
	}

public:
	QuickSort() {/* Empty */ }

	double sort(int* arr, int l, int r)
	{
		//Run and calculate elapsed time
		start = high_resolution_clock::now();
		QuickSortImplementation(arr, l, r);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};