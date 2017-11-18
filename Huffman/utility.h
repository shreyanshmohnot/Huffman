#pragma once
#ifndef UTILITY_H
#define UTILITY_H

//Gives ANSI version of standard includes

#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <cctype>
#include <ctime>
#include <string>

// Added by Team 5 --
#include <vector>
#include <list>
#include <sstream>
#include <queue>

using namespace std;

/* Added by Team 5 */
// structure to create and store values in a tree like data structure
struct Node {
	string ch; // store character
	int n; // character count
	int ascii;
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

// strucutre to compare the frequency inside the list.
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

#endif //UTILITY_H