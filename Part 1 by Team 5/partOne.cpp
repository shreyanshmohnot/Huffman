/* Part One by Team 5 - Mohnot and Thomas */

#include "utility.h"

int main() {
	fstream file;
	string inputFile = "clear.txt";
	string outputFile = "freq.txt";
	
	char singleCharacter;
	int ascii[128] = { 0 };

	/* Open input file to get character by character without skipping the whitespaces. */
	file.open(inputFile, ios::in);
	
	/* Loop to get characters from the file using get(). Increment the values of int array at each ascii value.
	*  static_cast is used for converting char to its ASCII value.
	*/
	while (file.get(singleCharacter)) {
		ascii[static_cast<int>(singleCharacter)]++;
	}
	file.close();
	
	/* Open new output file to store the output of the ascii array. */
	file.open(outputFile, ios::out | ios::trunc);
	
	/* Loop the array to fetch each ascii values and corresponding frequency counts. */
	for (int j = 0; j < 128; j++) {
		if (ascii[j] > 0) {
			if (j == 10)
				file << "LF " << ascii[j] << "\n";
			else
				file << static_cast<char>(j) << " " << ascii[j] << "\n";
		}
	}
	file.close();
	return 0;
}