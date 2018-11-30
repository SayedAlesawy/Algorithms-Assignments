#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <string>
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

int dp[N][N], n; string str;

void solve()
{
	for (int i = 0; i < n; i++)
		dp[i][0] = dp[i][1] = 1;

	for (int len = 2; len <= n; len++) {
		for (int i = 0; i < n - len + 1; i++) {
			dp[i][len] = (str[i] == str[i + len - 1]) && dp[i + 1][len - 2];
		}
	}

	int start = 0, mx = 0;
	for (int len = 1; len <= n; len++) {
		for (int i = 0; i < n; i++) {
			if (dp[i][len]) {
				if (len > mx) {
					mx = len;
					start = i;
				}
			}
		}
	}

	outarr << mx << endl;
	outarr << str.substr(start, mx);
}

double RunSolution()
{
	//Intialize the needed vairables to benchmark
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	duration<double> TimeElapsed;

	//Put the function to test
	start = high_resolution_clock::now();

	solve();

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
	in >> str;

	double ElapsedTime = RunSolution();

	//Output the to the stats file
	outstat << "Time taken: " << ElapsedTime << " ms." << endl;

	//int wait; cin >> wait;
}