/* Part4a - Team 5
Mr Mohnot & Mr Thomas
*/


#include "utility.h"
#include <map>

void readFile2(string filename, string& output) {
	ifstream myfile(filename, ifstream::in);
	char character = '+';
	while (myfile >> noskipws >> character) {
		output += character;
	}
	myfile.close();
}

void writeFile2(string filename, string output) {
	ofstream myfile(filename, ofstream::trunc);
	int strsize = (int)output.length();
	for (int i = 0; i < strsize; i++) {
		myfile << output[i];
	}
	myfile.close();
}

void buildDictionary(string input, map<string, char>& dictionary) {
	char currentChar = '+';
	string currentString = "";
	bool readingChar = true;
	int strsize = (int)input.length();
	for (int i = 0; i < strsize; i++) {
		if (!readingChar && input[i] == '\n') {
			readingChar = true;
			dictionary[currentString] = currentChar;
			currentString = "";
		}
		else if (!readingChar && input[i] == ' ') {
			readingChar = false;
		}
		else if (readingChar) {
			int strsize = (int)input.length();
			if (input[i] == 'L' &&
				(i + 1) < strsize &&
				input[i + 1] == 'F') {
				currentChar = '\n';
				i++;
			}
			else currentChar = input[i];
			readingChar = false;
		}
		else {
			currentString += input[i];
		}
	}
}

void decodeMessage(string input, string& output, map<string, char> dictionary) {
	string currentString = "";
	int strsize = (int)input.length();
	for (int i = 0; i < strsize; i++) {
		currentString += input[i];
		if (dictionary.find(currentString) != dictionary.end()) {
			output += dictionary[currentString];
			currentString = "";
		}
	}
}

/* Function to decode a character into ascii bits*/
string get_bits(char c) {
	string s;
	for (int i = 8; i--> 0;) {
		bool is_set = c & (1 << i);
		s += to_string(is_set);
	}
	return s;
}

void main() {
	string codeString = "";
	readFile2("codetable.txt", codeString);

	map<string, char> charCodes;
	buildDictionary(codeString, charCodes);

	// Part4a new:  read codedalt.txt and translate characters to binary
	fstream fin("codedalt.txt", fstream::in);
	char ch;
	string coded_new;
	while (fin >> noskipws >> ch) {
		coded_new += get_bits(ch);
	}

	// Decode binary to the original clear.txt
	string encodedString = "";
	decodeMessage(coded_new, encodedString, charCodes);

	// Write output
	writeFile2("decodedalt.txt", encodedString);
	cout << "Decoding complete. Close window.";
	while (true);
}