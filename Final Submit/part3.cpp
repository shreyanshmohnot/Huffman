#include "utility.h"
#include <map>

void readFile(string filename, string& output) {
	ifstream myfile(filename, ifstream::in);
	char character = '+';
	while (myfile >> noskipws >> character) {
		output += character;
	}
	myfile.close();
}

void writeFile(string filename, string output) {
	ofstream myfile(filename, ofstream::trunc);
	for(int i = 0; i < output.length(); i++) {
		myfile << output[i];
	}
	myfile.close();
}

void buildDictionary(string input, map<char, string>& dictionary) {
	char currentChar = '+';
	string currentString = "";
	bool readingChar = true;
	for (int i = 0; i < input.length(); i++) {
		if (!readingChar && input[i] == '\n') {
			readingChar = true;
			dictionary[currentChar] = currentString;
			currentString = "";
		}
		else if (!readingChar && input[i] == ' ') {
			readingChar = false;
		}
		else if (readingChar) {
			if (input[i] == 'L' &&
				(i + 1) < input.length() &&
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

void encodeMessage(string input, string& output, map<char, string> dictionary) {
	for (int i = 0; i < input.length(); i++) {
			output += dictionary[input[i]];
	}
}

void main() {
	string codeString = "";
	readFile("codetable.txt", codeString);

	map<char, string> charCodes;
	buildDictionary(codeString, charCodes);

	string encodedString = "";
	string message = "";
	readFile("clear.txt", message);
	encodeMessage(message, encodedString, charCodes);

	writeFile("coded.txt", encodedString);
	cout << "Encoding complete. Close window.";
	while (true);
}