#include "DNA.cpp"


int main(int argc, char** argv) {
	
	srand(time(0));
	
	string originStr = "";
	
	int stdDev = 10;
	int mean = 30;
	int lines = 1000;
	string filename = "origin.txt";
	
	if(argc > 1) {
		stdDev = stoi(argv[1]);
	}
	if(argc > 2) {
		mean = stoi(argv[2]);
	}
	if(argc > 3) {
		lines = stoi(argv[3]);	
	}
	if(argc > 4) {
		filename = argv[4];
	}
	if(argc > 5) {
		cout << "Incorrect number of parameters." << endl;
		return 1;
	}
	
	cout << "Standard Deviation: " << stdDev << endl;
	cout << "Mean: " << mean << endl;
	cout << "Lines: " << lines << endl;
	cout << "Output file: " << filename << endl;

	
	cout << "Generating origin string...";
	originStr = DNA::genDnaString(stdDev, mean, lines);
	cout << "Done." << endl;
	
	//Debug: cout << originStr << endl;
	
	cout << "Writing origin string to " + filename + "...";
	ofstream outFile;
	outFile.open(filename);
	outFile << originStr;
	outFile.close();
	cout << "Done." << endl;

	cout << "Origin DNA list generated and saved successfully." << endl;
	
	return 0;
}