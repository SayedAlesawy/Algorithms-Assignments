#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <utility>
#include <cstring>
#include <fstream>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std;
using namespace std::chrono;

ifstream in;
ofstream outarr, outstat;

const int N = 100100;

int arr1[N], arr2[N], inorder1[N], inorder2[N], idx, it;
vector<int>common;

void buildInorderBST(int curr, int size, int* arr, int* inorder)
{
	if (idx == size) return;
	if (arr[idx] == -1) {
		idx++;
		return;
	}
	buildInorderBST(++idx, size, arr, inorder);
	inorder[it++] = arr[curr];
	buildInorderBST(idx, size, arr, inorder);
}

void GetCommon(int n, int m)
{
	int i = 0, j = 0;
	
	while (i < n && j < m) {
		if (inorder1[i] == inorder2[j]) {
			common.push_back(inorder1[i]);
			i++; j++;
		}
		else if (inorder1[i] < inorder2[j]) i++;
		else j++;
	}
}

double RunSolution(int n, int m)
{
	//Intialize the needed vairables to benchmark
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	duration<double> TimeElapsed;

	//Put the function to test
	start = high_resolution_clock::now();

	int tmp;
	buildInorderBST(0, n, arr1, inorder1);
	tmp = it; idx = 0, it = 0;
	buildInorderBST(0, m, arr2, inorder2);
	GetCommon(tmp, it);

	end = high_resolution_clock::now();

	TimeElapsed = duration_cast<duration<double>>(end - start);

	return TimeElapsed.count()*1000.0;
}

int main()
{
	string InputFileName, OutputFileName, StatsFileName;

	InputFileName = "input.txt";
	OutputFileName = "output.txt";
	StatsFileName = "time.txt";

	//Open the files for input/output
	in.open(InputFileName);
	outarr.open(OutputFileName);
	outstat.open(StatsFileName);

	int n, m; 

	in >> n;
	for (int i = 0; i < n; i++) in >> arr1[i];
	in >> m;
	for (int i = 0; i < m; i++) in >> arr2[i];

	double ElapsedTime = RunSolution(n, m);
	
	outarr << common.size() << endl;

	for (int i = 0; i < common.size(); i++) {
		outarr << common[i];
		if (i != common.size()) outarr << " ";
	}

	//Output the to the stats file
	outstat << "Time taken: " << ElapsedTime << " ms." << endl;
}