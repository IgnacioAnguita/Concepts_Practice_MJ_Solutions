# include <iostream>
# include "test.h"
# include "greeks.h"


using namespace std;

int main(int argc, char** argv) {
	testDelta();
	testGamma();
	testVega();
	testRho();
	testTheta();
	testMC1();
	testMC2();
	testMC3();
}
