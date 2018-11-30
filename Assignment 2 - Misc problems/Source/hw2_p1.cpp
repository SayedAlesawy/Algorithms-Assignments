#include<iostream>
#include<fstream>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std;
using namespace std::chrono;

//The node structure that represents a linked list node
struct Node
{
	int data;
	Node* next;

	Node(int value) : data(value), next(NULL) {}
};

void add(int value, Node* &head)
{
	//Create the new node to be added
	Node* newNode = new Node(value);

	//Take a copy of the head pointer to use it for traversal
	Node* tmp = head;

	//If the linked list is empty, then add the new node at the front
	if (head == NULL) {
		head = newNode;
		return;
	}

	//Else, traverse to the end of the linked list and add it
	while (true) {
		if (tmp->next == NULL) {
			tmp->next = newNode;
			return;
		}
		tmp = tmp->next;
	}
}

//Time Complexity: O(n)
//Space Complexity: O(1) not considering the implicit recursion stack
//Not preferred, linear in the stack size (but cool :V)
Node* ReverseRecursive(Node* pre, Node* curr)
{
	//If the linked list is already empty
	if (curr == NULL) return NULL;

	//Base case, if the next node is the end node
	//Then start reversing edges and return the curr node
	//As it will be the new linked list head
	if (curr->next == NULL) {
		curr->next = pre;
		return curr;
	}

	//Keep going deeply to the end of the list
	Node* newHead = ReverseRecursive(curr, curr->next);
	curr->next = pre;

	return newHead;
}

//Time Complexity: O(n)
//Space Complexity: O(1)
Node* ReverseIterative(Node* head)
{
	//If the linked list is already empty
	if (head == NULL) return NULL;

	//Traverse the linked list using 2 pointers
	Node* curr = head;
	Node* prev = NULL;

	//If we didn't reach the end yet
	while (curr != NULL){
		//Will execute this everytime but the first
		if (prev != NULL) {
			//Save the next node, reverse the current node's pointer
			Node* temp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = temp;
		}
		else {
			//Executes only at the very first iteration, reverses the pointer
			//of the first node
			prev = curr;
			curr = curr->next;
			prev->next = NULL;
		}
	}

	//Return the new head
	return prev;
}

double RunSolution(Node* &head)
{
	//Intialize the needed vairables to benchmark
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
	duration<double> TimeElapsed;

	//Put the function to test
	start = high_resolution_clock::now();
	head = ReverseIterative(head);
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

	int x = 0, size = 0;
	Node* head = NULL;

	//Read the input data
	while (in >> x) {
		add(x, head);
		size++;
	}

	//Run the solution
	double ElapsedTime = RunSolution(head);
	
	//Output the reversed list
	Node* temp = head;
	while (temp != NULL) {
		outarr << temp->data << endl;
		temp = temp->next;
	}

	//Output the to the stats file
	outstat << "Time taken to reverse the list: " << ElapsedTime << " ms." << endl;
}