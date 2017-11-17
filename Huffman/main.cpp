#include "utility.h"

// Yuanhoa Tao
// Rich Lemke
// Group 4

int main(int argc, const char * argv[]) {

	char ch[10000];
	int char_count = 0;
	fstream myfile("clear.txt", fstream::in);
	
	while (myfile >> noskipws >> ch[char_count]) {
		char_count++;
	}
	myfile.close();

	int count[128] = { 0 };
	for (int i = 0; i<char_count; i++) {
		count[ch[i]]++;
	}

	//count numbers
	ofstream myOutput;
	myOutput.open("freq.txt", ofstream::trunc);
	for (int k = 0; k<128; k++) {
		if (count[k] != 0) {
			if (k == 10) myOutput << "LF " << count[k] << '\n';
			else myOutput << (char)(k) << " " << count[k] << '\n';
		}
	}
	myOutput.close();

	/*****Addition by TEAM 5 ****
	Mr. Thomas and Mr. Mohnot ***/

	// Linkedlist data structure for the frequency list
	list<Node*> freq_list;
	
	// read freq text file
	myfile.open("freq.txt", fstream::in);
	string line;
	
	// store nodes into list
	while (getline(myfile, line))
	{
		// store binary tree nodes into <list>
		if (line[0] == ' ') {
			Node *btree = newNode(" ", stoi(line));
			freq_list.push_back(btree);
		}
		else {
			vector<string> sep = split(line, ' ');
			Node *btree = newNode(sep[0], stoi(sep[1]));
			freq_list.push_back(btree);
		}
	}
	myfile.close();

	// sort the linkedlist with respect to frequency variables
	freq_list.sort(comp_freq());
	
	// while loop to build a huffman tree with reducing values
	while (freq_list.size() > 1) {
		// pop first two 
		Node *node1 = freq_list.front();
		freq_list.pop_front();
		Node *node2 = freq_list.front();
		freq_list.pop_front();

		// create new node
		struct Node *node3 = newNode("", node1->n + node2->n);
		node3->left = node1;
		node3->right = node2;

		// push new node into the linkedlist
		freq_list.push_front(node3);

		// resort the linkedlist
		freq_list.sort(comp_freq());
	}

	// get the first item from the linkedlist
	Node* root = freq_list.front();

	// depth-first traversal to perform huffman encoding on the linkedlist
	dfs(root, "");

	// output codes to file
	myOutput.open("codetable.txt", ofstream::trunc);
	
	// function to pop from the linkedlist and them display from the level inorder traversal
	LevelOrder(root, myOutput);
	myOutput.close();
	// output
	return 0;
}