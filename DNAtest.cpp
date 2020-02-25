#include "DNA.cpp"


int main(int argc, char** argv) {
	
	srand(time(0));
	
	string origin = DNA::genDnaString(5, 20, 1000);

	DNA *testDNA1 = new DNA(origin, "lwelsh.out1");
	cout << testDNA1->statString() << endl;
	
	DNA *testDNA2 = new DNA(testDNA1->genDnaString(1000), "lwelsh.out2");
	cout << testDNA2->statString() << endl;
	
	
	testDNA1->outputResults();
	testDNA2->outputResults();
	
	delete testDNA1;
	delete testDNA2;
	
	return 0;
}