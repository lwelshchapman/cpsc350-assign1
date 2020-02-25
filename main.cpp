#include "DNA.cpp"


int main(int argc, char** argv) {
	
	srand(time(0));
	
	string inFile = "origin.txt";
	string outFile = "lwelsh.out";
	
	if(argc > 1) {
		inFile = argv[1];
	}
	if(argc > 2) {
		outFile = argv[2];
	}
	if(argc > 3) {
		cout << "Incorrect number of parameters." << endl;
		return 1;
	}
	
	// Clearing out contents of previous outFile...
	ofstream outStream;
	outStream.open(outFile);
	outStream.close();
	// Done.

	cout << "Reading DNA list from " + inFile + " and computing stats...";
	DNA *dna = new DNA(inFile, outFile);
	cout << "Done." << endl;
	
	cout << "Writing stats to " + outFile + "...";
	dna->outputResults();
	cout << "Done." << endl;
	
	delete dna;
	
	return 0;
}