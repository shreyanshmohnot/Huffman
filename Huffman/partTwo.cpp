#include "utility.h"

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
			// of << current->ch << " " << current->huffman << endl;
		// Check left nodes for null values
		if (current->left != NULL)
			Q.push(current->left);
		// Check right nodes for null values
		if (current->right != NULL)
			Q.push(current->right);
	}
	temp_list.sort(comp_ascii());

	for (list<Node*>::iterator current = temp_list.begin(); current != temp_list.end(); current++)
		of << (*current)->ch << " " << (*current)->huffman << "\n";
}