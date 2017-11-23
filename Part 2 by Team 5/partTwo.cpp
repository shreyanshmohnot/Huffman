/* Part Two by Team 5 - Mr. Thomas and Mr. Mohnot */

#include "utility.h"
#include <vector>
#include <list>
#include <sstream>
#include <queue>

// structure to create and store values in a tree like data structure
struct Node {
	string ch; // store character
	int n; // character count
	int ascii; //ASCII value
	string huffman = ""; // huffman code
	Node *left; // pointer to left subtree
	Node *right; // pointer to right subtree
};

// strucutre to compare the frequency inside the list.
struct comp_freq {
	bool operator()(Node* const a, Node* const b) {
		return a->n < b->n;
	}
};

// strucutre to compare the ascii inside the list.
struct comp_ascii {
	bool operator()(Node* const a, Node* const b) {
		return a->ascii < b->ascii;
	}
};

// function declarations for the partTwo.cpp
struct Node* newNode(string, int);
vector<string> split(string, char);
void dfs(Node*, string);
void LevelOrder(Node*, ofstream&);

int main(int argc, const char * argv[]) {
	
	// Linkedlist data structure for the frequency list
	list<Node*> freq_list;
	
	// read freq text file
	fstream myfile("freq.txt", fstream::in);
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
	ofstream myOutput;
	myOutput.open("codetable.txt", ofstream::trunc);
	
	// function to pop from the linkedlist and them write to output file from the level inorder traversal
	LevelOrder(root, myOutput);
	myOutput.close();
	// output
	return 0;
}

/* Function to create a new node of tree and returns pointer 
It takes argument as a string of characters and there frequency count.
Returns address value of a new node */
struct Node* newNode(string ch, int n) {
	struct Node* temp = new Node;
	temp->ch = ch;
	if (ch == "LF")
		temp->ascii = static_cast<int>(10);
	else
		temp->ascii = static_cast<int>((char)*(ch.c_str()));
	temp->n = n;
	temp->left = temp->right = NULL;
	return temp;
}

/* Function to split a string by delimiter character
This function takes argument a string to be modified and delimiter charcater on that string.
It returns the modified string */
vector<string> split(string str, char dlim) {
	vector<string> temp_string;
	stringstream sstr(str);
	string token;
	while (getline(sstr, token, dlim)) {
		temp_string.push_back(token);
	}
	return temp_string;
}

/* Depth-first traversal to add huffman codes with corresponding characters.
This function takes argument first as node and then huffman code. It returns NULL for no character else recursive. */
void dfs(Node *node, string huff_code) {
	if (node == NULL)
		return;
	node->huffman = node->huffman + huff_code;
	dfs(node->left, huff_code + "0");
	dfs(node->right, huff_code + "1");
}

/* Traverse binary search tree in level order and send to file.
This fuction takes argument root value of the list and the output file stream. */
void LevelOrder(Node *root, ofstream &of) {
	list<Node*> temp_list;
	if (root == NULL)
		return;
	// queue to get values from the list and traverse in Inorder.
	queue<Node*> Q;
	Q.push(root);
	// while there is at least one discovered node
	while (!Q.empty()) {
		Node* current = Q.front();
		Q.pop(); // removing the element at front
		// Check current node for null values
		if (current->ch != "")
			temp_list.push_back(current);
		// Check left nodes for null values
		if (current->left != NULL)
			Q.push(current->left);
		// Check right nodes for null values
		if (current->right != NULL)
			Q.push(current->right);
	}
	// sort the list according to the ascii values
	temp_list.sort(comp_ascii());

	// write the list container elements into the output put codetable.txt
	for (list<Node*>::iterator current = temp_list.begin(); current != temp_list.end(); current++)
		of << (*current)->ch << " " << (*current)->huffman << endl;
}