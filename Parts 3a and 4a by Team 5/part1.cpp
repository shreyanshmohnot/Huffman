/*
Program 3 Part 1
Team 3
Uslu and Xu
*/
#include "utility.h"

int amain() {
	int frequencies[128] = {}; //use array of 128 bits to store frequencies
	string inputfile = "clear.txt";
	ifstream ifile(inputfile);
	unsigned char c;
	if (ifile) {
		while (ifile >> noskipws >> c) {
			int intc = static_cast<int>(c); //convert to ASCII
			//cout << c << " " << intc << endl;

			//convert 2 non-ASCII apostrophes in clear.txt to ASCII
			//"don't" and "Country's"
			// if (intc == 146) {
			//	frequencies[static_cast<int>('\'')]++;
			//}
			//else {
				frequencies[intc]++;
			//}
		}
	}

	//write output file of frequencies as space-delimited output
	string outputfile = "freq.txt";
	ofstream ofile(outputfile);

	if (ofile.is_open()) {
		for (int i = 0; i < 128; i++) {
			if (frequencies[i] > 0) { //non-zero frequencies only
				if (i == 10) { //if new line character
					ofile << "LF " << frequencies[i] << endl;
				}
				else {
					ofile << static_cast<char>(i) << " " << frequencies[i] << endl;
				}
			}
		}
		ofile.close();
	}
	cout << "Wrote frequencies to output file: " << outputfile << endl;
	system("pause");
	return 0;
}