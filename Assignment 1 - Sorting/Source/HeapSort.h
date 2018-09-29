#pragma once
#include "SortAlgo.h"

class HeapSort : public SortAlgo
{
private:
	void Heapify(int* arr, int size, int id)
	{
		int root = id, LeftChild = 2 * id + 1, RightChild = 2 * id + 2;

		if (LeftChild  < size && arr[LeftChild]  > arr[root]) root = LeftChild;
		if (RightChild < size && arr[RightChild] > arr[root]) root = RightChild;

		if (root != id) {
			swap(arr[id], arr[root]);
			Heapify(arr, size, root);
		}
	}

	void HeapSortImplementation(int* arr, int size)
	{
		for (int i = size / 2 - 1; i >= 0; i--) {
			Heapify(arr, size, i);
		}
		for (int i = size - 1; i >= 0; i--) {
			swap(arr[i], arr[0]);
			Heapify(arr, i, 0);
		}
	}

public:
	HeapSort() {/* Empty */ }

	double sort(int* arr, int l, int r)
	{
		start = high_resolution_clock::now();
		HeapSortImplementation(arr, r);
		end = high_resolution_clock::now();

		TimeElapsed = duration_cast<duration<double>>(end - start);
		return TimeElapsed.count()*1000.0;
	}
};