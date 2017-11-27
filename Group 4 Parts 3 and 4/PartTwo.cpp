/*
Program 3 Part 2
Team 3
Uslu and Xu
*/

#include "utility.h"
#include <list>

struct Node {
	string str;
	unsigned int count;
	Node *left;
	Node *right;

	Node(string str, unsigned int count) {
		this->str = str;
		this->count = count;
		left = NULL;
		right = NULL;
	}
};

bool compareNode(Node *x, Node *y) {
	return x->count < y->count;
}

void assignCode(Node *node, string code, string *codes) {
	if (node == NULL) {
		return;
	}
	assignCode(node->left, code + "0", codes);
	assignCode(node->right, code + "1", codes);
	
	if (node->str != "INTERNAL") {
		char chr;
		int c;
		if (node->str == "LF") {
			c = 10;
		}
		else {
			chr = node->str[0];
			c = static_cast<int>(chr);
		}
		codes[c] = code;
	}
	return;
}

int cmain() {
	//generate list of nodes
	list<Node*> frequencies;
	string inputfile = "freq.txt";

	ifstream ifile(inputfile);
	if (ifile) {
		string line, str;
		unsigned int delimiter, count;
		while (getline(ifile, line)) {
			delimiter = line.find(" ", 1);
			str = line.substr(0, delimiter);
			count = stoi(line.substr(delimiter + 1));

			Node *node = new Node(str, count);
			frequencies.push_back(node);
		}
	}

	//make the tree
	while (frequencies.size() > 1) {
		frequencies.sort(compareNode);

		//pop the first 2 items from the sorted list
		Node *left = frequencies.front();
		frequencies.pop_front();
		Node *right = frequencies.front();
		frequencies.pop_front();

		//make an internal mode
		Node *node = new Node("INTERNAL", left->count + right->count);
		node->left = left;
		node->right = right;
		frequencies.push_back(node);
	}

	//assign the codes
	Node *root = frequencies.front();
	string codes[128] = {};
	assignCode(root, "", codes);

	//write output file of frequencies as space-delimited output in ASCII order
	string outputfile = "codetable.txt";
	ofstream ofile(outputfile);

	if (ofile.is_open()) {
		for (int i = 0; i < 128; i++) {
			if (codes[i] != "") {
				if (i == 10) { //if new line character
					ofile << "LF " << codes[i] << endl;
				}
				else {
					ofile << static_cast<char>(i) << " " << codes[i] << endl;
				}
			}
		}
		ofile.close();
	}
	cout << "Wrote code table to output file: " << outputfile << endl;

	//ofile.close();

	system("pause");
	return 0;
}