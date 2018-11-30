#include<iostream>
#include<fstream>
#include<algorithm>
#include<set>
#include<vector>
#include<unordered_map>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std;
using namespace std::chrono;


int main(int argc, char** argv)
{
	ifstream in;
	ofstream outarr, outstat;

	string InputFileName, OutputFileName, StatsFileName;

	InputFileName = argv[1];
	OutputFileName = argv[2];
	StatsFileName = argv[3];

	//Open the files for input/output
	in.open(InputFileName);
	outarr.open(OutputFileName);
	outstat.open(StatsFileName);

	//Intialize the needed vairables to benchmark
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	duration<double> TimeElapsed;

	unordered_map<int, int>freq; //Stores the frequency of occurrence for each element.
	unordered_map<int, vector<int>>hashTable; //Stores a list for all element with certain ocurrence.
	vector<int>count; //Stores a list of all distinct counts

	//Read the input data and calculate the frequency
	int x = 0, size = 0;
	while (in >> x) {
		freq[x]++;
	}

	start = high_resolution_clock::now();

	//Build a hashtable to which the value is a list of all
	//Elements in the array the did occurr a certain number of times
	//i.e. arr = {2, 2, 1, 1, 4, 4, 4}, the hashtable will store smth like this
	//Key -> value
	//2 -> {2, 1}
	//3 -> {4}
	for (auto it = freq.begin(); it != freq.end(); it++) {
		hashTable[it->second].push_back(it->first);
	}

	//Get a list of all keys in the hashtable
	//Keys represents the distinct counts we have
	//i.e. count = {2, 3} in the previous example
	for (auto it = hashTable.begin(); it != hashTable.end(); it++) {
		count.push_back(it->first);
	}

	//Sort the keys descendingly
	sort(count.rbegin(), count.rend());

	//Sort each of the individual lists ascendingly
	for (auto it = hashTable.begin(); it != hashTable.end(); it++) {
		sort((it->second).begin(), (it->second).end());
	}

	//Now the hashtable looks smth like this
	//Key -> value
	//2 -> {1, 2}
	//3 -> {4}

	end = high_resolution_clock::now();
	TimeElapsed = duration_cast<duration<double>>(end - start);

	//Loop on the list keys (now sorted descendingly)
	//And for each key, output the corresponding element cnt number of times
	//Note, the time compelxity of the following is only O(n), since I am only outputing n elements
	for (int i = 0; i < count.size(); i++) {
		for (int j = 0; j < hashTable[count[i]].size(); j++) {
			for (int k = 0; k < count[i]; k++) {
				outarr << hashTable[count[i]][j] << endl;
			}
		}
	}

	double dur = TimeElapsed.count()*1000.0;

	//Output to the stats file
	outstat << "Time taken to sort the list = " << dur << " ms." << endl;

	//Total time complexity: O(n.lg(n))
	//Space complexity: O(k) where K is the number of distinct frequencies + the sizes of the hastables almost O(n)
}
