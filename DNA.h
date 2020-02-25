// http://www.cplusplus.com/reference/string/to_string/
// http://www.cplusplus.com/reference/string/stoi/
// https://www.mathsisfun.com/data/standard-deviation.html
// https://stackoverflow.com/questions/185844/how-to-initialize-private-static-members-in-c
// http://www.cplusplus.com/reference/cstdlib/RAND_MAX/
// http://www.cplusplus.com/forum/beginner/83485/



#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>


using namespace std;

class DNA {
	
	public:
		DNA(string newDnaString, string newOutPath);
		~DNA();
	

		static const string NUCLEO;
		
		string inPath;
		string outPath;
		ofstream outFile;
	
		void compute();
		
		void outputResults();

		string statString();
		
		static string genDnaString(double lenStdDev, double lenMean, int lineAmount);
		string genDnaString(int lineAmount);

	private:
		string dnaString;
		string dnaLengthStr;
		
		int lines;
		int sum;
		double mean;
		double variance;
		double stdDev;
		
		int totalNucleo;
		string nucleoProb;
		int totalBigrams;
		string bigramProb;



		int countLines(string inStr);
		int dnaLength(int line);
		void getDnaLengthStr();
		void calcDnaSum();
		void calcDnaMean();
		void calcDnaVariance();
		void calcDnaStdDev();
		
		void calcTotalNucleo();
		void calcNucleoProb();
		void calcTotalBigrams();
		void calcBigramProb();
		
		static int genLength(double lenStdDev, double lenMean);
		static char genNucleo();
		static string genLine(int len);
		
		
		
};