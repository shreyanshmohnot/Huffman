/* Part4a - Team 5
Mr Mohnot & Mr Thomas
*/

#include "utility.h"
#include <map>

/* Function to read file into a string. Function arguments - filename to read from, string to write to. */
void readFile2(string filename, string& output) {
	ifstream myfile(filename, ifstream::in);
	char character = '+';
	while (myfile >> noskipws >> character) {
		output += character;
	}
	myfile.close();
}

/* Function to write to a file from a string. Function arguments - filename to write to & string to read from */
void writeFile2(string filename, string output) {
	ofstream myfile(filename, ofstream::trunc);
	int strsize = (int)output.length();
	for (int i = 0; i < strsize; i++) {
		myfile << output[i];
	}
	myfile.close();
}

/* Function to Built Map table for each codetable entry with huffman code mapped to each char. This function takes argument as input string containing the codetable entries and mapping each of them to characters building a type of dictionary. */
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

/* Function to decode message from the coded.txt into transparent english characters. */
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
	for (int i = 7; i >= 0; i--) {
		bool is_set = (c >> i) & 1;
		s += to_string(is_set);
	}
	return s;
}

int main() {
	string codeString = "";
	readFile2("codetable.txt", codeString);

	map<string, char> charCodes;
	buildDictionary(codeString, charCodes);

	// Part4a new:  read codedalt.txt and translate characters to binary
	fstream fin("codedalt.txt", fstream::in);
	char ch;
	string coded_new;
	while (fin >> noskipws >> ch) {
		coded_new.append(get_bits(ch));
	}

	// Decode binary to the original clear.txt
	string encodedString = "";
	decodeMessage(coded_new, encodedString, charCodes);

	// Write output
	writeFile2("decodedalt.txt", encodedString);
	cout << "Decoding complete. Close window.";
	system("pause");
	return 0;
}