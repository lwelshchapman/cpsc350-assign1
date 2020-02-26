/* 
 * Logan Welsh
 * 2325215
 * lwelsh@chapman.edu
 * CPSC-350-01
 * Assignment 1
 * generateOrigin.cpp
 * Helper program to simplify generating an original "DNA list".
 */

#include "DNA.cpp"


int main(int argc, char** argv) {
	
	srand(time(0));	// Set unique seed for random number generation.
	
	
	// Initialize variables with default values.
	string originStr = "";
	
	int stdDev = 10;
	int mean = 30;
	int lines = 1000;
	string filename = "origin.out";
	
	
	// Work out command line arguments.
	if(argc > 1) {	// Arg 1: Standard deviation.
		stdDev = stoi(argv[1]);
	}
	if(argc > 2) {	// Arg 2: Mean.
		mean = stoi(argv[2]);
	}
	if(argc > 3) {	// Arg 3: Number of lines.
		lines = stoi(argv[3]);	
	}
	if(argc > 4) {	// Arg 4: Output file path.
		filename = argv[4];
	}
	if(argc > 5) {
		cout << "Incorrect number of parameters." << endl;
		return 1;
	}
	
	
	// Display to user the values that will be used.
	cout << "Standard Deviation: " << stdDev << endl;
	cout << "Mean: " << mean << endl;
	cout << "Lines: " << lines << endl;
	cout << "Output file: " << filename << endl;

	
	// Generate origin string.
	cout << "Generating origin string..." << endl;
	originStr = DNA::genDnaString(stdDev, mean, lines);
	cout << "  ...Done." << endl;
	//Debug: cout << originStr << endl;
	
	
	// Write origin string to file.
	cout << "Writing origin string to " + filename + "..." << endl;
	ofstream outFile;
	outFile.open(filename);
	outFile << originStr;
	outFile.close();
	cout << "  ...Done." << endl;


	// All done.
	cout << "Origin DNA list generated and saved successfully." << endl;
	
	return 0;
}