/* Part3 - Team 5
Mr Mohnot & Mr Thomas
*/

#include "Utility.h"
#include <vector>
#include <map>
#include <sstream>

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

int main() {
	fstream file;
	file.open("codetable.txt", fstream::in);
	string line;
	map<string, string> codes; // map used to map character to huffman codes
	map <string, string> ::iterator itr; // iterator to the map
	while (getline(file, line))
	{
		if (line[0] == ' ') {
			string temp = to_string(stoi(line));
			codes.insert(pair <string, string>(" ", temp));
		}
		else {
			vector<string> sep = split(line, ' ');
			codes.insert(pair <string, string>(sep[0], sep[1]));
		}
	}
	file.close();

	// open clear.txt input file for converting to code
	file.open("clear.txt", fstream::in);

	// output codes to file
	ofstream myOutput;
	myOutput.open("coded.txt", ofstream::trunc);

	char singleCharacter;
	while (file.get(singleCharacter)) {
		string s(1, singleCharacter);
		if (singleCharacter == '\n')
			itr = codes.find("LF");
		else
			itr = codes.find(s);
		if (itr != codes.end())
			myOutput << itr->second;
		else
			cout << singleCharacter << " NOT FOUND" << endl;
	}
	file.close();
	myOutput.close();
	return 0;
}