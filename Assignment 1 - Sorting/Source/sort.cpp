#include "Context.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include "TimSort.h"
#include <fstream>
#include <sstream>

using namespace std::chrono;

double Sort(int* arr, int size, int algo)
{
	//Depending on the algo id, choose the required algo
	//Create an instance of the required algo
	//Mount the instance in the context obj
	//Execute the required startegy

	if (algo == 0) {
		SelectionSort selection;
		Context context(&selection);
		return context.Execute(arr, 0, size);
	}
	else if (algo == 1) {
		InsertionSort insertion;
		Context context(&insertion);
		return context.Execute(arr, 0, size);
	}
	else if (algo == 2) {
		MergeSort mergesort;
		Context context(&mergesort);
		return context.Execute(arr, 0, size);
	}
	else if (algo == 3) {
		QuickSort quick;
		Context context(&quick);
		return context.Execute(arr, 0, size);
	}
	else if (algo == 4) {
		HeapSort heapsort;
		Context context(&heapsort);
		return context.Execute(arr, 0, size);
	}
	else {
		TimSort timsort;
		Context context(&timsort);
		return context.Execute(arr, 0, size);
	}
}

int main()
{
	//Preparing input and output files.
	ifstream in;
	ofstream outarr, outstat;
	int AlgoIdentifier = 5;
	
	//Open input/output files
	in.open("input.txt");
	outarr.open("output.txt");
	outstat.open("stats.txt", ios_base::app);

	//Input Buffer
	int x, size = 0;
	int* arr = new int[500100];

	//Read the input file
	while (in >> x) {
		arr[size] = x;
		size++;
	}

	//Try the algorithm on unsorted data
	double ElpasedTimeUnsorted = Sort(arr, size, AlgoIdentifier);

	//Output the sorted data
	for (int i = 0; i < size; i++) outarr << arr[i] << endl;

	//Output the performance stats on sorting unsorted (random) data.
	outstat << size << "_unsorted: " << ElpasedTimeUnsorted << endl;

	//Try the algorithm on sorted data
	double ElpasedTimeSorted = Sort(arr, size, AlgoIdentifier);

	//Output the performance stats on sorting sorted data.
	outstat << size << "_sorted: " << ElpasedTimeSorted << endl;

	//Close the input/output files and terminate
	in.close(); outarr.close(); outstat.close();
}