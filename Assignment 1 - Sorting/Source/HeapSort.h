#pragma once
#include "SortAlgo.h"

class HeapSort : public SortAlgo
{
private:
	void Heapify(int* arr, int size, int id)
	{
		int root = id, LeftChild = 2 * id + 1, RightChild = 2 * id + 2;

		//Makes sure that the parent is larger than both children. 
		//Also handle cases in which children indices go out of bounds
		if (LeftChild  < size && arr[LeftChild]  > arr[root]) root = LeftChild;
		if (RightChild < size && arr[RightChild] > arr[root]) root = RightChild;

		//If the root is not correct, then correct it and heapify
		if (root != id) {
			//Makes the parent larger than its children
			swap(arr[id], arr[root]);

			//Heapify my subtree
			Heapify(arr, size, root);
		}
	}

	void HeapSortImplementation(int* arr, int size)
	{
		//Use half of the array, so as not to go out of bounds when calculating 2*id+1 and 2*id+2
		for (int i = size / 2 - 1; i >= 0; i--) {
			Heapify(arr, size, i);
		}

		for (int i = size - 1; i >= 0; i--) {
			//Each iteration, swap the top element (largest) with a leaf element
			swap(arr[i], arr[0]);

			//And then heapify while shrinking the size of the heap by one to account for the
			//Taken element
			Heapify(arr, i, 0);
		}
	}

public:
	HeapSort() {/* Empty */ }

	double sort(int* arr, int l, int r)
	{
		//Run and calculate elapsed time
		start = high_resolution_clock::now();
		HeapSortImplementation(arr, r);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};