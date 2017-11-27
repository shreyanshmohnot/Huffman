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

void main() {
	string codeString = "";
	readFile2("codetable.txt", codeString);

	map<string, char> charCodes;
	buildDictionary(codeString, charCodes);

	string encodedString = "";
	string message = "";
	readFile2("coded.txt", message);
	decodeMessage(message, encodedString, charCodes);

	writeFile2("decoded.txt", encodedString);
	cout << "Decoding complete. Close window.";
	while (true);
}