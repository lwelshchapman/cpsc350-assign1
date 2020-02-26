/* 
 * Logan Welsh
 * 2325215
 * lwelsh@chapman.edu
 * CPSC-350-01
 * Assignment 1
 * main.cpp
 * Implementation of class for working with "DNA lists".
 */

#include "DNA.cpp"



int main(int argc, char** argv) {
	
	srand(time(0));	// Set unique seed for random number generation.
	
	
	cout << endl << "Beginning DNA processing program." << endl << endl;
	
	
	
	// Work out command line arguments.	
	string inFile = "origin.out";
	string outFile = "lwelsh.out";
	
	if(argc > 1) {	// Arg 1: Input file path.
		inFile = argv[1];
	}
	if(argc > 2) {	// Arg 2: Output file path.
		outFile = argv[2];
	}
	if(argc > 3) {
		cout << "Incorrect number of parameters." << endl;
		return 1;
	}
	
	
	// Clear output file.
	ofstream tempOut;
	tempOut.open(outFile, ios::trunc);
	tempOut.close();
	
	
	// DNA processing loop.
	bool keepAsking = true;
	
	while(keepAsking) {

		// Read in DNA list, compute stats.
		cout << "Reading DNA list from " + inFile + " and computing stats..." << endl;
		
		DNA *dna = new DNA(inFile, outFile);
		
		cout << "  ...Done." << endl;
		
		
		// Display stats.
		cout << endl << dna->statString() << endl;
		
		
		
		// Generate new list.
		cout << "Generating new DNA list..." << endl;
		
		string newDNA = dna->genDnaString();
		
		cout << "  ...Done." << endl;
		
		
		
		// Write to file.
		cout << "Writing to " + outFile + "..." << endl;
		dna->outputToFile( DNA::CONTACT_INFO + "\n" );	// Overwrite previous file
		dna->outputToFile( dna->statString() + "\n" );	// Append
		dna->outputToFile( newDNA + "\n" );	// Append
		cout << "  ...Done." << endl;
		
		
		
		// Prompt for another round.
		cout << "\nFinished processing " + outFile + " successfully.\n\n";
		cout << "Process another list? (\"y\" for yes, anything else to exit) ";
		
		string response = "";
		cin >> response;
		
		keepAsking = ( response == "y");
		
		if(keepAsking) {
			cout << "Filename: ";
			cin >> inFile;
			cout << endl;
		}
		
		delete dna;

	}

	
	cout << "Exiting.\n\n";
	
	return 0;
}