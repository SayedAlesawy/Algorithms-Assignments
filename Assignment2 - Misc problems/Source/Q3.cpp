#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std;
using namespace std::chrono;

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

void MergeSort(int* arr, int l, int r)
{
	//In a bottom up manner, merge all subarrays of size 1, and then size 2, and then size 4, ..

	for (int size = 1; size < r; size *= 2) {
		//Loop on all subarrays of size = size
		for (int i = l; i < r; i += 2 * size) {
			//Determine the mid (end of the left half)
			//Determine the rr (end of the right half)
			int mid = min(i + size, r);
			int rr = min(mid + size, r);

			//Left half  = [l, mid)
			//right half = [mid, r)
			Merge(arr, i, mid, rr);
		}
	}
}

double RunSolution(int* arr, int l, int r)
{
	//Intialize the needed vairables to benchmark
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	duration<double> TimeElapsed;

	//Put the function to test
	start = high_resolution_clock::now();
	MergeSort(arr, l, r);
	end = high_resolution_clock::now();

	TimeElapsed = duration_cast<duration<double>>(end - start);

	return TimeElapsed.count()*1000.0;
}

/*
int main()
{
	ifstream in;
	ofstream outarr, outstat;

	//Open input/output files
	in.open("input1.txt");
	outarr.open("output1.txt");
	outstat.open("stats1.txt");

	int* arr = new int[500100];
	int x = 0, size = 0;

	//Read the input
	while (in >> x) {
		arr[size] = x;
		size++;
	}
	
	double ElapsedTime = RunSolution(arr, 0, size);

	//Output the sorted array
	for (int i = 0; i < size; i++)
		outarr << arr[i] << endl;

	//Output to the stats file
	outstat << "Time taken to sort the array = " << ElapsedTime << " ms." << endl;
}
*/