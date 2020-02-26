/* 
 * Logan Welsh
 * 2325215
 * lwelsh@chapman.edu
 * CPSC-350-01
 * Assignment 1
 * DNA.h
 * Declaration of class for working with "DNA lists".
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>


using namespace std;

class DNA {
	
	public:
	
		// CONSTRUCTORS
		DNA(string inString, string newOutPath, bool literal);	// No default constructor because main.cpp handles default input file.
		~DNA();	// Destructor (a rather anticlimactic one).
	
	
		// PUBLIC MEMBER VARIABLES
		static const string NUCLEO;	// String of nucleotide characters, for checking nucleotide/bigram probabilities.
		static const string CONTACT_INFO;	// My contact info, for writing to the output file.
	
		string outPath;	// Filepath for file output.
	
	
		// PUBLIC FUNCTIONS
		void compute();	// Master computation; calls all sub-computations upon instantiation.
		
		void outputToFile(string data, std::ios_base::openmode flag);	// Write a string to this DNA list's output file.

		string statString();	// Generate a labelled string containing the calculated statistics.
		
		static string genDnaString(double lenStdDev, double lenMean, int lineAmount);
		string genDnaString(int lineAmount);	// Generate and combine multiple DNA lines into a DNA list.



	private:
	
		// PRIVATE MEMBER VARIABLES
		string dnaString;	// DNA list as one continuous string.
		string dnaLengthStr;	// DNA list line lengths one continuous string.
		
		int lines;	// Number of lines in the DNA list.
		int sum;	// Sum of the lengths of each line.
		double mean;	// Mean of the lengths of each line.
		double variance;	// Variance of the lengths of each line.
		double stdDev;	// Standard deviation of the lengths of each line.
		
		string nucleoProb;	// Relative probability of each nucleotide.
		string bigramProb;	// Relative probability of each bigram.


		// PRIVATE FUNCTIONS
		int countLines(string inStr);	// Get the number of lines in the DNA list.
		int dnaLength(int line);	// Get the length of a specific line.
		void getDnaLengthStr();	// Concatenate the lengths of each line into one string (in place of an array).
		void calcDnaSum();	// Calculate the sum of the lengths of each line.
		void calcDnaMean();	// Calculate the mean of the lengths of each line.
		void calcDnaVariance();	// Calculate the variance of the lengths of each line.
		void calcDnaStdDev();	// Calculate the standard deviation of the lengths of each line.
		
		int calcTotalNucleo();	// Calculate the total number of nucleotides.
		void calcNucleoProb();	// Calculate the relative probability of each nucleotide.
		int calcTotalBigrams();	// Calculate the total number of bigrams.
		void calcBigramProb();	// Calculate the relative probability of each bigram.
		
		static int genLength(double lenStdDev, double lenMean);	// Generate a new line length based on the Box-Muller transform thing.
		static char genNucleo();	// Randomly generate a nucleotide. Basically just rolling a D4.
		static string genLine(int len);	// Generate a line of random nucleotides from a given length.
		
		
		
};