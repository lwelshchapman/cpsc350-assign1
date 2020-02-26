/* 
 * Logan Welsh
 * 2325215
 * lwelsh@chapman.edu
 * CPSC-350-01
 * Assignment 1
 * DNA.cpp
 * Definition of class for working with "DNA lists".
 */

#include "DNA.h"


// CONSTRUCTORS

DNA::DNA(string inPath, string newOutPath = "lwelsh.out", bool literal = false) {

	
	// GET DNA LIST FROM GIVEN FILE.
	string newDnaString = "";
	
	ifstream inStream;
	inStream.open(inPath);
	
	if (!inStream.is_open()) {
		
		cout << "!! Could not open " + inPath + ". Using arbitrary values." << endl;
		newDnaString = DNA::genDnaString(5, 20, 1000);

	}
	else {
		
		string temp = "";

		while (!inStream.eof()) {
			
			inStream >> temp;
			
			if (!inStream.fail()) {
				
				newDnaString += temp + '\n';				
			}	
		}	
	}
	
	//Debug: cout << newDnaString << endl;
	
	
	
	// SET UP MEMBER VARIABLES.
	outPath = newOutPath;
	
	dnaString = newDnaString;
	dnaLengthStr = "";
	
	lines = 0;
	sum = 0;
	mean = 0.0;
	variance = 0.0;
	stdDev = 0.0;
	
	nucleoProb = "";
	bigramProb = "";
	
	//Debug: cout << "\tOingo" << endl;
	
	
	
	// COMPUTE STATISTICS.
	compute();	// Runs automatically upon instantiation! Saves some redundant code elsewhere.

	
}


DNA::~DNA() {	// Nothing to do here... no pointers to delete!
	//Debug: cout << "\tBoingo" << endl;
}


const string DNA::NUCLEO = "atcg";
const string DNA::CONTACT_INFO = "Logan Welsh\n2325215\nlwelsh@chapman.edu\nCPSC-350-01\nAssignment 1\n";









// MASTER COMPUTATION

void DNA::compute() {
	
	lines = countLines(dnaString);	// Get the number of lines in the DNA list.
	
	getDnaLengthStr();	// Concatenate the lengths of each line into one string (in place of an array).
	
	calcDnaSum();	// Calculate the sum of the lengths of each line.
	
	calcDnaMean();	// Calculate the mean of the lengths of each line.
	
	calcDnaVariance();	// Calculate the variance of the lengths of each line.
	
	calcDnaStdDev();	// Calculate the standard deviation of the lengths of each line.
	
	calcNucleoProb();	// Calculate the relative probability of each nucleotide.

	calcBigramProb();	// Calculate the relative probability of each bigram.
	
}





// SUB-COMPUTATIONS

int DNA::countLines(string inStr) {	// Get the number of lines in the DNA list.
	int lineCount = 0;
	
	for(int i = 0; i < inStr.size(); ++i) {
		if(inStr[i] == '\n') {
			lineCount += 1;
		}
	}
	
	return lineCount;
}


int DNA::dnaLength(int line) {	// Get the length of a specific line.
	int currentLine = 0;
	int countInd = 0;
	int count = 0;
	
	if(line != 0) {
		for(int i = 0; i < dnaString.size(); ++i) {
			
			if(dnaString[i] == '\n') {
				
				currentLine += 1;
				
				if(currentLine == line) {
					
					countInd = i + 1;
					break;
				}
			}
			
		}
	}
	
	while(dnaString[countInd] != '\n') {
		count += 1;
		countInd += 1;
	}
	
	return count;
}


void DNA::getDnaLengthStr() {	// Concatenate the lengths of each line into one string (in place of an array).
	
	dnaLengthStr = "";
	
	for(int i = 0; i < lines; ++i) {
		dnaLengthStr += to_string(dnaLength(i)) + '\n';
	}

}


void DNA::calcDnaSum() {	// Calculate the sum of the lengths of each line.
	
	sum = 0;
	string temp = "";
	
	for(int i = 0; i < dnaLengthStr.size(); ++i) {
		if(dnaLengthStr[i] != '\n') {
			temp += dnaLengthStr[i];
		}
		else {
			sum += stoi(temp);
			//Debug: cout << "[" << temp << "]" << endl;
			temp = "";
		}
	}

}


void DNA::calcDnaMean() {	// Calculate the mean of the lengths of each line.

	mean = static_cast<double>(sum) / lines;

}


void DNA::calcDnaVariance() {	// Calculate the variance of the lengths of each line.

	double sqSum = 0;
	string temp = "";
	
	for(int i = 0; i < dnaLengthStr.size(); ++i) {
		
		if(dnaLengthStr[i] != '\n') {
			
			temp += dnaLengthStr[i];
			
		}
		else {

			double diff = stoi(temp) - mean;
			sqSum += pow(diff, 2);
			temp = "";

		}
		
	}
	
	variance = sqSum / lines;
}


void DNA::calcDnaStdDev() {	// Calculate the standard deviation of the lengths of each line.
	
	stdDev = sqrt(variance);
	
}


int DNA::calcTotalNucleo() {	// Calculate the total number of nucleotides.
	
	int totalNuc = 0;
	
	for(int i = 0; i < dnaString.size(); ++i) {
		
		for(int j = 0; j < NUCLEO.size(); ++j) {
			
			if(tolower(dnaString[i]) == NUCLEO[j]) {
				
				totalNuc += 1;
				break;
				
			}
		}
	}

	return totalNuc;
}


void DNA::calcNucleoProb() {	// Calculate the relative probability of each nucleotide.
	
	int totalNucleo = calcTotalNucleo();
	
	nucleoProb = "";
	int nucSum = 0;
	
	for(int i = 0; i < NUCLEO.size(); ++i) {
		
		for(int j = 0; j < dnaString.size(); ++j) {
			
			if(tolower(dnaString[j]) == NUCLEO[i]) {
				nucSum += 1;
			}
		}
		
		nucleoProb += '\t';
		nucleoProb += NUCLEO[i];
		nucleoProb += ": " + to_string(100 * static_cast<double>(nucSum) / totalNucleo) + "%\n";
		nucSum = 0;
	}
}


int DNA::calcTotalBigrams() {	// Calculate the total number of bigrams.
	
	int totalBi = 0;
	
	for(int i = 0; i < dnaString.size() -1; ++i) {
		
		if( !( (dnaString[i] == '\n') || (dnaString[i + 1] == '\n') ) ) {
			
			totalBi += 1;
			
		}
	}
	
	return totalBi;
}


void DNA::calcBigramProb() {	// Calculate the relative probability of each bigram.
	
	int totalBigrams = calcTotalBigrams();
	
	bigramProb = "";
	int biSum = 0;

	for(int i = 0; i < NUCLEO.size(); ++i) {

		for(int j = 0; j < NUCLEO.size(); ++j) {

			string bigram = "";
			bigram += NUCLEO[i];
			bigram += NUCLEO[j];

			for(int k = 0; k < dnaString.size() - 1; ++k) {
				
				if( !( (dnaString[k] == '\n') || (dnaString[k + 1] == '\n') ) ) {
					
					string biCurrent = "";
					biCurrent += tolower(dnaString[k]);
					biCurrent += tolower(dnaString[k + 1]);
					
					//Debug: cout << biCurrent << endl;
					
					if( biCurrent  == bigram) {
						
						biSum += 1;
						
					}
				}
			}

			//Debug: cout << bigram << ' ' << biSum << endl;
			bigramProb += '\t' + bigram + ": " + to_string(100 * static_cast<double>(biSum) / totalBigrams) + "%\n";
			biSum = 0;

		}
	}
}






// DNA GENERATION

int DNA::genLength(double lenStdDev, double lenMean) {	// Generate a new line length based on the Box-Muller transform thing.
	
	//FIX: a and b are supposed to fall within [0, 1). Right now there is a tiny chance they can be 1.
	
	double a = static_cast<double>(rand()) / RAND_MAX;
	double b = static_cast<double>(rand()) / RAND_MAX;
	//Debug: cout << a << '\t' << b << endl;
	
	double c = sqrt( -2 * log(a) ) * cos( 2 * (4 * atan(1)) * b);
	
	int d = static_cast<int>( (lenStdDev * c) + lenMean );
	// ^-- "Life has many doors, Ed-boy!"
	
	return (d > 0) ? d : 1;	// Minimum of one nucleotide per line.
	
}

char DNA::genNucleo() {	// Randomly generate a nucleotide. Basically just rolling a D4.
	
	int i = rand() % NUCLEO.size();
	return NUCLEO[i];

}

string DNA::genLine(int len) {	// Generate a line of random nucleotides from a given length.

	string newLine = "";
	
	for(int i = 0; i < len; ++i) {
		
		newLine += genNucleo();
		
	}

	newLine += "\n";
	return newLine;
}


string DNA::genDnaString(double lenStdDev, double lenMean, int lineAmount = 1000) {	// [Overloaded] Generate and combine multiple DNA lines into a DNA list.
	
	string newDnaString = "";
	
	for(int i = 0; i < lineAmount; ++i) {
		
		newDnaString += genLine(genLength(lenStdDev, lenMean));
		
	}
	
	return newDnaString;
}


string DNA::genDnaString(int lineAmount = 1000) {	// Generate and combine multiple DNA lines into a DNA list.
	return genDnaString(stdDev, mean, lineAmount);
}






// DATA OUTPUT

string DNA::statString() {	// Generate a labelled string containing the calculated statistics.
	string outStr = "";
	
	outStr += "Lines: " + to_string(lines) + '\n';
	outStr += "Sum: " + to_string(sum) + '\n';
	outStr += "Mean: " + to_string(mean) + '\n';
	outStr += "Variance: " + to_string(variance) + '\n';
	outStr += "Standard Deviation: " + to_string(stdDev) + '\n';
	outStr += "Nucleotide Probability: \n" + nucleoProb;
	outStr += "Bigram Probability: \n" + bigramProb;
	
	return outStr;
}


void DNA::outputToFile(string data, std::ios_base::openmode flag = ios::app) {	// Write a string to this DNA list's output file.
	
	ofstream outStream;
	outStream.open(outPath, flag);
	outStream << data;
	outStream.close();

}