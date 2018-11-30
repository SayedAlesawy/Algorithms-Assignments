#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
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

int n, m, col, vis[N], ans[N], tmp[N];
vector<vector<int>>adj;

void dfs(int u)
{
	vis[u] = 1; int c = -1;
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (ans[v] != -1) tmp[ans[v]] = 1;
	}
	for (int i = 0; i <= col; i++) {
		if (!tmp[i]) {
			c = i;
			break;
		}
	}
	if (c == -1) c = ++col;
	ans[u] = c;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (!vis[v]) dfs(v);
	}
}

double RunSolution()
{
	//Intialize the needed vairables to benchmark
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	duration<double> TimeElapsed;

	//Put the function to test
	start = high_resolution_clock::now();

	dfs(0);

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

	in >> n >> m;
	
	memset(ans, -1, sizeof(ans));

	adj.resize(n);
	for (int i = 0; i < m; i++) {
		int u, v; in >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	double ElapsedTime = RunSolution();

	//outarr << col << endl;

	for (int i = 0; i < n; i++) outarr << i << " " << ans[i] << endl;

	//Output the to the stats file
	outstat << "Time taken: " << ElapsedTime << " ms." << endl;

	//int wait; cin >> wait;
}
