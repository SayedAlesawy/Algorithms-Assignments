#include "SortingAlgos.h"
#include <ctime>
#include <chrono>
#include <ratio>
#include <fstream>
#include <sstream>

using namespace std::chrono;

double Sort(int* arr, int size, int algo)
{
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;

	if (algo == 0) {
		start = high_resolution_clock::now();
		SelectionSort(arr, 0, size);
		end = high_resolution_clock::now();
	}
	else if (algo == 1) {
		start = high_resolution_clock::now();
		InsertionSort(arr, 0, size);
		end = high_resolution_clock::now();
	}
	else if (algo == 2) {
		start = high_resolution_clock::now();
		MergeSort(arr, 0, size);
		end = high_resolution_clock::now();
	}
	else if (algo == 3) {
		start = high_resolution_clock::now();
		QuickSort(arr, 0, size);
		end = high_resolution_clock::now();
	}
	else if (algo == 4) {
		start = high_resolution_clock::now();
		HeapSort(arr, size);
		end = high_resolution_clock::now();
	}
	else {
		start = high_resolution_clock::now();
		TimSort(arr, size, 32);
		end = high_resolution_clock::now();
	}

	duration<double> ElapsedTime = duration_cast<duration<double>>(end - start);

	return ElapsedTime.count()*1000.0;
}

int main(int argc, char** argv)
{
	//Preparing input and output files.
	ifstream in;
	ofstream outarr, outstat;
	int AlgoIdentifier = 3;
	string InputFileName, OutputFileName, StatsFileName;

	//Extracting the first argument which is the algo to be used.
	stringstream ss(argv[1]);
	ss >> AlgoIdentifier;

	//Extracting the rest of the arguments
	InputFileName = argv[2];
	OutputFileName = argv[3];
	StatsFileName = argv[4];
	
	//Open input/output files
	in.open(InputFileName);
	outarr.open(OutputFileName);
	outstat.open(StatsFileName, ios_base::app);

	//Input Buffer
	int arr[500100], x, size = 0;

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
