/*
Program 3
Yuanhoa Tao
Rich Lemke
Group 4
*/

#include "utility.h"
#include <queue>
#include <vector>
#include <list>

struct Node
{
	char character;
	int frequency;
	string code;
	struct Node* left;
	struct Node* right;

	Node(char character, int frequency) {
		left = NULL;
		right = NULL;
		this->character = character;
		this->frequency = frequency;
	}
};

struct comp {
	bool operator()(Node* left, Node* right) {
		return (left->frequency > right->frequency);
	}
};

bool alphaComp(pair<char, string> a, pair<char, string> b) {
	return ((int)a.first < (int)b.first);
}

/* Printing to file changed and removed ':' from the print values. */
void prettyPrint(list<pair<char, string>>& myList, ofstream& output) {
	while (myList.size() > 0) {
		pair<char, string> next = myList.front();
		// if (next.first == '*')
		/* Error 1 - Replace * with \n */
		if (next.first == '\n')
			output << "LF " << next.second << "\n";
		else
			output << next.first << " " << next.second << "\n";
		myList.pop_front();
	}
}

void createCodes(struct Node* tree, string code) {
	if (tree) {
		if (tree->character != '@')
			tree->code = code;
		createCodes(tree->left, code + "0");
		createCodes(tree->right, code + "1");
	}
}

void treeToQueue(struct Node* tree, list<pair<char, string>>& output) {
	if (tree) {
		if (tree->left) treeToQueue(tree->left, output);
		if (tree->right) treeToQueue(tree->right, output);
		if (tree->character != '@')
			output.push_front(make_pair(tree->character, tree->code));
	}
}

void reorder(struct Node* tree, list<pair<char, string>>& output) {
	treeToQueue(tree, output);
	output.sort(alphaComp);
}

void reduceTree(priority_queue<Node*, vector<Node*>, comp>& tree) {
	while (tree.size() != 1) {
		Node* left = tree.top();
		tree.pop();

		Node* right = tree.top();
		tree.pop();

		Node* top = new Node('@', left->frequency + right->frequency);
		top->left = left;
		top->right = right;
		tree.push(top);
	}
}

void readFile(int frequency[], char character[])
{
	fstream myfile("freq.txt", fstream::in);
	int count = 0;

	while (myfile >> noskipws >> character[count]) {
		if (character[count] == 'L') {
			char next = '*';
			myfile >> next;
			if (next == 'F') {
				// character[count] = '*';
				/* Error 1 - Replace * with \n */
				character[count] = '\n';
			}
		}
		int freq = 0;
		char num = ' ';
		while (num == ' ') {
			myfile >> noskipws >> num;
		}
		freq += num - '0';
		myfile >> noskipws >> num;
		while (num != '\n') {
			freq *= 10;
			freq += num - '0';
			myfile >> noskipws >> num;
		}
		frequency[count] = freq;
		count++;
	}
	myfile.close();
}

int abmain() {
	int frequency[50];
	char character[50];

	readFile(frequency, character);

	priority_queue<Node*, vector<Node*>, comp> tree;
	int i = 0;
	while (frequency[i] >= 0) {
		tree.push(new Node(character[i], frequency[i]));
		i++;
	}

	reduceTree(tree);
	createCodes(tree.top(), "");
	list<pair<char, string>> orderedOutput;
	reorder(tree.top(), orderedOutput);
	ofstream myOutput;
	myOutput.open("codetable.txt", ofstream::trunc);
	prettyPrint(orderedOutput, myOutput);
	myOutput.close();
	return 0;
}