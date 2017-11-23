#include "utility.h"

// Yuanhoa Tao
// Rich Lemke
// Group 4

int acmain(int argc, const char * argv[]) {

	char ch[10000];
	int char_count = 0;
	fstream myfile("clear.txt", fstream::in);
	while (myfile >> noskipws >> ch[char_count]) {
		char_count++;
	}
	myfile.close();

	int count[128] = { 0 };
	for (int i = 0; i<char_count; i++) {
		count[ch[i]]++;
	}
	
	//count numbers
	ofstream myOutput;
	myOutput.open("freq.txt", ofstream::trunc);
	for (int k = 0; k<128; k++) {
		if (count[k] != 0) {
			if (k == 10) myOutput << "LF " << count[k] << '\n';
			else myOutput << (char)(k) << " " << count[k] << '\n';
		}
	}
	myOutput.close();
	//ouput
	return 0;
}