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

int arr1[N], arr2[N], BST1[2*N], BST2[2*N];

void BuildBST(int* arr, int size, int* BST)
{
	if (size == 0) return;

	stack<pair<int, int>>stk; 
	stk.push(make_pair(0, 0));
	BST[0] = arr[0];

	for (int i = 1; i < size; i++) {
		if (stk.empty()) break;
		while (stk.top().second == 2) {
			stk.pop();
			if (stk.empty()) break;
			stk.top().second++;
		}
		if (arr[i] == -1) {
			stk.top().second++;
		}
		else {
			int p = stk.top().first, f = stk.top().second, c = 0;
			if (f == 0) c = 2 * p + 1;
			else c = 2 * p + 2;
			BST[c] = arr[i];
			stk.push(make_pair(c, 0));
		}
	}
}

void PrintCommon()
{
	stack<pair<int, int>>stk1, stk2;
	int r1 = 0, r2 = 0;

	while (true) {
		if (BST1[r1] != -1) stk1.push(make_pair(r1, BST1[r1])), r1 = 2 * r1 + 1;
		else if (BST2[r2] != -1) stk2.push(make_pair(r2, BST2[r2])), r2 = 2 * r2 + 1;
		else if (!stk1.empty() && !stk2.empty()) {
			r1 = stk1.top().first;
			r2 = stk2.top().first;
			int val1 = stk1.top().second, val2 = stk2.top().second;
			if (val1 == val2) {
				outarr << val1;
				stk1.pop(); stk2.pop();
				r1 = 2 * r1 + 2;
				r2 = 2 * r2 + 2;
			}
			else if (val1 < val2) {
				stk1.pop();
				r1 = 2 * r1 + 2;
				r2 = 2 * N - 5;
			}
			else if (val2 < val1) {
				stk2.pop();
				r2 = 2 * r2 + 2;
				r1 = 2 * N - 5;
			}
		}
		else return;
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
	BuildBST(arr1, n, BST1);
	BuildBST(arr2, m, BST2);

	PrintCommon();

	end = high_resolution_clock::now();

	TimeElapsed = duration_cast<duration<double>>(end - start);

	return TimeElapsed.count()*1000.0;
}

int main(int argc, char** argv)
{
	string InputFileName, OutputFileName, StatsFileName;

	InputFileName = argv[1];
	OutputFileName = argv[2];
	StatsFileName = argv[3];

	//Open the files for input/output
	in.open(InputFileName);
	outarr.open(OutputFileName);
	outstat.open(StatsFileName);

	int n, m; 
	in >> n;
	for (int i = 0; i < n; i++) in >> arr1[i];
	in >> m;
	for (int i = 0; i < m; i++) in >> arr2[i];

	memset(BST1, -1, sizeof(BST1));
	memset(BST2, -1, sizeof(BST2));

	double ElapsedTime = RunSolution(n, m);
	
	//Output the to the stats file
	outstat << "Time taken: " << ElapsedTime << " ms." << endl;

	//int wait; cin >> wait;
}