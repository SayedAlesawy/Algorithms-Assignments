#include<iostream>
#include<stack>
#include<algorithm>
#include<fstream>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std;
using namespace std::chrono;

//Represent a monotonic queue node
//each node stores the value that was pushed in the stack
//And the min value so far
struct Node
{
	int val, min;

	Node(int v, int mn) : val(v), min(mn){}
};

struct MonotonicQueue
{
	//Monotonic queue is implemeneted using 2 stacks
	//We only push new entries in stack1 and pop old entries from stack2
	stack<Node>st1, st2;

	void mpush(int val)
	{
		//Create a new node
		Node node(val, val);

		//If the first stack is not empty, update the minimum value
		if (!st1.empty()) 
			node.min = min(node.min, st1.top().min);
		
		//Then push in the first stack
		st1.push(node);
	}

	void mpop()
	{
		//If the second stack is not empty, then simply pop from it
		if (!st2.empty()) st2.pop();
		else {
			//If it's empty, this means we need to flip all entries from stack 1
			//Into stack 2, to get the bottom element in stack 1 to become the top
			//Element stack 2 and thus easily remove it

			//First, pop a node from stack 1, and update it's min value
			//Note that the min value represents the min so far, so if it's going to be
			//The only the value in the second stack, then the min equals that value for now
			Node temp = st1.top();
			temp.min = temp.val;
			st2.push(temp);
			st1.pop();

			while (!st1.empty()) {
				//Pop nodes from stack, push them in stack 2 and update the min
				Node temp = st1.top();
				temp.min = min(temp.val, st2.top().min);
				st2.push(temp);
				st1.pop();
			}

			//Finally pop the desired element, now on top of stack 2, so easily poped
			st2.pop();
		}
	}

	int getMin()
	{
		int mn = INT_MAX;

		//The min value is the min(top of stack 1, top of stack 2)
		if (!st1.empty()) mn = min(mn, st1.top().min);
		if (!st2.empty()) mn = min(mn, st2.top().min);

		return mn;
	}
};

void GetMinSubarray(int* A, int* B, int k, int size)
{
	MonotonicQueue mq; int idx = 0;

	//Push k-1 element from the current window into the monotonic queue
	for (int i = 0; i < k - 1; i++) 
		mq.mpush(A[i]);

	for (int i = k - 1; i < size; i++) {
		//Push the kth element from the window in the monotonic queue
		mq.mpush(A[i]);

		//Get the minimum value in the current window is O(1) and insert into B
		B[idx] = mq.getMin();
		idx++;

		//Pop the first element in the current window, and slide the window 1 position to the left
		mq.mpop();
	}
}

double RunSolution(int* A, int* B, int k, int size)
{
	//Intialize the needed vairables to benchmark
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	duration<double> TimeElapsed;

	//Put the function to test
	start = high_resolution_clock::now();
	GetMinSubarray(A, B, k, size);
	end = high_resolution_clock::now();

	TimeElapsed = duration_cast<duration<double>>(end - start);

	return TimeElapsed.count()*1000.0;
}


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

	//Read the input, k goes first
	int* A = new int[100100];
	int k, x, size = 0;

	in >> k;

	while (in >> x) {
		A[size] = x;
		size++;
	}

	//In n element, we have only n-k+1 sliding windows of size k
	int* B = new int[size - k + 1];

	double ElapsedTime = RunSolution(A, B, k, size);

	//Output B
	for (int i = 0; i < size - k + 1; i++)
		outarr << B[i] << endl;

	//Output to the stats file
	outstat << "Subarray found in = " << ElapsedTime << " ms." << endl;

	//Time complexity:  O(n)
	//Space complexity: O(n) "Auxiallary stacks"
}