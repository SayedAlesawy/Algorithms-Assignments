#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <fstream>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std;
using namespace std::chrono;

ifstream in;
ofstream outarr, outstat;

unordered_map<int, vector<int>>adj;
int ans; unordered_map<int, int> vis;

void dfs(int u, int h)
{
	vis[u] = 1; ans = max(ans, h);
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (!vis[v]) dfs(v, h + 1);
	}
}

double RunSolution(int r)
{
	//Intialize the needed vairables to benchmark
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	duration<double> TimeElapsed;

	//Put the function to test
	start = high_resolution_clock::now();
	
	dfs(r, 0);

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

	int n, r;

	in >> n;

	for (int i = 0; i < n; i++) {
		int p; 
		in >> p;
		if (p == -1) { r = i; continue; }
		adj[p].push_back(i);
	}
	
	double ElapsedTime = RunSolution(r);

	outarr << ans;

	//Output the to the stats file
	outstat << "Time taken: " << ElapsedTime << " ms." << endl;

	//int wait; cin >> wait;
}