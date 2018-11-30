#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std;
using namespace std::chrono;

ifstream in;
ofstream outarr, outstat;

const int N = 1005;
long long dp[N][N][2]; int n, arr[N];

long long solve(int i, int j, int t)
{
	if (i >= j) return 0;
	long long& ret = dp[i][j][t];
	if (~ret) return ret;
	if (t) return ret = max(solve(i + 1, j, !t) + arr[i], solve(i, j - 1, !t) + arr[j]);
	else return ret = min(solve(i + 1, j, !t), solve(i, j - 1, !t));
}

double RunSolution()
{
	//Intialize the needed vairables to benchmark
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	duration<double> TimeElapsed;

	//Put the function to test
	start = high_resolution_clock::now();

	outarr << solve(0, n - 1, 1);

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

	in >> n;

	for (int i = 0; i < n; i++) in >> arr[i];
	memset(dp, -1, sizeof(dp)); 

	double ElapsedTime = RunSolution();

	//Output the to the stats file
	outstat << "Time taken: " << ElapsedTime << " ms." << endl;

	int wait; cin >> wait;
}