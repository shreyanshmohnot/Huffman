/* Part3 - Team 5
Mr Mohnot & Mr Thomas
*/

#include "Utility.h"
#include <vector>
#include <map>
#include <queue>
#include <list>
#include <sstream>

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

string decode(struct Node* root, string str) {
	string ans = "";
	struct Node *temp = root;
	for (int i = 0; i<str.size(); i++) {
		if (str[i] == '0')
			temp = temp->left;
		else
			temp = temp->right;
		if (!temp->left && !temp->right) { //reached leaf node
			ans = ans + temp->character;
			temp = root;
		}
	}
	return ans;
}

int main() {
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

	fstream file;
	file.open("codetable.txt", fstream::in);
	string line;
	map<string, string> codes; // map used to map character to huffman codes
	map <string, string> ::iterator itr; // iterator to the map
	while (getline(file, line))
	{
		if (line[0] == ' ') {
			string temp = to_string(stoi(line));
			codes.insert(pair <string, string> (" ", temp));
		}
		else {
			vector<string> sep = split(line, ' ');
			codes.insert(pair <string, string> (sep[0], sep[1]));
		}
	}
	file.close();

	// open clear.txt input file for converting to code
	file.open("clear.txt", fstream::in);
	
	// output codes to file
	ofstream out_file;
	out_file.open("coded.txt", ofstream::trunc);
	
	char singleCharacter;
	string encode;
	while (file.get(singleCharacter)) {
		string s(1, singleCharacter);
		if (singleCharacter == '\n')
			itr = codes.find("LF");
		else 
			itr = codes.find(s);
		if (itr != codes.end()) {
			out_file << itr->second;
			encode.append(itr->second);
		}
		else
			cout << singleCharacter << " NOT FOUND" << endl;
	}
	file.close();
	out_file.close();
	out_file.open("decoded.txt", ofstream::trunc);
	out_file << decode(tree.top(), encode);
	out_file.close();
	system("pause");
	return 0;
}