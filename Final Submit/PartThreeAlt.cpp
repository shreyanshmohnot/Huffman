/* Part3a - Team 5
Mr Mohnot & Mr Thomas
*/

#include "Utility.h"
#include <sstream>
#include <bitset>

int main() {

	// open coded.txt file for input to decode
	fstream file;
	file.open("coded.txt", fstream::in);
	string encode;
	getline(file, encode);
	file.close();

	// reading string in stream and setting the bits from the coded.txt values.
	stringstream sstream(encode);
	string output;
	while (sstream.good())
	{
		std::bitset<8> bits;
		sstream >> bits;
		char c = char(bits.to_ulong());
		output += c;
	}

	// output to codedalt.txt
	ofstream out("codedalt.txt", ofstream::trunc);
	out << output;
	out.close();
	system("pause");
	return 0;
}