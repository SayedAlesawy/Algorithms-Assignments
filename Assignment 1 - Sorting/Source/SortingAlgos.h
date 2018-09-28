#include<iostream>
#include <algorithm>
#include<vector>

using namespace std;

void SelectionSort(int* arr, int l, int r)
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

void InsertionSort(int* arr, int l, int r)
{
	for (int i = l + 1; i < r; i++) {
		int j = i - 1, temp = arr[i];
		for (; j >= l && temp < arr[j]; j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
	}
}

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

void MergeSort(int* arr, int l, int r)
{
	if (r - l <= 1) return;
	int mid = (l + r) / 2;
	MergeSort(arr, l, mid);
	MergeSort(arr, mid, r);
	Merge(arr, l, mid, r);
}

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

void QuickSort(int* arr, int l, int r)
{
	if (r - l <= 1) return;
	int p = GetParitionIndex(arr, l, r);
	QuickSort(arr, l, p);
	QuickSort(arr, p, r);
}

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

void HeapSort(int* arr, int size)
{
	for (int i = size / 2 - 1; i >= 0; i--) {
		Heapify(arr, size, i);
	}
	for (int i = size - 1; i >= 0; i--) {
		swap(arr[i], arr[0]);
		Heapify(arr, i, 0);
	}
}


void TimSort(int* arr, int size, int BucketSize)
{
	for (int i = 0; i < size; i += BucketSize) {
		InsertionSort(arr, i, min(i + BucketSize, size));
	}
	for (int i = BucketSize; i < size; i *= 2) {
		for (int j = 0; j < size; j += 2 * i) {
			int l = j, mid = min(j + i, size), r = min(j + 2 * i, size);
			Merge(arr, l, mid, r);
		}
	}
}