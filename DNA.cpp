#include "DNA.h"

// CONSTRUCTORS
DNA::DNA(string newDnaString, string newOutPath = "lwelsh.out") {
	
	srand(time(0));
	
	outPath = newOutPath;
	outFile.open(outPath);
	outFile.close();
	outFile.open(outPath, ios::app);
	
	dnaString = newDnaString;
	dnaLengthStr = "";
	
	lines = 0;
	sum = 0;
	mean = 0.0;
	variance = 0.0;
	stdDev = 0.0;
	
	totalNucleo = 0;
	
	nucleoProb = "";
	bigramProb = "";
	
	//Debug: cout << "\tOingo" << endl;
	
	compute();
}


DNA::~DNA() {
	outFile.close();
	//Debug: cout << "\tBoingo" << endl;
}


const string DNA::NUCLEO = "atcg";

// MUTATORS
//void DNA::setDnaString(string newDnaString) {
	
	





// ACCESSORS






// MASTER COMPUTATION
void DNA::compute() {
	
	lines = countLines(dnaString);
	
	getDnaLengthStr();
	
	calcDnaSum();
	
	calcDnaMean();
	
	calcDnaVariance();
	
	calcDnaStdDev();
	
	calcNucleoProb();

	calcBigramProb();
	
	/*
	for(int i = 0; i < 100; ++i) {
		//cout << genLength() << endl;
		cout << genNucleo() << endl;
	}
	*/
	
	//cout << genDnaString(100) << endl;
}



// SUB-COMPUTATION
int DNA::countLines(string inStr) {
	int lineCount = 0;
	
	for(int i = 0; i < dnaString.size(); ++i) {
		if(dnaString[i] == '\n') {
			lineCount += 1;
		}
	}
	
	return lineCount;
}


int DNA::dnaLength(int line) {
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


void DNA::getDnaLengthStr() {
	
	dnaLengthStr = "";
	
	for(int i = 0; i < lines; ++i) {
		dnaLengthStr += to_string(dnaLength(i)) + '\n';
	}

}


void DNA::calcDnaSum() {
	
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


void DNA::calcDnaMean() {

	mean = static_cast<double>(sum) / lines;

}


void DNA::calcDnaVariance() {

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


void DNA::calcDnaStdDev() {
	
	stdDev = sqrt(variance);
	
}


void DNA::calcTotalNucleo() {
	
	totalNucleo = 0;
	
	for(int i = 0; i < dnaString.size(); ++i) {
		
		for(int j = 0; j < NUCLEO.size(); ++j) {
			
			if(tolower(dnaString[i]) == NUCLEO[j]) {
				
				totalNucleo += 1;
				break;
				
			}
		}
	}

}


void DNA::calcNucleoProb() {
	
	calcTotalNucleo();
	
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


void DNA::calcTotalBigrams() {
	
	totalBigrams = 0;
	
	for(int i = 0; i < dnaString.size() -1; ++i) {
		
		if( !( (dnaString[i] == '\n') || (dnaString[i + 1] == '\n') ) ) {
			
			totalBigrams += 1;
			
		}
	}
	
}


void DNA::calcBigramProb() {
	
	calcTotalBigrams();
	
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



int DNA::genLength(double lenStdDev, double lenMean) {
	
	//FIX: a and b are supposed to fall within [0, 1). Right now there is a tiny chance they can be 1.
	
	double a = static_cast<double>(rand()) / RAND_MAX;
	double b = static_cast<double>(rand()) / RAND_MAX;
	//Debug: cout << a << '\t' << b << endl;
	
	double c = sqrt( -2 * log(a) ) * cos( 2 * (4 * atan(1)) * b);
	
	double d = (lenStdDev * c) + lenMean;
	// ^-- "Life has many doors, Ed-boy!"

	return static_cast<int>(d);
}

char DNA::genNucleo() {
	
	int i = rand() % NUCLEO.size();
	return NUCLEO[i];

}

string DNA::genLine(int len) {

	string newLine = "";
	
	for(int i = 0; i < len; ++i) {
		
		newLine += genNucleo();
		
	}

	newLine += '\n';
	return newLine;

}


string DNA::genDnaString(double lenStdDev, double lenMean, int lineAmount = 1000) {
	
	string newDnaString = "";
	
	for(int i = 0; i < lineAmount; ++i) {
		
		newDnaString += genLine(genLength(lenStdDev, lenMean));
		
	}
	
	return newDnaString;
	
}

string DNA::genDnaString(int lineAmount = 1000) {
	return genDnaString(stdDev, mean, lineAmount);
}


// MISC

string DNA::statString() {
	string outStr = "";
	
	outStr += "Lines: " + to_string(lines) + '\n';
	outStr += "Sum: " + to_string(sum) + '\n';
	outStr += "Mean: " + to_string(mean) + '\n';
	outStr += "Variance: " + to_string(variance) + '\n';
	outStr += "Standard Deviation: " + to_string(stdDev) + '\n';
	outStr += "Total Nucleotides: " + to_string(totalNucleo) + '\n';
	outStr += "Nucleotide Probability: \n" + nucleoProb;
	outStr += "Bigram Probability: \n" + bigramProb;
	
	return outStr;
}


void DNA::outputResults() {
	
	string header = "Logan Welsh\n2325215\nlwelsh@chapman.edu\nCPSC-350-01\nAssignment 1\n";
	/*
	"Logan Welsh" +
	"2325215" +
	"lwelsh@chapman.edu" +
	"CPSC-350-01" +
	"Assignment 1"
	*/
	
	string stats = statString();
	
	//string fullStr = header + statString;
	
	outFile << header + "\n" + stats;
	
}