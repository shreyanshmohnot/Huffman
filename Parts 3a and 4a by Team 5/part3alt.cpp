/* Part3a - Team 5
Mr Mohnot & Mr Thomas
*/

#include "Utility.h"
#include <sstream>
#include <bitset>

int main() {

	fstream file;

	// open coded.txt file for input to decode
	file.open("coded.txt", fstream::in);
	string encode;
	getline(file, encode);
	file.close();

	stringstream sstream(encode);
	string output;
	while (sstream.good())
	{
		std::bitset<8> bits;
		sstream >> bits;
		char c = char(bits.to_ulong());
		output += c;
	}

	ofstream out("codedalt.txt");
	out << output;
	out.close();

	system("pause");
	return 0;
}